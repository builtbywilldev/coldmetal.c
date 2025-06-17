// ===============================================================
// File: memory.c
// Coldmetal Phase: 5
// Purpose: Persistent Memory Loader & Embedding Engine
// Linked to: tokenizer.h, embedder.h, memory.h
// Author: Silent Prototype — BuiltByWill
// ===============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tokenizer.h"
#include "embedder.h"
#include "memory.h"

#define MAX_MEMORY_ITEMS 9422
#define MEMORY_DIR "data/.mem/"
#define MEMORY_FILE "data/.mem/morpheus.mem"

static MemoryItem memory[MAX_MEMORY_ITEMS];
static int memory_count = 0;

// ===============================================================
// 📥 Load a Single Memory File
// Format: T||content
// T = memory type (U or A), content = string to embed
// ===============================================================
void load_memory(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("⚠️  Could not open file: %s\n", filename);
        return;
    }

    char line[MAX_MEMORY_LEN + 10];
    while (fgets(line, sizeof(line), file)) {
        if (memory_count >= MAX_MEMORY_ITEMS) break;

        line[strcspn(line, "\n")] = '\0';

        char type = 'U';
        char *content = line;
        if (line[1] == '|' && line[2] == '|') {
            type = line[0];
            content = &line[3];
        }

        // ✳️ Deduplication check
        int duplicate = 0;
        for (int i = 0; i < memory_count; i++) {
            if (strcmp(memory[i].content, content) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        strncpy(memory[memory_count].content, content, MAX_MEMORY_LEN);
        memory[memory_count].content[MAX_MEMORY_LEN - 1] = '\0';
        embed_text(memory[memory_count].content, memory[memory_count].vector);
        memory[memory_count].type = type;
        memory[memory_count].value = 1.0f;
        memory_count++;
    }

    fclose(file);
}

// ===============================================================
// 📦 Load All Memory Files from Disk
// Loads each .mem file including morpheus.mem last
// ===============================================================
void load_all_memories() {
    struct stat st = {0};
    if (stat(MEMORY_DIR, &st) == -1) {
        mkdir(MEMORY_DIR, 0700);
    }

    DIR *dir = opendir(MEMORY_DIR);
    if (!dir) {
        printf("⚠️  Could not open memory directory: %s\n", MEMORY_DIR);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!entry->d_name || !strstr(entry->d_name, ".mem")) continue;

        if (strcmp(entry->d_name, "morpheus.mem") == 0) continue; // Skip for now

        char path[512];
        snprintf(path, sizeof(path), "%s%s", MEMORY_DIR, entry->d_name);
        printf("📂 Loading memory: %s\n", path);
        load_memory(path);

        if (memory_count >= MAX_MEMORY_ITEMS) break;
    }

    closedir(dir);

    // Load morpheus.mem last (always)
    load_memory(MEMORY_FILE);
}

// ===============================================================
// 💾 Save All Current Memory to File
// ===============================================================
void save_memory(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("⚠️  Could not open file to save memory: %s\n", filename);
        return;
    }

    for (int i = 0; i < memory_count; i++) {
        fprintf(file, "%c||%s\n", memory[i].type, memory[i].content);
    }

    fclose(file);
}

// ===============================================================
// ➕ Add New Memory
// ===============================================================
void remember(const char *text) {
    remember_with_type(text, 'U');
}

void remember_with_type(const char *text, char type) {
    if (memory_count >= MAX_MEMORY_ITEMS) return;

    // ✳️ Prevent duplicates
    for (int i = 0; i < memory_count; i++) {
        if (strcmp(memory[i].content, text) == 0) return;
    }

    strncpy(memory[memory_count].content, text, MAX_MEMORY_LEN);
    memory[memory_count].content[MAX_MEMORY_LEN - 1] = '\0';
    embed_text(memory[memory_count].content, memory[memory_count].vector);

    memory[memory_count].type = type;
    memory[memory_count].value = 1.0f;
    memory_count++;

    struct stat st = {0};
    if (stat(MEMORY_DIR, &st) == -1) {
        mkdir(MEMORY_DIR, 0700);
    }
}

// ===============================================================
// 🧰 Utilities
// ===============================================================
void print_memory() {
    for (int i = 0; i < memory_count; i++) {
        printf("• (%c) [$%.2f COLD] %s\n",
               memory[i].type,
               memory[i].value,
               memory[i].content);
    }
}

int memory_count_items() {
    return memory_count;
}

float *memory_get_vector(int index) {
    if (index < 0 || index >= memory_count)
        return NULL;
    return memory[index].vector;
}

const char *memory_get_text(int index) {
    if (index < 0 || index >= memory_count)
        return "[invalid memory]";
    return memory[index].content;
}

char memory_get_type(int index) {
    if (index < 0 || index >= memory_count)
        return '?';
    return memory[index].type;
}

float memory_get_value(int index) {
    if (index < 0 || index >= memory_count)
        return 0.0f;
    return memory[index].value;
}

void score_memory(int index, float delta) {
    if (index < 0 || index >= memory_count) return;
    memory[index].value += delta;
    if (memory[index].value < 0.0f)
        memory[index].value = 0.0f;
}

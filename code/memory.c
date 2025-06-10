// ===============================================================
//  memory.c — Persistent Memory Loader & Embedding Engine
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#include "tokenizer.h"
#include "embedder.h"
#include "memory.h"

#define MAX_MEMORY_ITEMS 9422

MemoryItem memory[MAX_MEMORY_ITEMS];
int memory_count = 0;

// ===============================================================
// 📥 Load a Single Memory File
// ===============================================================
void load_memory(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("⚠️  Could not open file: %s\n", filename);
        return;
    }

    char line[MAX_MEMORY_LEN + 10];
    while (fgets(line, sizeof(line), file)) {
        if (memory_count >= MAX_MEMORY_ITEMS) break;

        line[strcspn(line, "\n")] = '\0';  // Strip newline

        // Check for type prefix like Q|| or A||
        char type = 'U';  // default: Unknown
        char* content = line;
        if (line[1] == '|' && line[2] == '|') {
            type = line[0];
            content = &line[3];  // skip "T||"
        }

        remember_with_type(content, type);
    }

    fclose(file);
}

// ===============================================================
// 📦 Load All Memory Files from Disk
// ===============================================================
void load_all_memories() {
    const char* folder = "data/.mem/";
    DIR* dir = opendir(folder);
    struct dirent* entry;

    if (!dir) {
        printf("⚠️  Could not open memory directory: %s\n", folder);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt")) {
            char path[512];
            snprintf(path, sizeof(path), "%s%s", folder, entry->d_name);
            load_memory(path);
        }

        if (memory_count >= MAX_MEMORY_ITEMS) break;
    }

    closedir(dir);

    // 🔄 Load persistent chat log last
    load_memory("data/.mem/morpheus.mem");
}

// ===============================================================
// 💾 Save All Current Memory to File (Snapshot)
// Format: T||Text
// ===============================================================
void save_memory(const char* filename) {
    FILE* file = fopen(filename, "w");
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
// 🧠 Remember: Append New Memory & Store in Vector Space
// Defaults to Unknown type ('U')
// ===============================================================
void remember(const char* text) {
    remember_with_type(text, 'U');
}

// ===============================================================
// 🧠 Tagged Memory Storage
// Called from upgraded trainer.c
// ===============================================================
void remember_with_type(const char* text, char type) {
    if (memory_count >= MAX_MEMORY_ITEMS) return;

    strncpy(memory[memory_count].content, text, MAX_MEMORY_LEN);
    memory[memory_count].content[MAX_MEMORY_LEN - 1] = '\0';

    embed_text(memory[memory_count].content, memory[memory_count].vector);
    memory[memory_count].type = type;
    memory_count++;

    // Also persist to morpheus.mem
    FILE* f = fopen("data/.mem/morpheus.mem", "a");
    if (f) {
        fprintf(f, "%c||%s\n", type, text);
        fclose(f);
    } else {
        printf("⚠️  Could not append to morpheus.mem\n");
    }
}

// ===============================================================
// 🛠️ Accessors & Utilities
// ===============================================================
void print_memory() {
    for (int i = 0; i < memory_count; i++) {
        printf("• (%c) %s\n", memory[i].type, memory[i].content);
    }
}

int memory_count_items() {
    return memory_count;
}

float* memory_get_vector(int index) {
    if (index < 0 || index >= memory_count) return NULL;
    return memory[index].vector;
}

const char* memory_get_text(int index) {
    if (index < 0 || index >= memory_count) return "[invalid memory]";
    return memory[index].content;
}

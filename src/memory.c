// ===============================================================
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

MemoryItem memory[MAX_MEMORY_ITEMS];
int memory_count = 0;

// Load one memory file into RAM and embed its contents
void load_memory(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("⚠️ Could not open file: %s\n", filename);
        return;
    }

    while (fgets(memory[memory_count].content, MAX_MEMORY_LEN, file)) {
        memory[memory_count].content[strcspn(memory[memory_count].content, "\n")] = '\0';
        embed_text(memory[memory_count].content, memory[memory_count].vector);
        memory_count++;
        if (memory_count >= MAX_MEMORY_ITEMS) break;
    }

    fclose(file);
}

// Load all .txt training files + chat history
void load_all_memories() {
    const char* folder = "data/.mem/";
    struct dirent* entry;
    DIR* dir = opendir(folder);

    if (!dir) {
        printf("⚠️ Could not open memory directory: %s\n", folder);
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

    // ✅ Also load ongoing chat memory
    load_memory("data/morpheus.mem");
}

// Save all memory items to a specific file (snapshot)
void save_memory(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < memory_count; i++) {
        fprintf(file, "%s\n", memory[i].content);
    }

    fclose(file);
}

// Store and embed new memory (also append to disk)
void remember(const char* text) {
    if (memory_count < MAX_MEMORY_ITEMS) {
        strncpy(memory[memory_count].content, text, MAX_MEMORY_LEN);
        memory[memory_count].content[MAX_MEMORY_LEN - 1] = '\0';

        embed_text(memory[memory_count].content, memory[memory_count].vector);
        memory_count++;

        // 🔁 Append to file
        FILE* f = fopen("data/.mem/morpheus.mem", "a");
        if (f) {
            fprintf(f, "%s\n", text);
            fclose(f);
        }
    }
}

// === Utility accessors ===

void print_memory() {
    for (int i = 0; i < memory_count; i++) {
        printf("• %s\n", memory[i].content);
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

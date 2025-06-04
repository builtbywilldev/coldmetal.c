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


#include "memory.h"

MemoryItem memory[MAX_MEMORY_ITEMS];
int memory_count = 0;

void load_memory(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    while (fgets(memory[memory_count].content, MAX_MEMORY_LEN, file)) {
        memory[memory_count].content[strcspn(memory[memory_count].content, "\n")] = '\0';
        memory_count++;
        if (memory_count >= MAX_MEMORY_ITEMS) break;
    }

    fclose(file);
}

void load_all_memories() {
    const char* folder = "data/.mem/";
    struct dirent* entry;
    DIR* dir = opendir(folder);

    if (!dir) {
        printf("⚠️ Could not open memory directory: %s\n", folder);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".mem")) {
            char path[512];
            snprintf(path, sizeof(path), "%s%s", folder, entry->d_name);
            load_memory(path);
        }

        if (memory_count >= MAX_MEMORY_ITEMS) break;
    }

    closedir(dir);
}

void save_memory(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    for (int i = 0; i < memory_count; i++) {
        fprintf(file, "%s\n", memory[i].content);
    }

    fclose(file);
}

void remember(const char* text) {
    if (memory_count < MAX_MEMORY_ITEMS) {
        strncpy(memory[memory_count].content, text, MAX_MEMORY_LEN);
        memory[memory_count].content[MAX_MEMORY_LEN - 1] = '\0';
        memory_count++;
    }
}

void print_memory() {
    for (int i = 0; i < memory_count; i++) {
        printf("• %s\n", memory[i].content);
    }
}

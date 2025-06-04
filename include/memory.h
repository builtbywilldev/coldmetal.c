// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef MEMORY_H
#define MEMORY_H

#define MAX_MEMORY_ITEMS 1024
#define MAX_MEMORY_LEN 512

typedef struct {
    char content[MAX_MEMORY_LEN];
} MemoryItem;

void load_memory(const char* filename);
void save_memory(const char* filename);
void remember(const char* text);
void print_memory();
void load_all_memories();  // ✅ NEW: Load all .mem files from /data/.mem/

#endif

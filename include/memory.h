// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef MEMORY_H
#define MEMORY_H

#define MAX_MEMORY_ITEMS 1024
#define MAX_MEMORY_LEN 512
#define EMBEDDING_SIZE 64  // Update if your system uses a different size

typedef struct {
    char content[MAX_MEMORY_LEN];
    float vector[EMBEDDING_SIZE];
} MemoryItem;

// Load memory file (line-by-line, embed to vector)
void load_memory(const char* filename);

// Load all .mem files from memory folder
void load_all_memories();

// Save current memory to disk
void save_memory(const char* filename);

// Add a new memory line (text + vector)
void remember(const char* text);

// Print all memory content
void print_memory();

// === New Functions for Vector-Based Logic ===
int memory_count_items();
float* memory_get_vector(int index);
const char* memory_get_text(int index);

#endif

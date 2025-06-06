// ===============================================================
// memory.h — Memory Vector Interface
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef MEMORY_H
#define MEMORY_H

#include <math.h>

#define MAX_MEMORY_ITEMS 9422
#define MAX_MEMORY_LEN   1024
#define EMBEDDING_SIZE   64

// ---------------------------------------------------------------
// 🧠 Memory Structure
// ---------------------------------------------------------------
typedef struct {
    char  content[MAX_MEMORY_LEN];
    float vector[EMBEDDING_SIZE];
    char  type;  // 'Q', 'A', 'U' (question, answer, unknown)
} MemoryItem;

// ---------------------------------------------------------------
// 📚 Global Memory Store
// ---------------------------------------------------------------
extern MemoryItem memory[MAX_MEMORY_ITEMS];
extern int        memory_count;

// ---------------------------------------------------------------
// 🔄 Load + Save
// ---------------------------------------------------------------
void load_memory(const char* filename);
void load_all_memories();
void save_memory(const char* filename);

// ---------------------------------------------------------------
// ➕ Add to Memory
// ---------------------------------------------------------------
void remember(const char* text);
void remember_with_type(const char* text, char type);  // ⬅️ Add by type

// ---------------------------------------------------------------
// 🧰 Memory Utilities
// ---------------------------------------------------------------
void        print_memory();
int         memory_count_items();
float*      memory_get_vector(int index);
const char* memory_get_text(int index);

#endif  // MEMORY_H

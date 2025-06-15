// ===============================================================
// memory.h — Memory Vector Interface
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef MEMORY_H
#define MEMORY_H

#include <math.h>
#include "config.h"

// ---------------------------------------------------------------
// 🧠 Memory Structure (Internal Use)
// ---------------------------------------------------------------
typedef struct {
    char  content[MAX_MEMORY_LEN];
    float vector[EMBEDDING_SIZE];
    char  type;    // 'Q', 'A', 'U' (question, answer, unknown)
    float value;   // 💰 Value score for weighted memory recall
} MemoryItem;

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
void remember_with_type(const char* text, char type);

// ---------------------------------------------------------------
// 🧰 Memory Utilities
// ---------------------------------------------------------------
void        print_memory();
int         memory_count_items();
float*      memory_get_vector(int index);
const char* memory_get_text(int index);
char        memory_get_type(int index);        // 🆕 Get type char (Q, A, U)
float       memory_get_value(int index);       // 🆕 Get $COLD value
void        score_memory(int index, float delta); // 💸 Tip or penalize memory

#endif  // MEMORY_H

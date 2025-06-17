// ===============================================================
// File: memory.h
// Coldmetal Phase: 4
// Purpose: Memory Vector Interface — Load, Store, Score, Recall
// Linked to: memory.c, embedder.c, tokenizer.c
// Author: Silent Prototype — BuiltByWill
// ===============================================================

#ifndef MEMORY_H
#define MEMORY_H

#include <math.h>
#include "config.h"

// ---------------------------------------------------------------
// 🧠 Memory Structure (Internal Use Only)
// ---------------------------------------------------------------
typedef struct {
    char  content[MAX_MEMORY_LEN];            // Memory text content
    float vector[EMBEDDING_SIZE];             // Embedded vector
    char  type;                               // 'Q', 'A', 'U'
    float value;                              // $COLD weighted value
} MemoryItem;

// ---------------------------------------------------------------
// 🔄 Load + Save Operations
// ---------------------------------------------------------------
void load_memory(const char* filename);
void load_all_memories();
void save_memory(const char* filename);

// ---------------------------------------------------------------
// ➕ Memory Insertion
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
char        memory_get_type(int index);
float       memory_get_value(int index);
void        score_memory(int index, float delta);

#endif  // MEMORY_H

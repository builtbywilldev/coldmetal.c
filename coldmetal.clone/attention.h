// ===============================================================
// File: attention.h
// Coldmetal Phase: 4
// Purpose: Header for core semantic similarity operations
// Linked to: attention.c, embedder.c, memory.c
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================


#ifndef ATTENTION_H
#define ATTENTION_H

// Computes cosine similarity between two float vectors
float cosine_similarity(const float *a, const float *b, int size);

#endif  // ATTENTION_H

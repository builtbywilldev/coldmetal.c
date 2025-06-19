// ===============================================================
// File: attention.c
// Coldmetal Phase: 4
// Purpose: Vector-based semantic similarity function (cosine similarity)
// Linked to: embedder.c, tokenizer.c, memory.c
// Notes: Used for memory ranking and response generation based on vector closeness
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================


#define _GNU_SOURCE

#include <math.h>     // sqrtf
#include <float.h>    // FLT_EPSILON
#include <stdio.h>

#include "tokenizer.h"
#include "attention.h"
#include "memory.h"

// ---------------------------------------------------------------
// Computes the cosine similarity between two float vectors
// ---------------------------------------------------------------
float cosine_similarity(const float *a, const float *b, int size) {
    float dot   = 0.0f;
    float mag_a = 0.0f;
    float mag_b = 0.0f;

    for (int i = 0; i < size; i++) {
        dot   += a[i] * b[i];
        mag_a += a[i] * a[i];
        mag_b += b[i] * b[i];
    }

    float denom = sqrtf(mag_a) * sqrtf(mag_b);
    if (denom < FLT_EPSILON) return 0.0f; // avoid div by zero
    return dot / denom;
}

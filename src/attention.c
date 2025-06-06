// ===============================================================
// attention.c Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================
#define _GNU_SOURCE

#include <math.h>     // sqrtf
#include <float.h>    // FLT_EPSILON
#include <stdio.h>

#include "../include/tokenizer.h"
#include "../include/attention.h"
#include "../include/memory.h"

// ---------------------------------------------------------------
// Computes the dot product between two float vectors
// ---------------------------------------------------------------
float dot_product(const float *a, const float *b, int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

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
    if (denom < FLT_EPSILON) return 0.0f;
    return dot / denom;
}

// ===============================================================
// File: softmax.c — Memory Vector Interface
// Silent Prototype — BuiltByWill
// Phase 4 Artifact // Morpheus Intelligence Unit
// Purpose: Stable softmax for probability normalization
// Linked to: softmax.h
// ===============================================================

#include <math.h>      // expf
#include <float.h>     // FLT_EPSILON

#include "softmax.h"

// 🔁 Stable, float-precise softmax (with overflow guard)
void softmax(const float* input, float* output, int length) {
    float max_val = input[0];
    for (int i = 1; i < length; i++) {
        if (input[i] > max_val) max_val = input[i];
    }

    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        output[i] = expf(input[i] - max_val);  // stabilize
        sum += output[i];
    }

    if (sum < FLT_EPSILON) sum = 1.0f;  // avoid divide-by-zero

    for (int i = 0; i < length; i++) {
        output[i] /= sum;
    }
}

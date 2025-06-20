// ===============================================================
// File: softmax.c — Memory Vector Interface
// Silent Prototype — BuiltByWill
// Phase 5 Upgrade // Morpheus Intelligence Unit
// Purpose: Softmax with internal argmax logic
// Linked to: softmax.h
// ===============================================================

#include <math.h>      // expf
#include <float.h>     // FLT_EPSILON
#include "softmax.h"

// 🔁 Softmax: normalize vector in-place
void softmax(const float* input, float* output, int length) {
    float max_val = input[0];
    for (int i = 1; i < length; i++) {
        if (input[i] > max_val) max_val = input[i];
    }

    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        output[i] = expf(input[i] - max_val);  // stabilized
        sum += output[i];
    }

    if (sum < FLT_EPSILON) sum = 1.0f;

    for (int i = 0; i < length; i++) {
        output[i] /= sum;
    }

    // No return — function matches header signature (void)
}

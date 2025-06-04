// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <math.h>
#include "attention.h"
#include "tokenizer.h"


float dot_product(const float *a, const float *b, int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

float cosine_similarity(const float *a, const float *b, int size) {
    float dot = 0.0f, mag_a = 0.0f, mag_b = 0.0f;

    for (int i = 0; i < size; i++) {
        dot   += a[i] * b[i];
        mag_a += a[i] * a[i];
        mag_b += b[i] * b[i];
    }

    float denom = sqrtf(mag_a) * sqrtf(mag_b);
    return denom != 0 ? dot / denom : 0.0f;
}

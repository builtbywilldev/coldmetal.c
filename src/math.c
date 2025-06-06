// ===============================================================
//  math.c — Coldmetal Internal Arithmetic Engine
// Purpose: Vector operations for memory-based attention systems
// Author: BuiltByWill | Format: Precision-First, Dependency-Free
// ===============================================================

#define _ISOC99_SOURCE
#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <math.h>      // sqrtf, acosf, expf, fabsf
#include <float.h>     // FLT_EPSILON
#include <stdio.h>

#include "../include/attention.h"
#include "../include/memory.h"

// ============================
// 🔢 Vector Math Core
// ============================

float vector_dot(const float *a, const float *b, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; ++i)
        sum += a[i] * b[i];
    return sum;
}

float vector_norm(const float *v, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; ++i)
        sum += v[i] * v[i];
    return sqrtf(sum);
}

void normalize_vector(float *v, int len) {
    float norm = vector_norm(v, len);
    if (norm < FLT_EPSILON) return;
    for (int i = 0; i < len; ++i)
        v[i] /= norm;
}

// ============================
// 📐 Semantic Geometry Tools
// ============================

float cosine_distance(const float *a, const float *b, int len) {
    return 1.0f - cosine_similarity(a, b, len);
}

float euclidean_distance(const float *a, const float *b, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrtf(sum);
}

float scalar_projection(const float *a, const float *b, int len) {
    float norm_b = vector_norm(b, len);
    if (norm_b < FLT_EPSILON) return 0.0f;

    float proj = 0.0f;
    for (int i = 0; i < len; ++i)
        proj += a[i] * (b[i] / norm_b);
    return proj;
}

float angle_between(const float *a, const float *b, int len) {
    float cos_sim = cosine_similarity(a, b, len);
    if (cos_sim < -1.0f) cos_sim = -1.0f;
    if (cos_sim > 1.0f)  cos_sim = 1.0f;
    return acosf(cos_sim);
}

int are_orthogonal(const float *a, const float *b, int len) {
    return fabsf(vector_dot(a, b, len)) < FLT_EPSILON;
}

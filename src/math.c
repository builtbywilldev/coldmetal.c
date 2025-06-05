// ===============================================================
// 🔬 math.c — Coldmetal Internal Arithmetic Engine
// Purpose: Vector operations for memory-based attention systems
// Author: BuiltByWill | Format: Precision-First, Dependency-Free
// ===============================================================
#define _ISOC99_SOURCE
#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <math.h>
#include <float.h>
#include <stdio.h>

// Manual declarations to silence dumb compiler behavior
double sqrt(double);
double acos(double);
double exp(double);
double fabs(double);

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
    return sqrt(sum);
}


float scalar_projection(const float *a, const float *b, int len) {
    float norm_b = vector_norm(b, len);
    if (norm_b < FLT_EPSILON) return 0.0f;

    float unit_b[len];
    for (int i = 0; i < len; ++i)
        unit_b[i] = b[i] / norm_b;

    return vector_dot(a, unit_b, len);
}

float cosine_distance(const float *a, const float *b, int len) {
    return 1.0f - cosine_similarity(a, b, len);
}

float euclidean_distance(const float *a, const float *b, int len) {
    float sum = 0.0f;
    for (int i = 0; i < len; ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

float angle_between(const float *a, const float *b, int len) {
    float cos_sim = cosine_similarity(a, b, len);
    if (cos_sim < -1.0f) cos_sim = -1.0f;
    if (cos_sim > 1.0f) cos_sim = 1.0f;
    return acos(cos_sim);
}

int are_orthogonal(const float *a, const float *b, int len) {
    return fabs(vector_dot(a, b, len)) < FLT_EPSILON;
}

void softmax(const float *input, float *output, int len) {
    float max_val = input[0];
    for (int i = 1; i < len; ++i)
        if (input[i] > max_val)
            max_val = input[i];

    float sum_exp = 0.0f;
    for (int i = 0; i < len; ++i) {
        output[i] = exp(input[i] - max_val);
        sum_exp += output[i];
    }

    if (sum_exp < FLT_EPSILON) sum_exp = 1.0f;
    for (int i = 0; i < len; ++i)
        output[i] /= sum_exp;
}

void normalize_vector(float *v, int len) {
    float norm = vector_norm(v, len);
    if (norm < FLT_EPSILON) return;
    for (int i = 0; i < len; ++i)
        v[i] /= norm;
}

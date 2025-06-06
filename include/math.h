// ===============================================================
// math.h — Vector Math Interface
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef MATH_H
#define MATH_H

// ------------------------
// 🔢 Vector Math Core
// ------------------------
float vector_dot(const float *a, const float *b, int len);
float vector_norm(const float *v, int len);
void  normalize_vector(float *v, int len);

// ------------------------
// 📐 Distance & Geometry
// ------------------------
float cosine_similarity(const float *a, const float *b, int len);
float cosine_distance(const float *a, const float *b, int len);
float euclidean_distance(const float *a, const float *b, int len);
float scalar_projection(const float *a, const float *b, int len);
float angle_between(const float *a, const float *b, int len);
int   are_orthogonal(const float *a, const float *b, int len);

// ------------------------
// 🔥 Probability Mapping
// ------------------------
void softmax(const float *input, float *output, int len);

#endif  // MATH_H

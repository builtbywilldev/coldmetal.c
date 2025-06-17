// ===============================================================
// File: softmax.h — Memory Vector Interface
// Silent Prototype — BuiltByWill
// Phase 4 Artifact // Morpheus Intelligence Unit
// Purpose: Converts raw vectors into probability distributions
// Linked to: softmax.c
// ===============================================================

#ifndef SOFTMAX_H
#define SOFTMAX_H

// 🔥 Softmax Function for Probability Mapping
// Converts raw scores into a stable probability distribution
void softmax(const float* input, float* output, int length);

#endif  // SOFTMAX_H

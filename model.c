// ============================================================
// model.c — Core Weights + Inference
// Silent Prototype — Coldmetal Phase 4
// Author: BuiltByWill | Tactical LLM Systems
// ============================================================

#include "model.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 🔧 Core Weights
float W_q[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_k[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_v[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_out[EMBEDDING_SIZE][EMBEDDING_SIZE];

// ------------------------------------------------------------
// 📦 Load or Randomize Weights
// ------------------------------------------------------------
void load_weights(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        // If not found, initialize small random values
        for (int i = 0; i < EMBEDDING_SIZE; i++) {
            for (int j = 0; j < EMBEDDING_SIZE; j++) {
                W_q[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_k[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_v[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_out[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
            }
        }
        return;
    }

    fread(W_q, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_k, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_v, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_out, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fclose(f);
}

// ------------------------------------------------------------
// 💾 Save Weights
// ------------------------------------------------------------
void save_weights(const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        fprintf(stderr, "[MODEL] Failed to save weights\n");
        return;
    }
    fwrite(W_q, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_k, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_v, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_out, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fclose(f);
}

// ------------------------------------------------------------
// 🚀 Forward Pass (Basic Dense Output)
// ------------------------------------------------------------
float* forward_pass(float *input) {
    float *output = malloc(sizeof(float) * EMBEDDING_SIZE);
    if (!output) {
        fprintf(stderr, "[MODEL] Failed to allocate output vector\n");
        return NULL;
    }

    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        output[i] = 0.0f;
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            output[i] += input[j] * W_out[j][i];  // 🧠 Basic dense multiply
        }
    }

    return output;
}

// ------------------------------------------------------------
// 📉 Compute MSE Loss
// ------------------------------------------------------------
float compute_loss(float *output, float *target) {
    float loss = 0.0f;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        float diff = output[i] - target[i];
        loss += diff * diff;
    }
    return loss / EMBEDDING_SIZE;
}

// ------------------------------------------------------------
// 🧠 Update Weights Based on Loss
// ------------------------------------------------------------
void update_weights(float *input, float *target, float *output, float loss) {
    const float lr = 0.01f;  // 🔧 Learning rate

    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            float grad = 2.0f * (output[j] - target[j]) * input[i];
            W_out[i][j] -= lr * loss * grad;  // 🔥 Scaled by loss
        }
    }
}

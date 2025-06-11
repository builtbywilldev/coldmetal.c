#include "model.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float W_q[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_k[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_v[EMBEDDING_SIZE][EMBEDDING_SIZE];
float W_out[EMBEDDING_SIZE][EMBEDDING_SIZE];

void load_weights(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        // Init randomly
        for (int i = 0; i < EMBEDDING_SIZE; i++)
            for (int j = 0; j < EMBEDDING_SIZE; j++) {
                W_q[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_k[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_v[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
                W_out[i][j] = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;
            }
        return;
    }

    fread(W_q, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_k, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_v, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fread(W_out, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fclose(f);
}

void save_weights(const char *path) {
    FILE *f = fopen(path, "wb");
    fwrite(W_q, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_k, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_v, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fwrite(W_out, sizeof(float), EMBEDDING_SIZE * EMBEDDING_SIZE, f);
    fclose(f);
}

float* forward_pass(float *input) {
    float *output = malloc(sizeof(float) * EMBEDDING_SIZE);
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        output[i] = 0;
        for (int j = 0; j < EMBEDDING_SIZE; j++)
            output[i] += input[j] * W_out[j][i];  // Dumb FF for now
    }
    return output;
}

float compute_loss(float *output, float *target) {
    float loss = 0;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        float diff = output[i] - target[i];
        loss += diff * diff;
    }
    return loss / EMBEDDING_SIZE;
}

void update_weights(float *input, float *target, float *output, float loss) {
    float lr = 0.01f;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            float grad = 2.0f * (output[j] - target[j]) * input[i];
            W_out[i][j] -= lr * loss * grad;  // 🔥 now scales by loss
        }
    }
}


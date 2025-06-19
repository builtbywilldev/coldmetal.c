// ============================================================
// model.h — Coldmetal Learning Core
// Silent Prototype — Phase 4 Intelligence Unit
// Linked to: model.c
// Purpose: Declare model weights and learning functions
// ============================================================

#ifndef MODEL_H
#define MODEL_H

#include "config.h"  // for EMBEDDING_SIZE

// 🔗 Weight Matrices (shared across model.c)
extern float W_q[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_k[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_v[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_out[EMBEDDING_SIZE][EMBEDDING_SIZE];

// 🧠 Core Functions
float* forward_pass(float *input);
float compute_loss(float *output, float *target);
void  update_weights(float *input, float *target, float *output, float loss);

// 💾 I/O Operations
void  save_weights(const char *path);
void  load_weights(const char *path);

#endif // MODEL_H

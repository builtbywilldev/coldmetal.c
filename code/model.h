// model.h — Coldmetal Learning Core
#ifndef MODEL_H
#define MODEL_H

#include "config.h"  // for EMBEDDING_SIZE

extern float W_q[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_k[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_v[EMBEDDING_SIZE][EMBEDDING_SIZE];
extern float W_out[EMBEDDING_SIZE][EMBEDDING_SIZE];

float* forward_pass(float *input);
float compute_loss(float *output, float *target);
void update_weights(float *input, float *target, float *output, float loss);

void save_weights(const char *path);
void load_weights(const char *path);

#endif

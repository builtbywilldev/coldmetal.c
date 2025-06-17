// ===============================================================
// File: embedder.h
// Coldmetal Phase: 4
// Purpose: Header for symbolic embedding functions used across Coldmetal
// Linked to: embedder.c, config.h, math.c
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================


#ifndef EMBEDDER_H
#define EMBEDDER_H

#include "config.h"

// Embeds a single token into a fixed-size float vector
void embed_token(const char *token, float *vector);

// Embeds a full sentence by averaging token embeddings
void embed_text(const char *text, float *out_vector);

// Optional: Normalize a vector (from math.c)
void normalize_vector(float *v, int len);

#endif  // EMBEDDER_H

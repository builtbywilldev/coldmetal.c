// ===============================================================
// embedder.c Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#define _ISOC99_SOURCE

#include <math.h>     // sqrtf
#include <stdio.h>
#include <float.h>    // FLT_EPSILON

#include "../include/tokenizer.h"
#include "../include/attention.h"
#include "../include/memory.h"

// ---------------------------------------------------------------
// Hash-based token embedding: maps a token to a signed float vector
// ---------------------------------------------------------------
void embed_token(const char *token, float *vector) {
    unsigned int hash = 5381;
    while (*token) {
        hash = ((hash << 5) + hash) + (unsigned char)(*token++);
    }

    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        vector[i] = ((hash >> i) & 1) ? 1.0f : -1.0f;
    }
}

// ---------------------------------------------------------------
// Embed a full text string by averaging embedded token vectors
// ---------------------------------------------------------------
void embed_text(const char *text, float *out_vector) {
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int count;

    tokenize(text, tokens, &count);

    // Initialize output vector
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        out_vector[i] = 0.0f;
    }

    // Accumulate token embeddings
    for (int i = 0; i < count; i++) {
        float temp[EMBEDDING_SIZE];
        embed_token(tokens[i], temp);

        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            out_vector[j] += temp[j];
        }
    }

    // Normalize the final vector
    float norm = 0.0f;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        norm += out_vector[i] * out_vector[i];
    }

    norm = sqrtf(norm);

    if (norm > FLT_EPSILON) {
        for (int i = 0; i < EMBEDDING_SIZE; i++) {
            out_vector[i] /= norm;
        }
    }
}

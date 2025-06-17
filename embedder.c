// ===============================================================
// File: embedder.c
// Coldmetal Phase: 4
// Purpose: Embed input strings into normalized float vectors via deterministic token hashing
// Linked to: tokenizer.h, attention.h, memory.h, math.h
// Notes: Uses hash-based embedding for symbolic understanding (no ML weights)
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================


#include <math.h>     // sqrtf
#include <stdio.h>
#include <float.h>    // FLT_EPSILON

#include "tokenizer.h"
#include "attention.h"
#include "memory.h"
#include "math.h" // Required for vector_norm() and normalize_vector()

// ---------------------------------------------------------------
// Maps a token to a signed float vector via bitwise hashing
// ---------------------------------------------------------------
void embed_token(const char *token, float *vector) {
    unsigned int hash = 5381;
    while (*token) {
        hash = ((hash << 5) + hash) + (unsigned char)(*token++); // djb2 hash
    }

    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        vector[i] = ((hash >> i) & 1) ? 1.0f : -1.0f;
    }
}

// ---------------------------------------------------------------
// Embeds a full string by averaging hashed token embeddings
// ---------------------------------------------------------------
void embed_text(const char *text, float *out_vector) {
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int count;

    tokenize(text, tokens, &count);

    // Initialize embedding
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        out_vector[i] = 0.0f;
    }

    // Accumulate token vectors
    for (int i = 0; i < count; i++) {
        float temp[EMBEDDING_SIZE];
        embed_token(tokens[i], temp);

        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            out_vector[j] += temp[j];
        }
    }

    // Normalize result vector to unit length
    float norm = vector_norm(out_vector, EMBEDDING_SIZE);
    if (norm > FLT_EPSILON) {
        normalize_vector(out_vector, EMBEDDING_SIZE);
    }
}

// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <string.h>
#include <stdlib.h>
#include "embedder.h"
#include "tokenizer.h"
#include <math.h>

// Simple hash function to embed a token into a float vector
void embed_token(const char *token, float *vector) {
    unsigned int hash = 5381;
    while (*token) {
        hash = ((hash << 5) + hash) + (unsigned char)(*token++);
    }

    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        vector[i] = ((hash >> i) & 1) ? 1.0f : -1.0f;
    }
}

// Embed a full sentence by averaging token vectors
void embed_text(const char *text, float *out_vector) {
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int count;
tokenize(text, tokens, &count);


    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        out_vector[i] = 0.0f;
    }

    for (int i = 0; i < count; i++) {
        float temp[EMBEDDING_SIZE];
        embed_token(tokens[i], temp);

        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            out_vector[j] += temp[j];
        }
    }

    // Normalize the vector
    float norm = 0.0f;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        norm += out_vector[i] * out_vector[i];
    }
    norm = sqrtf(norm);
    if (norm > 0) {
        for (int i = 0; i < EMBEDDING_SIZE; i++) {
            out_vector[i] /= norm;
        }
    }
}

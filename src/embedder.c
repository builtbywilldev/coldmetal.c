// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <string.h>
#include <stdlib.h>
#include "embedder.h"  
#include "tokenizer.h"

// Hash-based fake embedder
void embed_token(const char *token, float *vector) {
    unsigned int seed = 0;
    for (int i = 0; token[i] != '\0'; i++) {
        seed = seed * 31 + token[i];
    }

    srand(seed);  // deterministic per token
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        vector[i] = (float)(rand() % 1000) / 1000.0f;
    }
}

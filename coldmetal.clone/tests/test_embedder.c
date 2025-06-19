// ===============================================================
// 🔮 Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include "embedder.h"

int main() {
    const char *tokens[] = {"hello", "world", "iron", "man"};
    const int num_tokens = sizeof(tokens) / sizeof(tokens[0]);

    for (int i = 0; i < num_tokens; i++) {
        float vector[EMBEDDING_SIZE];
        embed_token(tokens[i], vector);

        printf("%s → [", tokens[i]);
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            printf("%.3f", vector[j]);
            if (j < EMBEDDING_SIZE - 1) printf(", ");
        }
        printf("]\n");
    }

    return 0;
}

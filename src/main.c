// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include <string.h>

#include "tokenizer.h"
#include "embedder.h"
#include "attention.h"
#include "memory.h"

#define MEMORY_PATH "data/morpheus.mem"

extern int memory_count;
extern MemoryItem memory[];

int main() {
    load_memory(MEMORY_PATH);

    char input[256];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens;

    printf("Morpheus Booted. Type something:\n");

    while (1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);

        if (strncmp(input, "exit", 4) == 0) break;

        input[strcspn(input, "\n")] = '\0';  // Strip newline
        remember(input);  // Store user input

        tokenize(input, tokens, &num_tokens);

        float input_vec[EMBEDDING_SIZE];
        embed_token(tokens[0], input_vec);  // Embed first token (simple heuristic)

        float best_score = 0.0f;
        const char* best_match = "I'm not sure what to say yet.";

        for (int i = 0; i < memory_count; i++) {
            float memory_vec[EMBEDDING_SIZE];
            embed_token(memory[i].content, memory_vec);

            float score = cosine_similarity(input_vec, memory_vec, EMBEDDING_SIZE);
            if (score > best_score) {
                best_score = score;
                best_match = memory[i].content;
            }
        }

        remember(best_match);  // Store response
        printf("Morpheus: %s\n", best_match);
    }

    save_memory(MEMORY_PATH);
    return 0;
}

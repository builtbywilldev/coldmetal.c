// ===============================================================
// main.c — Morpheus Terminal REPL
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tokenizer.h"
#include "embedder.h"
#include "attention.h"
#include "memory.h"

#define MEMORY_PATH "data/.mem/morpheus.mem"

int main() {
    srand(time(NULL));  // 🔑 Seed RNG
    load_all_memories(); // 📥 Load all memory files

    char input[256];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens;
    int last_response_index = -1;

    printf("Morpheus: Online. Input your thought:\n");

    while (1) {
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        if (strncmp(input, "exit", 4) == 0) break;
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) < 2) continue;

        tokenize(input, tokens, &num_tokens);

        float input_vec[EMBEDDING_SIZE] = {0.0f};
        for (int i = 0; i < num_tokens; i++) {
            float temp[EMBEDDING_SIZE];
            embed_token(tokens[i], temp);
            for (int j = 0; j < EMBEDDING_SIZE; j++)
                input_vec[j] += temp[j];
        }
        for (int j = 0; j < EMBEDDING_SIZE; j++)
            input_vec[j] /= (float)num_tokens;

        normalize_vector(input_vec, EMBEDDING_SIZE);

        float best_score = -1.0f;
        int best_index = -1;

        for (int i = 0; i < memory_count_items(); i++) {
            const char *mem_text = memory_get_text(i);
            if (strcmp(input, mem_text) == 0) continue;

            float *mem_vec = memory_get_vector(i);

            float mem_copy[EMBEDDING_SIZE];
            memcpy(mem_copy, mem_vec, sizeof(float) * EMBEDDING_SIZE);
            normalize_vector(mem_copy, EMBEDDING_SIZE);

            float score = cosine_similarity(input_vec, mem_copy, EMBEDDING_SIZE);

            if (score > best_score) {
                best_score = score;
                best_index = i;
            }
        }

        const char *response = NULL;

        if (best_index == -1 || best_score < 0.50f) {
            const char *fallbacks[] = {
                "I'm still learning.",
                "Try rephrasing that.",
                "Can't match that yet.",
                "Tell me more.",
                "Not sure how to respond to that."
            };
            response = fallbacks[rand() % 5];
        } else if (best_score > 0.96f && best_index != last_response_index) {
            response = memory_get_text(best_index);
            last_response_index = best_index;
        } else if (best_score > 0.75f) {
            const char *ack[] = {
                "Related thought:",
                "This comes to mind:",
                "Closest match I found:"
            };
            printf("Morpheus: %s %s\n", ack[rand() % 3], memory_get_text(best_index));
            remember(input);
            continue;
        } else {
            const char *soft_fallbacks[] = {
                "Interesting.",
                "Noted.",
                "Hmm.",
                "Logging that.",
                "Understood."
            };
            response = soft_fallbacks[rand() % 5];
        }

        remember(input);
        remember(response);
        printf("Morpheus: %s\n", response);
    }

    save_memory(MEMORY_PATH);
    return 0;
}

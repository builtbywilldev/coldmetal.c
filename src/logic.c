// ===============================================================
// logic.c Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#define _ISOC99_SOURCE

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "../include/tokenizer.h"
#include "../include/attention.h"
#include "../include/embedder.h"
#include "../include/memory.h"
#include "../include/logic.h"

// ---------------------------------------------------------------
// Generates a response by embedding input tokens and scanning memory
// ---------------------------------------------------------------
const char* generate_response(char tokens[][MAX_TOKEN_LEN], int num_tokens) {
    float input_vec[EMBEDDING_SIZE] = {0.0f};

    // === [1] Embed input tokens into a single vector ===
    for (int i = 0; i < num_tokens; i++) {
        float temp_vec[EMBEDDING_SIZE];
        embed_token(tokens[i], temp_vec);
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            input_vec[j] += temp_vec[j];
        }
    }

    for (int j = 0; j < EMBEDDING_SIZE; j++) {
        input_vec[j] /= (float)num_tokens;
    }

    normalize_vector(input_vec, EMBEDDING_SIZE);

    // === [2] Search memory for best cosine similarity match ===
    int mem_count = memory_count_items();
    float best_score = -1.0f;
    int best_index = -1;
    float scores[mem_count];

    for (int i = 0; i < mem_count; i++) {
        float* mem_vec = memory_get_vector(i);
        normalize_vector(mem_vec, EMBEDDING_SIZE);

        float score = cosine_similarity(input_vec, mem_vec, EMBEDDING_SIZE);
        scores[i] = score;

        if (score > best_score) {
            best_score = score;
            best_index = i;
        }
    }

    // === [3] Echo suppression ===
    if (best_score > 0.99f) {
        return "You've already said that. Ask me something new.";
    }

    // === [4] Softmax logic (future blending support) ===
    float softmaxed[mem_count];
    softmax(scores, softmaxed, mem_count);

    // === [5] Respond based on confidence ===
    if (best_score > 0.85f && best_index >= 0) {
        return memory_get_text(best_index);
    }

    // === [6] Fallback if no strong match ===
    return "I don't recognize that yet, but I'm learning.";
}

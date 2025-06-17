// ===============================================================
// File: logic.c
// Coldmetal Phase: 4
// Purpose: Semantic response engine using memory scoring
// Linked to: tokenizer.h, memory.h, embedder.h, attention.h, softmax.h
// Silent Prototype — BuiltByWill
// Tactical Intelligence Unit // Morpheus Artifact
// ===============================================================

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>  // ✅ For rand() and RAND_MAX
#include <math.h>

#include "tokenizer.h"
#include "attention.h"
#include "embedder.h"
#include "memory.h"
#include "logic.h"
#include "softmax.h"

const char* generate_response(char tokens[][MAX_TOKEN_LEN], int num_tokens) {
    float input_vec[EMBEDDING_SIZE] = {0.0f};

    // [1] Embed + Normalize Input Vector
    for (int i = 0; i < num_tokens; i++) {
        float temp[EMBEDDING_SIZE];
        embed_token(tokens[i], temp);
        for (int j = 0; j < EMBEDDING_SIZE; j++) {
            input_vec[j] += temp[j];
        }
    }
    for (int j = 0; j < EMBEDDING_SIZE; j++) {
        input_vec[j] /= (float)num_tokens;
    }
    normalize_vector(input_vec, EMBEDDING_SIZE);

    // [2] Score All Memories
    int mem_count = memory_count_items();
    float scores[mem_count];
    float best_score = -1.0f;
    int best_index = -1;

    for (int i = 0; i < mem_count; i++) {
        float vec[EMBEDDING_SIZE];
        memcpy(vec, memory_get_vector(i), sizeof(vec));
        normalize_vector(vec, EMBEDDING_SIZE);

        float sim = cosine_similarity(input_vec, vec, EMBEDDING_SIZE);
        float val = memory_get_value(i);
        float score = sim * (0.8f + 0.2f * fminf(val, 5.0f));
        scores[i] = score;

        if (score > best_score) {
            best_score = score;
            best_index = i;
        }
    }

    const char* match = memory_get_text(best_index);
    if (best_score > 0.97f && match && strstr(match, tokens[0])) {
        return "🌀 Repetition detected. Let’s evolve this idea.";
    }

    float softmaxed[mem_count];
    softmax(scores, softmaxed, mem_count);

    // [3] High-Confidence Direct Recall
    if (best_score > 0.88f && best_index >= 0) {
        score_memory(best_index, 0.2f);
        return memory_get_text(best_index);
    }

    // [4] Mid-Confidence: Top-K Sampling
    if (best_score > 0.6f) {
        int top_k = 3;
        int indices[top_k];
        float probs[top_k];

        for (int i = 0; i < top_k; i++) {
            float max = -1.0f;
            int max_idx = -1;
            for (int j = 0; j < mem_count; j++) {
                int skip = 0;
                for (int k = 0; k < i; k++) {
                    if (indices[k] == j) skip = 1;
                }
                if (!skip && softmaxed[j] > max) {
                    max = softmaxed[j];
                    max_idx = j;
                }
            }
            indices[i] = max_idx;
            probs[i] = softmaxed[max_idx];
        }

        float r = (float)rand() / (float)RAND_MAX;
        float accum = 0.0f;
        for (int i = 0; i < top_k; i++) {
            accum += probs[i];
            if (r <= accum) {
                score_memory(indices[i], 0.1f);
                return memory_get_text(indices[i]);
            }
        }
        return memory_get_text(indices[0]);
    }

    // [5] Low-Confidence: Reflection
    if (best_score > 0.4f) {
        static char buffer[MAX_MEMORY_LEN + 64];
        snprintf(buffer, sizeof(buffer), "Closest I found: \"%s\"", match);
        return buffer;
    }

    // [6] No Match: Passive Acknowledgment
    return "I don't recognize that yet — but I'm listening.";
}

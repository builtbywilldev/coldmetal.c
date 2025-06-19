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
    static char buffer[MAX_MEMORY_LEN + 128];

    // [0] Handle minting mode
    if (num_tokens == 1 && strcmp(tokens[0], "::mint") == 0) {
        int best_index = 0;
        float highest_val = 0.0f;
        for (int i = 0; i < memory_count_items(); i++) {
            float val = memory_get_value(i);
            if (val > highest_val) {
                highest_val = val;
                best_index = i;
            }
        }
        snprintf(buffer, sizeof(buffer),
            "{ \"minted\": \"%s\", \"value\": %.2f }",
            memory_get_text(best_index), highest_val);
        return buffer;
    }

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
    if (mem_count == 0) {
        snprintf(buffer, sizeof(buffer),
            "{ \"text\": \"No memories yet.\", \"score\": 0.0, \"new\": true }");
        return buffer;
    }

    float scores[mem_count];
    float best_score = -1.0f;
    int best_index = -1;

    for (int i = 0; i < mem_count; i++) {
        float vec[EMBEDDING_SIZE];
        memcpy(vec, memory_get_vector(i), sizeof(vec));
        normalize_vector(vec, EMBEDDING_SIZE);

        float sim = cosine_similarity(input_vec, vec, EMBEDDING_SIZE);
        float val = memory_get_value(i);
        float score = sim * logf(1.0f + val);  // COLD SCALING LOGIC
        scores[i] = score;

        if (score > best_score) {
            best_score = score;
            best_index = i;
        }
    }

    const char* match = memory_get_text(best_index);
    if (best_score > 0.97f && match && strstr(match, tokens[0])) {
        snprintf(buffer, sizeof(buffer),
            "{ \"text\": \"🌀 Repetition detected. Let’s evolve this idea.\", \"score\": %.2f, \"new\": true }",
            best_score);
        return buffer;
    }

    float softmaxed[mem_count];
    softmax(scores, softmaxed, mem_count);

    // [3] High-Confidence Direct Recall
    if (best_score > 0.88f && best_index >= 0) {
        score_memory(best_index, 0.2f);
        snprintf(buffer, sizeof(buffer),
            "{ \"text\": \"%s\", \"score\": %.2f, \"new\": false }",
            memory_get_text(best_index), best_score);
        return buffer;
    }

    // [4] Mid-Confidence: Top-K Sampling
    if (best_score > 0.4f) {
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
                snprintf(buffer, sizeof(buffer),
                    "{ \"text\": \"%s\", \"score\": %.2f, \"new\": false }",
                    memory_get_text(indices[i]), best_score);
                return buffer;
            }
        }
        snprintf(buffer, sizeof(buffer),
            "{ \"text\": \"%s\", \"score\": %.2f, \"new\": false }",
            memory_get_text(indices[0]), best_score);
        return buffer;
    }

    // [5] Low-Confidence: Reflection
    if (best_score > 0.1f) {
        snprintf(buffer, sizeof(buffer),
            "{ \"text\": \"Closest I found: %s\", \"score\": %.2f, \"new\": true }",
            match ? match : "none", best_score);
        return buffer;
    }

    // [6] No Match: Passive Acknowledgment
    snprintf(buffer, sizeof(buffer),
        "{ \"text\": \"I don't recognize that yet — but I'm listening.\", \"score\": 0.0, \"new\": true }");
    return buffer;
}

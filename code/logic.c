// ===============================================================
// logic.c — Semantic Response Generator
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "tokenizer.h"
#include "attention.h"
#include "embedder.h"
#include "memory.h"
#include "logic.h"
#include "softmax.h"

// ---------------------------------------------------------------
// 🧠 Advanced Weighted Semantic Matching + $COLD Boost
// ---------------------------------------------------------------
const char* generate_response(char tokens[][MAX_TOKEN_LEN], int num_tokens) {
    float input_vec[EMBEDDING_SIZE] = {0.0f};

    // === [1] Embed + Normalize Input Vector ===
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

    // === [2] Scan Memory and Score ===
    int mem_count = memory_count_items();
    float best_score = -1.0f;
    int best_index = -1;
    float scores[mem_count];

    for (int i = 0; i < mem_count; i++) {
        float* mem_vec = memory_get_vector(i);
        float mem_copy[EMBEDDING_SIZE];
        memcpy(mem_copy, mem_vec, sizeof(float) * EMBEDDING_SIZE);
        normalize_vector(mem_copy, EMBEDDING_SIZE);

        float similarity = cosine_similarity(input_vec, mem_copy, EMBEDDING_SIZE);
        float value = memory_get_value(i);
        float boosted = similarity * (0.8f + 0.2f * fminf(value, 5.0f));  // ⬅️ Cap $COLD weight to prevent overfitting

        scores[i] = boosted;

        if (boosted > best_score) {
            best_score = boosted;
            best_index = i;
        }
    }

    // === [3] Echo Filter ===
    const char* matched = memory_get_text(best_index);
    if (best_score > 0.97f && matched != NULL && strstr(matched, tokens[0])) {
        return "🌀 Repetition detected. Let’s evolve this idea.";
    }

    // === [4] Softmax Vector (Optional Preview) ===
    float softmaxed[mem_count];
    softmax(scores, softmaxed, mem_count);

    // === [5] High-Confidence Direct Recall ===
    if (best_score > 0.88f && best_index >= 0) {
        score_memory(best_index, 0.2f);  // Auto-reward for triggering memory
        return memory_get_text(best_index);
    }

    // === [6] Mid-Confidence Thought Reflection ===
    if (best_score > 0.75f && best_index >= 0) {
        static char buffer[MAX_MEMORY_LEN + 64];
        snprintf(buffer, sizeof(buffer), "Closest I found: \"%s\"", memory_get_text(best_index));
        score_memory(best_index, 0.1f);
        return buffer;
    }

    // === [7] Unknown Recall: Echo the vibe back ===
    return "I don't recognize that yet — but I'm listening.";
}

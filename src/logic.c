// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <string.h>
#include <ctype.h>
#include "logic.h"
#include "embedder.h"
#include "attention.h"
#include "tokenizer.h"


const char* generate_response(char tokens[][MAX_TOKEN_LEN], int num_tokens) {
    const char* known_phrases[] = {"hello", "hi", "greetings"};
    const char* replies[] = {
        "Hello, Operator.",
        "Hi there.",
        "Coldmetal online."
    };

    int phrase_count = sizeof(known_phrases) / sizeof(known_phrases[0]);
    float input_vec[EMBEDDING_SIZE];
    float greeting_vec[EMBEDDING_SIZE];

    for (int i = 0; i < num_tokens; i++) {
        embed_token(tokens[i], input_vec);

        for (int j = 0; j < phrase_count; j++) {
            embed_token(known_phrases[j], greeting_vec);
            float similarity = cosine_similarity(input_vec, greeting_vec, EMBEDDING_SIZE);

            if (similarity > 0.90f) {
                return replies[j];
            }
        }
    }

    return "I'm not sure what to say yet.";
}

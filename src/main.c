// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#include "tokenizer.h"
#include "embedder.h"
#include "attention.h"
#include "memory.h"
#include "math.h"

#define MEMORY_PATH "data/.mem/morpheus.mem"

int main()
{
    srand(time(NULL));   // 🔑 Seed random number generator
    load_all_memories(); // loads all .mem files from data/.mem/

    char input[256];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens;
    int last_index = -1;  // 🧠 Memory index buffer to avoid repeats

    printf("Morpheus Booted. Type something:\n");

    while (1)
    {
        printf(">> ");
        fgets(input, sizeof(input), stdin);

        if (strncmp(input, "exit", 4) == 0)
            break;

        input[strcspn(input, "\n")] = '\0'; // Strip newline
        remember(input);                    // Store user input

        // === Tokenize + Embed entire sentence ===
        tokenize(input, tokens, &num_tokens);

        float input_vec[EMBEDDING_SIZE] = {0};

        for (int i = 0; i < num_tokens; i++)
        {
            float temp[EMBEDDING_SIZE];
            embed_token(tokens[i], temp);
            for (int j = 0; j < EMBEDDING_SIZE; j++)
            {
                input_vec[j] += temp[j];
            }
        }

        for (int j = 0; j < EMBEDDING_SIZE; j++)
            input_vec[j] /= (float)num_tokens;

        normalize_vector(input_vec, EMBEDDING_SIZE);

        // === Score all memory entries ===
        float best_score = -1.0f;
        int best_index = -1;

        for (int i = 0; i < memory_count_items(); i++)
        {
            float *mem_vec = memory_get_vector(i);
            normalize_vector(mem_vec, EMBEDDING_SIZE);
            float score = cosine_similarity(input_vec, mem_vec, EMBEDDING_SIZE);

            if (score > best_score)
            {
                best_score = score;
                best_index = i;
            }
        }

        const char *response = "I'm not sure what to say yet.";

        if (best_index >= 0)
        {
            if (best_score > 0.96f)
            {
                // 🧠 Don't return the same line over and over
                int rand_index;
                do {
                    rand_index = rand() % memory_count_items();
                } while (rand_index == last_index);

                response = memory_get_text(rand_index);
                last_index = rand_index;
            }
            else if (best_score > 0.75f)
            {
                response = memory_get_text(best_index);
                last_index = best_index;
            }
            else
            {
                const char *unknown_responses[] = {
                    "That’s above my clearance.",
                    "I’m logging that for review.",
                    "Say more.",
                    "Hmmm. That’s different.",
                    "Not sure yet, but I’m learning."
                };
                response = unknown_responses[rand() % 5];
                last_index = -1; // Reset since it's not a memory line
            }
        }

        remember(response); // Store response
        printf("Morpheus: %s\n", response);
    }

    save_memory(MEMORY_PATH);
    return 0;
}

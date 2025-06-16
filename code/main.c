// ===============================================================
// main.c — Morpheus Terminal REPL (Coldmetal Upgrade)
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
#include "logic.h"

#define MEMORY_PATH "data/.mem/morpheus.mem"

int main()
{
    srand(time(NULL));   // 🔑 Seed RNG
    load_all_memories(); // 📅 Load all memory files

    char input[256];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens;

    printf("\n");
    printf("=========================================\n");
    printf("Morpheus: Coldmetal Core Online [BOOT OK]\n");
    printf("Tip with: tip [index] [amount]\n");
    printf("Peek with: peek or peek [index]\n");
    printf("Exit with: exit\n");
    printf("=========================================\n\n");

    while (1)
    {
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) < 2)
            continue;

        // === Command: Exit ===
        if (strncmp(input, "exit", 4) == 0)
            break;

        // === Command: Tip ===
        if (strncmp(input, "tip", 3) == 0)
        {
            int index;
            float delta;
            if (sscanf(input, "tip %d %f", &index, &delta) == 2)
            {
                score_memory(index, delta);
                printf("$$ Memory %d tipped with %.2f $COLD\n", index, delta);
            }
            else
            {
                printf("$$$ Usage: tip [index] [amount]\n");
            }
            continue;
        }

        // === Command: Peek ===
        if (strncmp(input, "peek", 4) == 0)
        {
            int index;
            if (sscanf(input, "peek %d", &index) == 1)
            {
                if (index >= 0 && index < memory_count_items())
                {
                    const char *text = memory_get_text(index);
                    float value = memory_get_value(index);
                    char type = text[0]; // Crude fallback, ideally use memory_get_type(index)
                    printf("[%d] (%c) %.2f $COLD → %s\n", index, type, value, text);
                }
                else
                {
                    printf("⚠️ Invalid memory index.\n");
                }
            }
            else
            {
                print_memory();
            }
            continue;
        }

        // === Normal Input: Tokenize + Respond ===
        tokenize(input, tokens, &num_tokens);
        const char *response = generate_response(tokens, num_tokens);

        remember_with_type(input, 'U');
        remember_with_type(response, 'A');

        printf("Morpheus: %s\n", response);
    }

    save_memory(MEMORY_PATH);
    return 0;
}

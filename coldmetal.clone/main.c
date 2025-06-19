// ===============================================================
// File: main.c
// Coldmetal Phase: 4.3
// Purpose: Terminal REPL for Morpheus (Coldmetal Core) with memory scoring, token minting, and response handling.
// Linked to: tokenizer.c, embedder.c, attention.c, memory.c, mint.c, logic.c
// Silent Prototype — BuiltByWill
// Tactical Intelligence Unit // Morpheus Artifact
// ===============================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h> // For access()

#include "tokenizer.h"
#include "embedder.h"
#include "attention.h"
#include "memory.h"
#include "logic.h"
#include "mint.h"
#include "config.h"

#define MEMORY_PATH "data/.mem/morpheus.mem"

int main() {
    srand(time(NULL));

    if (access(MEMORY_PATH, F_OK) != 0) {
        printf("⚠️  Warning: memory file not found (%s)\n", MEMORY_PATH);
    }

    load_all_memories();

    char input[256];
    char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    int num_tokens;

    printf("\n");
    printf("=========================================\n");
    printf("Morpheus: Coldmetal Core Online [BOOT OK]\n");
    printf("Tip with: tip [index] [amount]\n");
    printf("Peek with: peek or peek [index]\n");
    printf("Mint with: mint [index]\n");
    printf("Score with: score [index]\n");
    printf("Exit with: exit\n");
    printf("=========================================\n\n");

    while (1) {
        printf(">> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) < 2) continue;

        if (strncmp(input, "exit", 4) == 0) break;

        if (strncmp(input, "tip", 3) == 0) {
            int index;
            float delta;
            if (sscanf(input, "tip %d %f", &index, &delta) == 2) {
                score_memory(index, delta);
                printf("$$ Memory %d tipped with %.2f $COLD\n", index, delta);
                save_memory(MEMORY_PATH);  // ✅ Save right after tipping
            } else {
                printf("$$$ Usage: tip [index] [amount]\n");
            }
            continue;
        }

        if (strncmp(input, "score", 5) == 0) {
            int index;
            if (sscanf(input, "score %d", &index) == 1) {
                float val = memory_get_value(index);
                printf("💰 Memory %d has %.2f $COLD\n", index, val);
            } else {
                printf("Usage: score [index]\n");
            }
            continue;
        }

        if (strncmp(input, "peek", 4) == 0) {
            int index;
            if (sscanf(input, "peek %d", &index) == 1) {
                if (index >= 0 && index < memory_count_items()) {
                    const char *text = memory_get_text(index);
                    float value = memory_get_value(index);
                    char type = memory_get_type(index);  // ✅ Replace fallback
                    printf("[%d] (%c) %.2f $COLD → %s\n", index, type, value, text);
                } else {
                    printf("⚠️ Invalid memory index.\n");
                }
            } else {
                print_memory();
            }
            continue;
        }

        if (strncmp(input, "mint", 4) == 0) {
            int index;
            if (sscanf(input, "mint %d", &index) == 1) {
                mint_from_mem(index);
            } else {
                printf("Usage: mint [index]\n");
            }
            continue;
        }

        tokenize(input, tokens, &num_tokens);
        const char *response = generate_response(tokens, num_tokens);

        remember_with_type(input, 'U');
        remember_with_type(response, 'A');

        save_memory(MEMORY_PATH);  // ✅ Save every loop

        printf("Morpheus: %s\n", response);
    }

    save_memory(MEMORY_PATH);  // Final save just in case
    return 0;
}

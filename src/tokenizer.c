// ===============================================================
// tokenizer.c — Lexical Token Filter for Semantic Embedding
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <ctype.h>
#include <string.h>

#include "../include/tokenizer.h"
#include "../include/memory.h"

// ---------------------------------------------------------------
// ⛓️ Token Boundary Logic — Preserves apostrophes like "don't"
// ---------------------------------------------------------------
int is_boundary(char c) {
    return isspace(c) || (ispunct(c) && c != '\'');
}

// ---------------------------------------------------------------
// 🪓 Tokenizer — Cleans input into lowercase semantic tokens
// Filters out:
///   - meaningless single-letter junk (except 'i' and 'a')
///   - punctuation (except apostrophes)
/// Outputs:
///   - `tokens` array (MAX_TOKENS x MAX_TOKEN_LEN)
///   - `num_tokens` count
// ---------------------------------------------------------------
void tokenize(const char *input, char tokens[][MAX_TOKEN_LEN], int *num_tokens) {
    int i = 0, t = 0, j = 0;
    char token[MAX_TOKEN_LEN];

    while (input[i] != '\0') {
        char c = input[i];

        if (is_boundary(c)) {
            if (j > 0) {
                token[j] = '\0';

                // Only allow single letters 'a' and 'i' to survive
                if (!(strlen(token) == 1 && token[0] != 'i' && token[0] != 'a')) {
                    strncpy(tokens[t], token, MAX_TOKEN_LEN);
                    tokens[t][MAX_TOKEN_LEN - 1] = '\0';
                    t++;
                    if (t >= MAX_TOKENS) break;
                }

                j = 0;
            }
        } else {
            if (j < MAX_TOKEN_LEN - 1) {
                token[j++] = tolower(c);  // Normalize: lowercase
            }
        }

        i++;
    }

    // Flush final token
    if (j > 0 && t < MAX_TOKENS) {
        token[j] = '\0';
        strncpy(tokens[t], token, MAX_TOKEN_LEN);
        tokens[t][MAX_TOKEN_LEN - 1] = '\0';
        t++;
    }

    *num_tokens = t;
}

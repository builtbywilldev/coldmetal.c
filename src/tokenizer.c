// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#include <ctype.h>
#include <string.h>
#include "tokenizer.h"

int is_boundary(char c) {
    return isspace(c) || (ispunct(c) && c != '\''); // keep apostrophes
}

void tokenize(const char *input, char tokens[][MAX_TOKEN_LEN], int *num_tokens) {
    int i = 0, t = 0, j = 0;
    char token[MAX_TOKEN_LEN];

    while (input[i] != '\0') {
        char c = input[i];

        if (is_boundary(c)) {
            if (j > 0) {
                token[j] = '\0';

                // filter single-letter tokens except 'i' or 'a'
                if (!(strlen(token) == 1 && token[0] != 'i' && token[0] != 'a')) {
                    strncpy(tokens[t], token, MAX_TOKEN_LEN);
                    tokens[t][MAX_TOKEN_LEN - 1] = '\0';
                    t++;
                }

                j = 0;
            }
            i++;
        } else {
            if (j < MAX_TOKEN_LEN - 1) {
                token[j++] = tolower(c);  // force lowercase
            }
            i++;
        }
    }

    if (j > 0) {
        token[j] = '\0';
        strncpy(tokens[t], token, MAX_TOKEN_LEN);
        tokens[t][MAX_TOKEN_LEN - 1] = '\0';
        t++;
    }

    *num_tokens = t;
}

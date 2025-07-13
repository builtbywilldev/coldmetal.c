// ===============================================================
// File: tokenizer.c
// Coldmetal Phase: 5
// Purpose: Upgraded lexical tokenizer with suffix splitting and phrase compression
// Linked to: memory.h, tokenizer.h
// Author: BuiltByWill — Silent Prototype Labs
// ===============================================================

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

#define PHRASE_COUNT 4
const char *phrases[PHRASE_COUNT][2] = {
    {"united states", "__us__"},
    {"artificial intelligence", "__ai__"},
    {"machine learning", "__ml__"},
    {"project gutenberg", "__pg__"}
};

// 🔁 Check if word ends with suffix
int ends_with(const char *word, const char *suffix) {
    size_t len_word = strlen(word);
    size_t len_suffix = strlen(suffix);
    if (len_word < len_suffix) return 0;
    return strcmp(word + len_word - len_suffix, suffix) == 0;
}

// ✂️ Replace known phrases in-place
void replace_phrases(char *input, size_t max_len) {
    char buffer[1024];
    strcpy(buffer, input);
    for (int i = 0; i < PHRASE_COUNT; i++) {
        char *pos = strstr(buffer, phrases[i][0]);
        if (pos) {
            buffer[0] = '\0';
            strcat(buffer, phrases[i][1]);
            strcat(buffer, pos + strlen(phrases[i][0]));
            strncpy(input, buffer, max_len);
            input[max_len - 1] = '\0';
        }
    }
}

// 🪓 Tokenizer — Strips junk, applies phrase map, splits suffixes
void tokenize(const char *input_raw, char tokens[][MAX_TOKEN_LEN], int *num_tokens) {
    char input[1024];
    strncpy(input, input_raw, sizeof(input));
    input[sizeof(input) - 1] = '\0';

    replace_phrases(input, sizeof(input));

    int i = 0, t = 0, j = 0;
    char token[MAX_TOKEN_LEN];

    while (input[i] != '\0') {
        char c = input[i];

        if (isspace(c) || (ispunct(c) && c != '\'')) {
            if (j > 0) {
                token[j] = '\0';

                // Keep single letters i and a
                if (!(strlen(token) == 1 && token[0] != 'i' && token[0] != 'a')) {

                    // ✂️ Suffix split
                    if (ends_with(token, "ing")) {
                        token[strlen(token) - 3] = '\0';
                        strncpy(tokens[t++], token, MAX_TOKEN_LEN);
                        strncpy(tokens[t++], "ing", MAX_TOKEN_LEN);
                    } else if (ends_with(token, "ed")) {
                        token[strlen(token) - 2] = '\0';
                        strncpy(tokens[t++], token, MAX_TOKEN_LEN);
                        strncpy(tokens[t++], "ed", MAX_TOKEN_LEN);
                    } else {
                        strncpy(tokens[t++], token, MAX_TOKEN_LEN);
                    }

                    if (t >= MAX_TOKENS) break;
                }
                j = 0;
            }
        } else {
            if (j < MAX_TOKEN_LEN - 1) {
                token[j++] = tolower(c);
            }
        }
        i++;
    }

    if (j > 0 && t < MAX_TOKENS) {
        token[j] = '\0';
        strncpy(tokens[t], token, MAX_TOKEN_LEN);
        tokens[t][MAX_TOKEN_LEN - 1] = '\0';
        t++;
    }

    *num_tokens = t;
}

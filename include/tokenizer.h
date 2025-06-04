// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef TOKENIZER_H
#define TOKENIZER_H

#define MAX_TOKENS 1024
#define MAX_TOKEN_LEN 64

int is_separator(char c);
void tokenize(const char *input, char tokens[][MAX_TOKEN_LEN], int *num_tokens);

#endif

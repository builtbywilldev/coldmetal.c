// ===============================================================
// tokenizer.h — Header for Lexical Token Filter
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "config.h"


// ---------------------------------------------------------------
// 🪓 Tokenizer Interface
// ---------------------------------------------------------------
void tokenize(const char *input, char tokens[][MAX_TOKEN_LEN], int *num_tokens);

// ---------------------------------------------------------------
// ⛓️ Token Boundary Logic
// Used to detect token breaks (e.g., spaces, most punctuation)
// ---------------------------------------------------------------
int is_boundary(char c);

#endif  // TOKENIZER_H

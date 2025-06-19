// ===============================================================
// File: tokenizer.h
// Coldmetal Phase: 4
// Purpose: Header for Lexical Token Filter
// Linked to: tokenizer.c, memory.h
// Notes: Declares tokenizer + boundary logic interface
// ===============================================================

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "config.h"  // for MAX_TOKEN_LEN, MAX_TOKENS

// ---------------------------------------------------------------
// 🪓 Tokenizer Interface
// Splits input string into normalized tokens
// ---------------------------------------------------------------
void tokenize(const char *input, char tokens[][MAX_TOKEN_LEN], int *num_tokens);

// ---------------------------------------------------------------
// ⛓️ Token Boundary Logic
// Used to detect token breaks (e.g., spaces, most punctuation)
// ---------------------------------------------------------------
int is_boundary(char c);

#endif  // TOKENIZER_H

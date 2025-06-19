// ===============================================================
// logic.h — Inference and Response Logic
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef LOGIC_H
#define LOGIC_H

#include "tokenizer.h"

// Generates a response from embedded memory context
const char* generate_response(char tokens[][MAX_TOKEN_LEN], int num_tokens);

#endif  // LOGIC_H

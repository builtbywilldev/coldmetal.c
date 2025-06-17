// ===============================================================
// File: config.h
// Coldmetal Phase: 4
// Purpose: Centralized constants for memory, tokenizer, and embedding operations
// Linked to: tokenizer.c, embedder.c, memory.c, mint.c
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================


#ifndef CONFIG_H
#define CONFIG_H

// Tokenizer settings
#define MAX_TOKENS        1024    // Max tokens per input sequence
#define MAX_TOKEN_LEN     64      // Max characters per token

// Embedding vector size
#define EMBEDDING_SIZE    64      // Dimensionality of vector embeddings

// Memory constraints
#define MAX_MEMORY_ITEMS  9422    // Max memory entries loaded at once
#define MAX_MEMORY_LEN    1024    // Max length of content in each memory item

#endif // CONFIG_H

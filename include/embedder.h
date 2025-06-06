// ===============================================================
// embedder.h — Token and Sentence Embedding Interface
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================

#ifndef EMBEDDER_H
#define EMBEDDER_H

#define EMBEDDING_SIZE 64

// Embeds a single token into a fixed-size float vector
void embed_token(const char *token, float *vector);

// Embeds a full sentence by averaging token embeddings
void embed_text(const char* text, float* out_vector);

#endif  // EMBEDDER_H

// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Tactical Intelligence Unit
// ===============================================================
#ifndef EMBEDDER_H
#define EMBEDDER_H

#define EMBEDDING_SIZE 64

void embed_token(const char *token, float *vector);
void embed_text(const char* text, float* out_vector);

#endif

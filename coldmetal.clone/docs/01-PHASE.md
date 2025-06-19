# Morpheus — Phase 1: Offline Birth

## Summary
Phase 1 created the foundational offline LLM loop using C — no dependencies, no cloud, no training required. Morpheus can tokenize, embed, compare via attention, and recall persistent memory.

## Core Components
- Tokenizer
- Embedder
- Attention (cosine similarity)
- Persistent Memory
- Training Ingest Loop
- Semantic Inference REPL

## Files Introduced
- `main.c`
- `tokenizer.[ch]`
- `embedder.[ch]`
- `attention.[ch]`
- `memory.[ch]`
- `trainer.c`

## Output
`./morpheus` runs in CLI, fully offline, and responds using embedded memory from training corpus.

## Next Steps
- Expand training dataset (Poe, Aurelius, etc.)
- Implement vector averaging
- Optional: Build UI wrapper for human interaction

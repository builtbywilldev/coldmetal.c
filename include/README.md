# 📁 `include/` — Coldmetal Headers

This folder holds all the header (`.h`) files used by the Coldmetal.c core system. Each file defines the interface and shared structures used across the engine’s modules.

## 🧩 Header Overview

### `tokenizer.h`
Defines:
- `tokenize()`  
Breaks a string into fixed-length tokens using whitespace and punctuation delimiters.

### `embedder.h`
Defines:
- `embed_token()`  
- `embed_text()`  
Turns tokens into vector embeddings via a lightweight hash function. Averages multiple tokens into a single vector.

### `attention.h`
Defines:
- `cosine_similarity()`  
- `find_best_match()`  
Handles vector comparison via cosine similarity and selects the closest match from memory.

### `memory.h`
Defines:
- `save_memory()`  
- `load_memory()`  
- `recall_memory()`  
Interfaces for reading and writing `.mem` files (persistent memory stores).

### `math.h`
Defines:
- `vector_dot()`  
- `vector_norm()`  
Internal vector math routines for dot products and L2 normalization. Precision-first, dependency-free.

## 💡 Notes

- All headers are dependency-free and self-contained.
- Compatible with `C99` and standard POSIX environments.
- Each `.h` has a matching `.c` file in `src/`.

---

> 🧠 Coldmetal headers provide modular, human-readable building blocks for AI systems that run anywhere — even without an OS.

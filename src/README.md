# 🧠 `src/` — Coldmetal Core

This folder contains the foundational C source files powering **Coldmetal.c**, an offline transformer engine with zero dependencies.

## 📁 Contents

### `main.c`
Coldmetal REPL loop for token input, embedding, attention comparison, and memory recall. Acts as the CLI interface.

### `tokenizer.c/.h`
Whitespace and punctuation-based tokenizer. Converts raw input into clean token arrays for further processing.

### `embedder.c/.h`
Simple hash-based embedding of tokens into fixed-length vectors. Averages embeddings for full input strings.

### `attention.c/.h`
Performs cosine similarity between embedded inputs and stored memory. Determines "closest match" recall.

### `memory.c/.h`
Handles persistent `.mem` storage and lookup. Memory files can be swapped, archived, or trained offline.

### `trainer.c`
Reads `.txt` files line-by-line, embeds each, and saves output to memory files for later inference.

### `math.c/.h`
Internal arithmetic engine. Provides `vector_dot` and `vector_norm` for cosine similarity and normalization. No reliance on external math libs.

## ⚙️ Design Philosophy

- **Dependency-Free** — No Python, no Torch, no C++.
- **POSIX Compatible** — Works in airgapped or embedded environments.
- **Human-Readable Code** — Every file is under 150 LOC.
- **Swappable Parts** — You can replace tokenizers, embedders, or memory logic independently.

## 🔐 Ideal Use Cases

- Offline intelligence systems  
- Embedded inference on secure hardware  
- Disaster-proof personal AI assistants  
- Teaching tools for understanding transformers from scratch

---

Built for precision. Runs anywhere. Dies never.

> Authored by [@builtbywill](https://github.com/builtbywilldev)

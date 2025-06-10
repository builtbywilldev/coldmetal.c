# 🔥 Coldmetal.c — Dependency-Free AI Memory Engine (C) 
A fully offline, zero-dependency AI system inspired by `llm.c` — engineered for airgapped environments.  
Built in pure C with no Python, no external libraries, and no cloud ties.  

> "Proof that intelligence doesn’t require a subscription."  

---

### ✅ What's Inside

- 🧠 `tokenizer.c`: Converts input to raw tokens.
- 🧩 `embedder.c`: Turns tokens into float vectors.
- 🎯 `attention.c`: Computes cosine similarity to find relevant meaning.
- 🧠 `logic.c`: Uses memory recall and rules to generate responses.
- 🧠 `memory.c`: Persistent `.mem` file format for long-term learning.
- 🔁 `trainer.c`: Learn new ideas from any `.txt` file.

---

### 📚 Pretrained `.mem` files (so far)
- `tiny-shakespeare.mem`
- `tiny-poe.mem`
- `dracula.mem`
- `sherlock.mem`
- `declaration.mem`
- `snowden.mem`
- And more...

---

### 🔒 License

This project is proprietary and not open-source.

    The core logic and architecture of coldmetal.c are licensed exclusively to Silent Prototype Labs and BuiltByWill.
    Redistribution, modification, or reuse of any part of this system is prohibited without written permission.

If you're interested in collaboration, licensing, or research use, contact: builtbywill@proton.me. 

---

### 🔧 Optional: Web Scraper for Custom Training

If you want to train your own `.txt` files from websites (like Project Gutenberg), we include an optional **1-dependency scraper** using:

- `lynx` (console web browser — install via your package manager)

#### `scrape.sh`
```bash
#!/bin/bash
url="$1"
output="$2"
lynx -dump "$url" > "$output"
echo "Scraped to $output"
```

📦 Usage:
```bash
./scrape.sh "https://www.gutenberg.org/cache/epub/600/pg600-images.html" "data/untrained/frankenstein.txt"
```

---

### 🛠️ Next Steps

- Upgrade `tokenizer.c` to include real token math (subwords, frequencies, etc.)
- Add attention-based multi-line memory.
- Experiment with `.mem` merging logic for deeper training.
- Long term: compressed embedding files and vector search tree logic.

---

> BuiltByWill // Silent Prototype Labs  
> Phase 1 complete. Echo machine online.

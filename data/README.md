# 📁 `data/` — Training Input Files

This folder contains raw text files used to generate `.mem` memory modules.

## 📄 File Types

- `*.txt` — Cleaned input data (books, chats, docs)
- `*.log` — Optional logs or crawled output before processing

## 🧠 Usage

To train a new memory capsule:

```bash
./trainer data/dracula.txt

The output .mem file will appear in the current directory. Move it to your preferred memory location if needed.

    This is where raw language becomes memory. Feed your machine here.
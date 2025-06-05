

---

### 🧪 `tests/README.md`

```markdown
# 🧪 `tests/` — Module Verification Suite

This folder contains test files for each core component in the system.

## 🔬 Structure

- `test_tokenizer.c`
- `test_embedder.c`
- `test_attention.c`
- `test_memory.c`

Each file is written to test one module in isolation. Outputs are printed to the terminal for manual inspection.

## ▶️ Run

```bash
gcc tests/test_tokenizer.c -o test_tokenizer && ./test_tokenizer

Repeat for each module as needed. Later, these can be unified under a master test script or CI runner.

    You trust a machine with your thoughts? Test it first.
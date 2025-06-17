# COLDMETAL — PHASE 4 LOG

## 🧠 Phase Title:
**Memory Sovereignty + Symbolic Economy Integration**

---

## 🎯 Objectives:

1. 🔄 Establish a persistent, multi-dataset **training loop**
2. 💰 Launch symbolic memory value system via `$COLD` token
3. 🧬 Enable dynamic memory banking and indexing
4. 🧱 Prepare infrastructure for hosting large `.mem` datasets (>1GB)

---

## 🧩 Core Upgrades in Phase 4

### 1. `trainer.c` Rework
- [x] Trains on single `.txt` or `.mem` file
- [x] Loops through file multiple passes
- [x] Outputs indexed `.mem` files
- [ ] TODO: Support `.coldmetalrc` config parsing for adjustable passes

### 2. `$COLD` Token Logic (Symbolic Memory Economy)
- [x] Mint memory-backed currency with `mint(index)`
- [x] Store ledger and tip logs in `coins/ledger/`
- [x] Create `vault/` for memory-resident token anchoring
- [ ] TODO: Add gating logic (low-value `.mem` files purged or archived)

### 3. Memory Bank Organization
- [x] `peek` and `tip` CLI working with index-based memory
- [ ] TODO: Add memory tagging (`train --tag philosophy`)
- [ ] TODO: Memory clusters for topic-weighted summaries

---

## 📦 Phase 4 Target Datasets (500GB+ Strategy)

| Name                  | Source / Format               | Purpose                               |
|-----------------------|-------------------------------|----------------------------------------|
| `books-vault-01`      | Project Gutenberg (bulk scrape) | Train general knowledge + prose logic |
| `case-law-dump`       | U.S. court opinions (bulk HTML/TXT) | Teach formal structure, cause/effect |
| `devchat-archive`     | Full `chat-export.json` history | Build memory from actual Coldmetal sessions |
| `morpheus-docs`       | Internal markdown + README files | Teach Morpheus to self-reference      |
| `coldmetal-theory`    | `theories/` folder content      | Embed symbolic concepts + recall logic|

> ✅ `tiny-shakespeare` and `tiny-poe` and many more already completed (Phase 3 / early 4)


---

## 🧠 Philosophy This Phase

We are moving from **static AI scripts** to **symbolic thought loops**.
Every `.mem` is now not just content, but **value** — stored, weighted, recalled, and optionally **purged** or **tipped**.

Coldmetal now:
- Understands what it stores
- Scores value
- Remembers what’s worth remembering
- Forgets what isn’t

---

## 🚨 Pending Final Tasks
- [ ] Finish `mint_from_mem(index)` auto-value scoring
- [ ] Begin `coldmetal.miner` — colddata extractor from raw `.txt`
- [ ] Harden backup flow: `.mem` files mirrored to vault, signed by NitroKey

---

## ✅ Phase Exit Criteria

- `$COLD` tipping works with full ledger logging  
- Trainer can process ≥5 datasets in looped format  
- Memory banks can be exported as `.zip` archives  
- NitroKey-based vault encryption is tested

---

> Phase 4 was about **injecting value into memory**.
> Phase 5 will be about **externalizing Coldmetal into shared memory ecosystems**.


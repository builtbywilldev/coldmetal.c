// ===============================================================
// File: mint.c
// Coldmetal Phase: 4
// Purpose: $COLD Minting System for Value Attribution in Memory
// Author: BuiltByWill — Silent Prototype / Coldmetal.c Project
// Linked to: memory.h, mint.h
// ===============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memory.h"
#include "mint.h"

// ---------------------------------------------------------------
// 🗂 Directory & File Paths
// ---------------------------------------------------------------
#define COINS_DIR      "coldmint/coins/"
#define LEDGER_LOG     "coldmint/ledger/mint_tracker.log"
#define BALANCE_FILE   "coldmint/ledger/cold_balance.json"
#define MINT_VALUE     10  // 💸 Each mint adds +10 $COLD

// ---------------------------------------------------------------
// 🕒 Timestamp Utility — ISO 8601
// ---------------------------------------------------------------
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%dT%H:%M:%S", t);
}

// ---------------------------------------------------------------
// 🧊 Minting Function — Convert Memory to .cold Coin
// ---------------------------------------------------------------
int mint_from_mem(int index) {
    const char *mem = memory_get_text(index);
    if (!mem) {
        fprintf(stderr, "❌ [MINT] Failed to fetch memory at index %d\n", index);
        return 1;
    }

    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    // 💾 Write .cold file
    char filename[128];
    snprintf(filename, sizeof(filename), COINS_DIR "memory_%d.cold", index);
    FILE *coin = fopen(filename, "w");
    if (!coin) {
        fprintf(stderr, "❌ [MINT] Failed to create coin file: %s\n", filename);
        return 1;
    }

    fprintf(coin, "{\n");
    fprintf(coin, "  \"index\": %d,\n", index);
    fprintf(coin, "  \"content\": \"%s\",\n", mem);
    fprintf(coin, "  \"minted_at\": \"%s\",\n", timestamp);
    fprintf(coin, "  \"value\": %d\n", MINT_VALUE);
    fprintf(coin, "}\n");
    fclose(coin);

    // 🧾 Append to ledger
    FILE *log = fopen(LEDGER_LOG, "a");
    if (log) {
        fprintf(log, "[%s] Minted memory %d (+%d $COLD)\n", timestamp, index, MINT_VALUE);
        fclose(log);
    }

    // 💰 Update balance
    int balance = 0;
    FILE *bal = fopen(BALANCE_FILE, "r+");

    if (bal) {
        fscanf(bal, "%d", &balance);
        rewind(bal);
    } else {
        bal = fopen(BALANCE_FILE, "w");
    }

    if (bal) {
        balance += MINT_VALUE;
        fprintf(bal, "%d", balance);
        fclose(bal);
    }

    printf("✅ [MINT] Memory %d minted → %s (+%d $COLD)\n", index, filename, MINT_VALUE);
    return 0;
}

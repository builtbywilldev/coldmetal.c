// mint.c — $COLD Minting System
// Purpose: Generates .cold files, logs minting, and updates balance
// Author: BuiltByWill | Coldmetal.c Project

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "memory.h"  // Adjust if memory access requires another header
#include "mint.h"

#define COINS_DIR      "coldmint/coins/"
#define LEDGER_LOG     "coldmint/ledger/mint_tracker.log"
#define BALANCE_FILE   "coldmint/ledger/cold_balance.json"
#define MINT_VALUE     10 // Each mint gives +10 $COLD

// Helper to get current ISO timestamp
void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%dT%H:%M:%S", t);
}

// Main minting function
int mint_from_mem(int index) {
    // Get memory by index
    const char *mem = memory_get_text(index);
    if (!mem) {
        fprintf(stderr, "[COLD] Failed to fetch memory at index %d\n", index);
        return 1;
    }

    // Generate timestamp
    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    // Create filename
    char filename[128];
    snprintf(filename, sizeof(filename), COINS_DIR "memory_%d.cold", index);

    // Write .cold file
    FILE *coin = fopen(filename, "w");
    if (!coin) {
        fprintf(stderr, "[COLD] Failed to write coin file: %s\n", filename);
        return 1;
    }

    fprintf(coin, "{\n");
    fprintf(coin, "  \"index\": %d,\n", index);
    fprintf(coin, "  \"content\": \"%s\",\n", mem);
    fprintf(coin, "  \"minted_at\": \"%s\",\n", timestamp);
    fprintf(coin, "  \"value\": %d\n", MINT_VALUE);
    fprintf(coin, "}\n");
    fclose(coin);

    // Append to mint_tracker.log
    FILE *log = fopen(LEDGER_LOG, "a");
    if (log) {
        fprintf(log, "[%s] Minted memory %d (+%d $COLD)\n", timestamp, index, MINT_VALUE);
        fclose(log);
    }

    // Update cold_balance.json (very basic: just reads current and adds)
    FILE *bal = fopen(BALANCE_FILE, "r+");
    int balance = 0;

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

    printf("[COLD] Minted memory %d to %s (+%d $COLD)\n", index, filename, MINT_VALUE);
    return 0;
}

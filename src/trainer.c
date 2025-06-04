// ===============================================================
// Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Trainer v2
// ===============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/memory.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [input.txt] [output.mem]\n", argv[0]);
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];

    FILE* file = fopen(input_path, "r");
    if (!file) {
        printf("Failed to open input: %s\n", input_path);
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // strip newline
        if (strlen(line) > 0) {
            remember(line);
            printf("[+] Trained: %s\n", line);
        }
    }

    fclose(file);
    save_memory(output_path);
    printf("Saved memory to %s\n", output_path);
    return 0;
}

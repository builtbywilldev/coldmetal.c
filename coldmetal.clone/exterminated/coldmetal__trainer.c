// ===============================================================
// File: coldmetal_trainer.c
// Coldmetal Phase: 4
// Purpose: Converts raw text into .mem format by embedding lines into labeled vector entries
// Linked to: embedder.c, config.h
// Output: JSON-style .mem file with vectors + labels
// ===============================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#include "embedder.h"  // Uses embed_text() from your system
#include "config.h"    // Must define EMBEDDING_SIZE

#define MAX_LINE 2048

// ---------------------------------------------------------------
// Writes a single memory entry to the output .mem file
// ---------------------------------------------------------------
void write_memory_entry(FILE *out, const char *text, float *vec, const char *label, int is_last) {
    fprintf(out, "  {\n    \"text\": \"%s\",\n    \"vector\": [", text);
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        fprintf(out, "%.6f", vec[i]);
        if (i < EMBEDDING_SIZE - 1) fprintf(out, ", ");
    }
    fprintf(out, "],\n    \"label\": \"%s\"\n  }", label);
    if (!is_last) fprintf(out, ",");
    fprintf(out, "\n");
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <input.txt> <label> <output.mem>\n", argv[0]);
        return 1;
    }

    const char *input_path  = argv[1];
    const char *label       = argv[2];
    const char *output_path = argv[3];

    FILE *in = fopen(input_path, "r");
    if (!in) {
        perror("Input file");
        return 1;
    }

    FILE *out = fopen(output_path, "w");
    if (!out) {
        perror("Output file");
        fclose(in);
        return 1;
    }

    fprintf(out, "[\n");

    char line[MAX_LINE];
    int entry_count = 0;
    char *lines[10000];  // Maximum of 10,000 lines supported

    while (fgets(line, sizeof(line), in)) {
        if (strlen(line) < 3) continue;  // Skip empty or tiny lines
        lines[entry_count] = strdup(line);
        lines[entry_count][strcspn(lines[entry_count], "\n")] = 0;  // Strip newline
        entry_count++;
    }

    for (int i = 0; i < entry_count; i++) {
        float vec[EMBEDDING_SIZE];
        embed_text(lines[i], vec);  // 💥 Real semantic embedding
        write_memory_entry(out, lines[i], vec, label, i == entry_count - 1);
        free(lines[i]);
    }

    fprintf(out, "]\n");
    fclose(in);
    fclose(out);

    printf("✅ Trained %d entries → %s\n", entry_count, output_path);
    return 0;
}

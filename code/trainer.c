// ===============================================================
// trainer.c Silent Prototype — BuiltByWill
// Phase-Coded Artifact of Morpheus // Trainer v3.0
// ===============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "memory.h"

// JSON parser for ChatGPT exports
void train_from_json(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("❌ Failed to open JSON: %s\n", path);
        return;
    }

    char line[2048];
    char current_type = 'U';
    char content[2048];

    while (fgets(line, sizeof(line), file)) {
        char* ptr = line;
        while (isspace(*ptr)) ptr++;

        if (strstr(ptr, "\"role\": \"user\"")) {
            current_type = 'Q';
        } else if (strstr(ptr, "\"role\": \"assistant\"")) {
            current_type = 'A';
        } else if (strstr(ptr, "\"content\":")) {
            char* start = strchr(ptr, '[');
            if (!start) continue;
            start++;

            char* quote_start = strchr(start, '"');
            if (!quote_start) continue;
            quote_start++;

            char* quote_end = strchr(quote_start, '"');
            if (!quote_end) continue;
            *quote_end = '\0';

            strncpy(content, quote_start, sizeof(content) - 1);
            content[sizeof(content) - 1] = '\0';

            remember_with_type(content, current_type);
            printf("[+] Trained (%c): %s\n", current_type, content);
        }
    }

    fclose(file);
}

// TXT line-based parser
void train_from_txt(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("❌ Failed to open TXT: %s\n", path);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        char type = 'U';
        char* content = line;

        if (line[0] == '[' && line[2] == ']') {
            type = line[1];
            content = &line[4];
        }

        remember_with_type(content, type);
        printf("[+] Trained (%c): %s\n", type, content);
    }

    fclose(file);
}

// 🔥 THIS is what the linker needs
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [input.json|txt] [output.mem]\n", argv[0]);
        return 1;
    }

    const char* input_path = argv[1];
    const char* output_path = argv[2];

    if (strstr(input_path, ".json")) {
        train_from_json(input_path);
    } else {
        train_from_txt(input_path);
    }

    save_memory(output_path);
    printf("✅ Saved memory to %s\n", output_path);
    return 0;
}

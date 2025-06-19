// ===============================================================
// File: trainer.c
// Coldmetal Phase: 5
// Purpose: Unified memory trainer and model weight updater
// BuiltByWill — Silent Prototype Tactical Intelligence Unit
// ===============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>

#include "embedder.h"
#include "config.h"
#include "model.h"
#include "math.h"

#define MAX_LINE 2048
#define MAX_PATH 1024
#define MAX_NAME 256
#define MAX_LINES 10000

void write_mem_entry(FILE *out, const char *text, float *vec, const char *label, int is_last) {
    fprintf(out, "  {\n    \"text\": \"%s\",\n    \"vector\": [", text);
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        fprintf(out, "%.6f", vec[i]);
        if (i < EMBEDDING_SIZE - 1) fprintf(out, ", ");
    }
    fprintf(out, "],\n    \"label\": \"%s\"\n  }", label);
    if (!is_last) fprintf(out, ",");
    fprintf(out, "\n");
}

void embed_txt_file(const char *input_path, const char *output_path) {
    FILE *in = fopen(input_path, "r");
    if (!in) {
        printf("❌ Failed to open %s\n", input_path);
        return;
    }

    FILE *out = fopen(output_path, "w");
    if (!out) {
        printf("❌ Failed to write %s\n", output_path);
        fclose(in);
        return;
    }

    char *lines[MAX_LINES];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), in)) {
        if (strlen(line) < 3) continue;
        if (count >= MAX_LINES) break;
        lines[count] = strdup(line);
        lines[count][strcspn(lines[count], "\n")] = 0;
        count++;
    }

    if (count == 0) {
        printf("⚠️  No lines to embed in %s\n", input_path);
        fclose(in);
        fclose(out);
        return;
    }

    fprintf(out, "[\n");
    for (int i = 0; i < count; i++) {
        float vec[EMBEDDING_SIZE];
        embed_text(lines[i], vec);
        write_mem_entry(out, lines[i], vec, "U", i == count - 1);
        free(lines[i]);
    }
    fprintf(out, "]\n");

    fclose(in);
    fclose(out);
    printf("✅ Embedded %d lines → %s\n", count, output_path);
}

void train_model_from_mem(const char *mem_dir, int epochs) {
    load_weights("model.weights");

    for (int e = 0; e < epochs; e++) {
        DIR *dir = opendir(mem_dir);
        if (!dir) {
            printf("❌ Could not open memory directory: %s\n", mem_dir);
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (!entry->d_name || !strstr(entry->d_name, ".mem")) continue;

            char path[MAX_PATH];
            snprintf(path, sizeof(path), "%s/%s", mem_dir, entry->d_name);
            printf("🧠 Training on: %s\n", path);
            fflush(stdout);

            FILE *f = fopen(path, "r");
            if (!f) continue;

            fseek(f, 0, SEEK_END);
            long size = ftell(f);
            rewind(f);

            char *content = malloc(size + 1);
            if (fread(content, 1, size, f) != size) {
                printf("⚠️ Failed to read %s\n", path);
                free(content);
                fclose(f);
                continue;
            }
            content[size] = '\0';
            fclose(f);

            if (!strstr(content, "\"vector\": [")) {
                printf("⚠️ Skipping %s (no vectors found)\n", path);
                free(content);
                continue;
            }

            int trained = 0;
            char *p = content;
            while ((p = strstr(p, "\"vector\": [")) != NULL) {
                p += strlen("\"vector\": [");
                float vec[EMBEDDING_SIZE] = {0};

                for (int i = 0; i < EMBEDDING_SIZE; i++) {
                    sscanf(p, "%f", &vec[i]);
                    char *comma = strchr(p, ',');
                    char *bracket = strchr(p, ']');
                    if (!comma || comma > bracket) {
                        p = bracket;
                        break;
                    }
                    p = comma + 1;
                }

                float *out = forward_pass(vec);
                float loss = compute_loss(out, vec);
                update_weights(vec, vec, out, loss);
                free(out);
                trained++;
            }

            printf("   ↪️  Trained %d vectors from %s\n", trained, entry->d_name);
            fflush(stdout);
            free(content);
        }

        closedir(dir);
        printf("🔥 Epoch %d complete\n", e + 1);
    }

    save_weights("model.weights");
    printf("✅ Weights saved to model.weights\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <txt_folder>\n", argv[0]);
        return 1;
    }

    const char *source_dir = argv[1];
    const char *output_dir = "data/.mem";
    mkdir("data", 0777);
    mkdir(output_dir, 0777);

    DIR *dir = opendir(source_dir);
    if (!dir) {
        printf("❌ Could not open source dir: %s\n", source_dir);
        return 1;
    }

    int embedded = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!entry->d_name || !strstr(entry->d_name, ".txt")) continue;

        char base[MAX_NAME];
        strncpy(base, entry->d_name, sizeof(base) - 1);
        base[sizeof(base) - 1] = '\0';
        char *dot = strrchr(base, '.');
        if (dot) *dot = '\0';

        char in_path[MAX_PATH], out_path[MAX_PATH];
        snprintf(in_path, sizeof(in_path), "%s/%s", source_dir, entry->d_name);
        snprintf(out_path, sizeof(out_path), "%s/%s.mem", output_dir, base);

        embed_txt_file(in_path, out_path);
        embedded++;
    }

    closedir(dir);

    if (embedded == 0) {
        printf("⚠️ No .txt files found in %s\n", source_dir);
        return 1;
    }

    train_model_from_mem(output_dir, 5);
    return 0;
}

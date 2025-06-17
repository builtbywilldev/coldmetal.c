// ===============================================================
// File: memory_loader.c
// Coldmetal Phase: 4
// Purpose: Load and score closest .mem memory matches via cosine similarity
// Linked to: memory.h, config.h, math.h
// Notes: Scans memory files and ranks top semantic matches
// ===============================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <sys/stat.h>

#include "config.h"
#include "memory.h"
#include "math.h"

#define MAX_RESULTS 5
#define MAX_PATH 512

typedef struct {
    char text[1024];
    float vector[EMBEDDING_SIZE];
    float score;
} MemoryEntry;

MemoryEntry top_matches[MAX_RESULTS] = {0};

// 🧠 Cosine similarity between input and `.mem` vector
float cosine_similarity(float *a, float *b) {
    float dot = 0.0f, mag_a = 0.0f, mag_b = 0.0f;
    for (int i = 0; i < EMBEDDING_SIZE; i++) {
        dot += a[i] * b[i];
        mag_a += a[i] * a[i];
        mag_b += b[i] * b[i];
    }
    return dot / (sqrtf(mag_a) * sqrtf(mag_b) + 1e-8f);
}

// 📦 Attempt to insert a memory chunk into top N
void try_insert_match(const char *text, float *vec, float score) {
    for (int i = 0; i < MAX_RESULTS; i++) {
        if (score > top_matches[i].score) {
            for (int j = MAX_RESULTS - 1; j > i; j--) {
                top_matches[j] = top_matches[j - 1];
            }
            strncpy(top_matches[i].text, text, sizeof(top_matches[i].text) - 1);
            memcpy(top_matches[i].vector, vec, sizeof(float) * EMBEDDING_SIZE);
            top_matches[i].score = score;
            break;
        }
    }
}

// 🔄 Load .mem file and compare entries
void process_mem_file(const char *path, float *input_vec) {
    FILE *f = fopen(path, "r");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);

    char *content = malloc(fsize + 1);
    fread(content, 1, fsize, f);
    content[fsize] = '\0';
    fclose(f);

    char *entry_start = strchr(content, '{');
    while (entry_start) {
        char *entry_end = strchr(entry_start, '}');
        if (!entry_end) break;

        char entry[2048] = {0};
        strncpy(entry, entry_start, entry_end - entry_start + 1);

        // Extract text
        char *text_start = strstr(entry, "\"text\":");
        char text[1024] = {0};
        if (text_start) {
            sscanf(text_start, "\"text\": \"%[^\"]", text);
        }

        // Extract vector
        float vec[EMBEDDING_SIZE] = {0};
        char *vec_start = strstr(entry, "\"vector\": [");
        if (vec_start) {
            vec_start = strchr(vec_start, '[') + 1;
            for (int i = 0; i < EMBEDDING_SIZE; i++) {
                sscanf(vec_start, "%f", &vec[i]);
                vec_start = strchr(vec_start, ',') ? strchr(vec_start, ',') + 1 : strchr(vec_start, ']');
                if (!vec_start || *vec_start == ']') break;
            }

            float score = cosine_similarity(input_vec, vec);
            try_insert_match(text, vec, score);
        }

        entry_start = strchr(entry_end + 1, '{');
    }

    free(content);
}

// 📂 Scan all .mem files in directory
void scan_memory_dir(const char *dir_path, float *input_vec) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!strstr(entry->d_name, ".mem")) continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);
        process_mem_file(full_path, input_vec);
    }

    closedir(dir);
}

// 🧪 Entry point for testing
int main() {
    float input_vec[EMBEDDING_SIZE];
    for (int i = 0; i < EMBEDDING_SIZE; i++) input_vec[i] = 0.5f;

    scan_memory_dir("../data/.mem", input_vec);

    printf("\n🧠 Top Memory Matches:\n");
    for (int i = 0; i < MAX_RESULTS; i++) {
        if (top_matches[i].score > 0) {
            printf(" [%d] %.4f → \"%s\"\n", i + 1, top_matches[i].score, top_matches[i].text);
        }
    }

    return 0;
}

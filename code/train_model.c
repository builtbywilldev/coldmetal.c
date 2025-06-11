#include "model.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

float* load_vector(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    float *vec = malloc(sizeof(float) * EMBEDDING_SIZE);
    fread(vec, sizeof(float), EMBEDDING_SIZE, f);
    fclose(f);
    return vec;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <mem_folder> <epochs>\n", argv[0]);
        return 1;
    }

    const char *folder = argv[1];
    int epochs = atoi(argv[2]);
    load_weights("model.weights");

    for (int e = 0; e < epochs; e++) {
        DIR *dir = opendir(folder);
        if (!dir) {
            perror("opendir");
            return 1;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (!strstr(entry->d_name, ".mem")) continue;

            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", folder, entry->d_name);


            float *vec = load_vector(fullpath);
            if (!vec) continue;

            float *output = forward_pass(vec);
            float loss = compute_loss(output, vec);  // target = same as input (autoencoder style)
            update_weights(vec, vec, output, loss);

            free(vec);
            free(output);
        }

        closedir(dir);
        printf("Epoch %d complete ✅\n", e + 1);
    }

    save_weights("model.weights");
    printf("✅ Training complete. Weights saved to model.weights\n");
    return 0;
}

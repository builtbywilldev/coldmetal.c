// ===============================================================
// 🧪 math_test.c — Validation Suite for math.c Operations
// Author: BuiltByWill | Purpose: Local Test Run on Coldmetal Stack
// ===============================================================

#include <stdio.h>
#include "math.h"

int main() {
    float a[] = {1.0f, 2.0f, 3.0f};
    float b[] = {4.0f, 5.0f, 6.0f};
    int len = 3;

    printf("Dot Product: %f\n", vector_dot(a, b, len));
    printf("Norm A: %f\n", vector_norm(a, len));
    printf("Norm B: %f\n", vector_norm(b, len));
    printf("Cosine Similarity: %f\n", cosine_similarity(a, b, len));
    printf("Cosine Distance: %f\n", cosine_distance(a, b, len));
    printf("Angle (radians): %f\n", angle_between(a, b, len));
    printf("Scalar Projection (A on B): %f\n", scalar_projection(a, b, len));
    printf("Are Orthogonal? %s\n", are_orthogonal(a, b, len) ? "Yes" : "No");

    // Softmax test
    float soft_in[] = {1.0f, 2.0f, 3.0f};
    float soft_out[3];
    softmax(soft_in, soft_out, 3);
    printf("Softmax: [");
    for (int i = 0; i < 3; ++i) {
        printf("%f", soft_out[i]);
        if (i < 2) printf(", ");
    }
    printf("]\n");

    // Normalization test
    float to_norm[] = {3.0f, 4.0f};
    normalize_vector(to_norm, 2);
    printf("Normalized [3,4]: [%f, %f]\n", to_norm[0], to_norm[1]);

    return 0;
}

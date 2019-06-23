#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "matrix.h"
#include "activations.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // VECTOR

    vector_t rand_layer;
    rand_vector(&rand_layer, 10, 100);
    float* after_activation = relu(rand_layer.data, rand_layer.size);
    for (int i = 0; i < rand_layer.size; i++) {
        printf("before relu: %f  |  ", rand_layer.data[i]);
        printf("after relu: %f\n", after_activation[i]);
    }
    free(after_activation);
    free_vector(&rand_layer);

    // MATRIX

    matrix_t m;
    rand_matrix(&m, 3, 2, 100);
    printf("printing matrix:\n");
    print_matrix(&m);

    matrix_t t = transpose_matrix(&m);
    printf("printing transpose:\n");
    print_matrix(&t);
    free_matrix(&m);
    free_matrix(&t);
    return 0;
}

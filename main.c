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
    rand_matrix(&m, 2, 2, 5);
    printf("printing matrix m:\n");
    print_matrix(&m);

    matrix_t t = transpose_matrix(&m);
    printf("printing transpose of m:\n");
    print_matrix(&t);

    matrix_t n;
    rand_matrix(&n, 2, 2, 5);
    printf("printing matrix n:\n");
    print_matrix(&n);

    printf("product of m*n:\n");
    matrix_t p = matrix_mult(&m, &n);
    print_matrix(&p);

    printf("mult by -1:\n");
    matrix_t negative_p = matrix_mult_scalar(&p, -1);
    print_matrix(&negative_p);

    printf("sum of p + -p:\n");
    matrix_t sum = matrix_add(&p, &negative_p);
    print_matrix(&sum); // should be 0 matrix
    
    free_matrix(&m);
    free_matrix(&t);
    free_matrix(&p);
    free_matrix(&negative_p);
    free_matrix(&sum);
    return 0;
}

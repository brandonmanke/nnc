#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "activations.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // VECTOR

    matrix_t rand_layer;
    rand_matrix(&rand_layer, 1, 10, 100);
    // row vs col shouldnt matter for 1-D 
    // which ever dimension is not 1 is fine since we are always using 1-D array
    float* after_relu = relu_activation(rand_layer.data, rand_layer.col);
    float* after_sigmoid = sigmoid_activation(rand_layer.data, rand_layer.col);
    float* after_tanh = tanh_activation(rand_layer.data, rand_layer.col);
    float* after_softmax = softmax_activation(rand_layer.data, rand_layer.col);
    for (int i = 0; i < rand_layer.col; i++) {
        printf("input layer: %f  |  ", rand_layer.data[i]);
        printf("after relu: %f | ", after_relu[i]);
        printf("after sigmoid: %f | ", after_sigmoid[i]);
        printf("after tanh: %f | ", after_tanh[i]);
        printf("after softmax: %f\n", after_softmax[i]);
    }
    free(after_relu);
    free(after_sigmoid);
    free(after_tanh);
    free(after_softmax);
    free_matrix(&rand_layer);

    // MATRIX

    matrix_t id;
    create_identity_matrix(&id, 3, 3);
    printf("printing 3x3 identity matrix:\n");
    print_matrix(&id);
    printf("trace 3x3 id: %.1f\n", trace_matrix(&id)); // should be 3.0

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
    matrix_t p = mult_matrix(&m, &n);
    print_matrix(&p);

    printf("mult by -1:\n");
    matrix_t negative_p = scalar_mult_matrix(&p, -1.0f);
    print_matrix(&negative_p);

    printf("sum of p + -p:\n");
    matrix_t sum = add_matrix(&p, &negative_p);
    print_matrix(&sum); // should be 0 matrix
    
    free_matrix(&id);
    free_matrix(&m);
    free_matrix(&t);
    free_matrix(&p);
    free_matrix(&negative_p);
    free_matrix(&sum);
    return 0;
}

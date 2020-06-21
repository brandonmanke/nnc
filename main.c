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
    identity_matrix(&id, 3, 3);
    printf("printing 3x3 identity matrix:\n");
    print_matrix(stdout, &id);
    printf("trace 3x3 id: %.1f\n", trace_matrix(&id)); // should be 3.0

    matrix_t m;
    rand_matrix(&m, 2, 2, 5);
    printf("printing matrix m:\n");
    print_matrix(stdout, &m);

    matrix_t t = transpose_matrix(&m);
    printf("printing transpose of m:\n");
    print_matrix(stdout, &t);

    matrix_t n;
    rand_matrix(&n, 2, 2, 5);
    printf("printing matrix n:\n");
    print_matrix(stdout, &n);

    printf("product of m*n:\n");
    matrix_t p = mult_matrix(&m, &n);
    print_matrix(stdout, &p);

    printf("mult by -1:\n");
    matrix_t negative_p = scalar_mult_matrix(&p, -1.0f);
    print_matrix(stdout, &negative_p);

    printf("sum of p + -p:\n");
    matrix_t sum = add_matrix(&p, &negative_p);
    print_matrix(stdout, &sum); // should be 0 matrix

    printf("activation of p (relu):\n");
    struct activation act;
    act.type = RELU;
    act.function = relu_activation;
    matrix_t a = matrix_activation(&p, &act);
    print_matrix(stdout, &a);

    printf("activation of p (lrelu):\n");
    act.type = LRELU;
    act.function = NULL;
    float alpha = 0.02f;
    act.param = (void*) &alpha;
    matrix_t b = matrix_activation(&p, &act);
    print_matrix(stdout, &b);

    //determinant_matrix(&b);
    //swap_row_matrix(&b, 0, 1);
    //print_matrix(stdout, &b);

    tensor_t ten;
    rand_tensor(&ten, 3, 3, 3, 100);
    printf("random 3x3x3 tensor:\n");
    for (int i = 0; i < ten.dimension; i++) {
        print_matrix(stdout, &ten.matrices[i]);
        printf("\\\n");
    }
    free_tensor(&ten);

    free_matrix(&id);
    free_matrix(&m);
    free_matrix(&n);
    free_matrix(&t);
    free_matrix(&p);
    free_matrix(&negative_p);
    free_matrix(&sum);
    free_matrix(&a);
    free_matrix(&b);
    return 0;
}

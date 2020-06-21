#include "network.h"

#include <stdlib.h>
#include <assert.h>

// idk
void init_matrix(network_t* net, const int layer_sizes[], const size_t lsize) {
    assert(net != NULL);
    for (int i = 0; i <  net->size; i++) {
        layer_t l;
        l.size = 10;
        init_layer(&l);
    }
}

void init_layer(layer_t* l) {
    assert(l != NULL);
    matrix_t m;
    rand_matrix(&m, 1, l->size, 1);
    l->weight = m;
}

matrix_t feed_forward(layer_t* l, const matrix_t* input) {
    assert(l != NULL);
    assert(input != NULL);
    l->input = *input;

    matrix_t prod = mult_matrix(&l->input, &l->weight);
    matrix_t sum = add_matrix(&prod, &l->bias);
    return matrix_activation(&sum, &l->act);
}

float mse_loss(matrix_t y, layer_t* l) {
    return 0.0f;
}

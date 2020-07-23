#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.h"
#include "activations.h"

typedef struct layer {
    matrix_t input;
    matrix_t weight;
    matrix_t bias;
    struct activation act;
    int size;
} layer_t;

typedef struct network {
    layer_t* layers;
    int size;
} network_t;

void init_network(network_t* net);

void init_layer(layer_t* l);

matrix_t feed_forward(layer_t* l, const matrix_t* input);

// TODO: loss fn, backprop, train, test, init, delete

float mse_loss(const matrix_t* y_true, const matrix_t* y_pred);

#endif

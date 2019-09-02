// TODO: Think about the design of our activation function types
// i.e. do we want to use structs, callbacks etc.
// Not sure if I want to pass matrix_t instead of float*
// or allowing side effects 
#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <stddef.h>

#include "matrix.h"

typedef enum { LINEAR, RELU, LRELU, SIGMOID, TANH, SOFTMAX } activation_t;

typedef float* (*activation_fn)(const float*, const size_t);

struct activation {
    activation_t type;
    activation_fn function;
    void* param; // optional (e.x. alpha)
};

matrix_t matrix_activation(const matrix_t* m, const struct activation* fn);

// ReLU(x) = max(x, 0)
// derivative = x > 0 ? 1 : 0
float* relu_activation(const float* layer, const size_t s);

float* lrelu_activation(const float* layer, const size_t s);

float* lrelu_activation2(const float* layer, const size_t s, const float alpha);

// Sigmoid(x) = 1 / (1 + e^-x) = e^x / (e^x + 1)
// derivative = e^x / (1 + e^x)^2
float* sigmoid_activation(const float* layer, const size_t s);

// hyperbolic tan
float* tanh_activation(const float* layer, const size_t s);

// softmax / normalized exp
float* softmax_activation(const float* layer, const size_t s);

#endif

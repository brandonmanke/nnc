// TODO: Think about the design of our activation function types
// i.e. do we want to use structs, callbacks etc.
#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <stddef.h>

// ReLU(x) := max(x, 0)
float* relu_activation(const float* layer, const size_t s);

// Sigmoid(x) := 1 / (1 + e^-x) = e^x / (e^x + 1)
float* sigmoid_activation(const float* layer, const size_t s);

// hyperbolic tan
float* tanh_activation(const float* layer, const size_t s);

// softmax / normalized exp
float* softmax_activation(const float* layer, const size_t s);

#endif

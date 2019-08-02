#include "activations.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>

// ReLU(x) := max(x, 0)
float* relu_activation(const float* layer, const size_t s) {
    float* new_layer = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++) {
        new_layer[i] = (layer[i] > 0) ? layer[i] : 0;
    }
    return new_layer;
}

// sigmoid(x) := 1 / (1 + e^-x) = e^x / (e^x + 1)
float* sigmoid_activation(const float* layer, const size_t s) {
    float* new_layer = calloc(s, sizeof(float));
    // Do we want to normalize this as well, like softmax? 
    // Or just leave it up to input to make it stable?
    for (int i = 0; i < s; i++) {
        new_layer[i] = (expf(layer[i]) / (expf(layer[i]) + 1));
    }
    return new_layer;
}

// hyperbolic tan
float* tanh_activation(const float* layer, const size_t s) {
    float* new_layer = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++) {
        new_layer[i] = tanhf(layer[i]);
    }
    return new_layer;
}

// softmax / normalized exp
// consider not normalizing input, since on some inputs it's not needed?
float* softmax_activation(const float* layer, const size_t s) {
    float* new_layer = calloc(s, sizeof(float));

    // see: Practical issues: Numeric stability
    // http://cs231n.github.io/linear-classify/#softmax
    float max = FLT_MIN;
    for (int i = 0; i < s; i++) {
        max = (layer[i] > max) ? layer[i] : max;
    }

    float exp_sum = 0;
    for (int i = 0; i < s; i++) {
        exp_sum += expf(layer[i] - max); // should we worry about overflow?
    }
    for (int i = 0; i < s; i++) {
        // exp normalize
        new_layer[i] = expf(layer[i] - max) / exp_sum;
    }
    return new_layer;
}

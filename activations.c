#include "activations.h"

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

matrix_t matrix_activation(const matrix_t* m, const struct activation* fn) {
    assert(m != NULL);
    matrix_t a;
    create_matrix(&a, m->row, m->col);
    size_t size = m->row * m->col;
    // Ideally there would be a cleaner way to handle this
    // Will look into alternatives
    // Also not sure about the safety of just checking if a void* -> float > 0
    if (fn->type == LRELU && fn->param != NULL && *((float*) fn->param) > 0) {
        const float alpha = *((const float*) fn->param);
        a.data = lrelu_activation2(m->data, size, alpha);
    } else {
        a.data = fn->function(m->data, size);
    }
    return a;
}

// ReLU(x) := max(x, 0)
float* relu_activation(const float* layer, const size_t s) {
    assert(layer != NULL && s > 0);
    float* new_layer = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++) {
        new_layer[i] = (layer[i] > 0) ? layer[i] : 0;
    }
    return new_layer;
}

float* lrelu_activation(const float* layer, const size_t s) {
    assert(layer != NULL && s > 0);
    float* new_layer = calloc(s, sizeof(float));
    float a = 0.01f; //(alpha < 0) ? 0.01f : alpha;
    for (int i = 0; i < s; i++) {
        new_layer[i] = (layer[i] > 0) ? layer[i] : (a * layer[i]);
    }
    return new_layer;
}

float* lrelu_activation2(const float* layer, const size_t s, const float alpha) {
    assert(layer != NULL && s > 0);
    float* new_layer = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++) {
        new_layer[i] = (layer[i] > 0) ? layer[i] : (alpha * layer[i]);
    }
    return new_layer;
}

// sigmoid(x) := 1 / (1 + e^-x) = e^x / (e^x + 1)
float* sigmoid_activation(const float* layer, const size_t s) {
    assert(layer != NULL && s > 0);
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
    assert(layer != NULL && s > 0);
    float* new_layer = calloc(s, sizeof(float));
    for (int i = 0; i < s; i++) {
        new_layer[i] = tanhf(layer[i]);
    }
    return new_layer;
}

// softmax / normalized exp
// consider not normalizing input, since on some inputs it's not needed?
float* softmax_activation(const float* layer, const size_t s) {
    assert(layer != NULL && s > 0);
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

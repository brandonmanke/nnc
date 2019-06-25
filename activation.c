#include "activations.h"

#include <stdlib.h>

// ReLU activation function
// consider sigmoid also
// just take float*? would work for both vector and matrix
float* relu(const float* layer, const int size) {
    float* new_data = calloc(size, sizeof(float));
    for (int i = 0; i < size; i++) {
        new_data[i] = (layer[i] > 0) ? layer[i] : 0;
    }
    return new_data;
}

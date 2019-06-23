#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

void create_vector(vector_t* v, const int size) {
    v->size = size;
    v->data = calloc(size, sizeof(float));
}

// vector_t expected to have specified size
void rand_vector(vector_t* v, const int size, const int range) {
    create_vector(v, size);
    for (int i = 0; i < size; i++) {
        float div = (RAND_MAX / range);
        v->data[i] = (float) (rand() % (2 * range + 1)) - range;
    }
}

void free_vector(vector_t* v) {
    if (v == NULL) {
        fprintf(stderr, "vector is NULL\n");
        return;
    }
    if (v->size < 1 || v->data == NULL) {
        fprintf(stderr, "%d\n", v->size);
        fprintf(stderr, "vector data is NULL or size 0\n");
        return;
    }
    free(v->data);
    v->size = 0;
}

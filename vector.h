#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
    int size;
    float* data;
} vector_t;

void create_vector(vector_t* v, const int size);

// random vector within [-range,range]
void rand_vector(vector_t* v, const int size, const int range);

void free_vector(vector_t* v);

#endif

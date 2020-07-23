#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef struct matrix {
    int row;
    int col;
    float* data;
} matrix_t;

// Not sure if needed? Could just make an array of matrices.
typedef struct tensor {
    matrix_t* matrices;
    int dimension;
} tensor_t;

void create_tensor(tensor_t* t, const int dim, const int row, const int col);

void rand_tensor(tensor_t* t, const int dim, const int row, const int col, const int range);

void free_tensor(tensor_t* t);

// unsure about design of functions/api
// pass by pointer vs copy by value and return
void create_matrix(matrix_t* m, const int row, const int col);

void rand_matrix(matrix_t* m, const int row, const int col, const int range);

void identity_matrix(matrix_t* m, const int row, const int col);

matrix_t mult_matrix(const matrix_t* m, const matrix_t* n);

matrix_t scalar_mult_matrix(const matrix_t* m, const float scalar);

matrix_t pow_matrix(const matrix_t* m, const float pow);

matrix_t add_matrix(const matrix_t* m, const matrix_t* n);

matrix_t sub_matrix(const matrix_t* m, const matrix_t* n);

float sum_matrix(const matrix_t* m);

matrix_t transpose_matrix(const matrix_t* m);

float trace_matrix(const matrix_t* m);

float norm_matrix(const matrix_t* m, const int n);

//float determinant_matrix(const matrix_t* m); // TODO

//matrix_t inverse_matrix(const matrix_t* m); // TODO

matrix_t copy_matrix(const matrix_t* m);

//void swap_row_matrix(matrix_t* m, const int i, const int j);

// print matrix to stream
void print_matrix(FILE* stream, const matrix_t* m);

void free_matrix(matrix_t* m);

#endif

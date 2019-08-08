#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
    int row;
    int col;
    float* data;
} matrix_t;

// unsure about design of functions/api
// pass by pointer vs copy by value and return
void create_matrix(matrix_t* m, const int row, const int col);

void rand_matrix(matrix_t* m, const int row, const int col, const int range);

void create_identity_matrix(matrix_t* m, const int row, const int col);

matrix_t mult_matrix(const matrix_t* m, const matrix_t* n);

matrix_t scalar_mult_matrix(const matrix_t* m, const float scalar);

matrix_t add_matrix(const matrix_t* m, const matrix_t* n);

matrix_t transpose_matrix(const matrix_t* m);

float trace_matrix(const matrix_t* m);

matrix_t copy_matrix(const matrix_t* m);

// print matrix to stdout
void print_matrix(const matrix_t* m);

void free_matrix(matrix_t* m);

#endif

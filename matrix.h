#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
    int row;
    int col;
    float* data;
} matrix_t;

// unsure about design of functions
// whether we want to pass by pointer vs copy by value and return
void create_matrix(matrix_t* m, const int row, const int col);

void rand_matrix(matrix_t* m, const int row, const int col, const int range);

matrix_t matrix_mult(matrix_t* m, matrix_t* n);

matrix_t matrix_mult_scalar(matrix_t* m, const int scalar);

matrix_t matrix_add(matrix_t* m, matrix_t* n);

matrix_t transpose_matrix(matrix_t* m);

matrix_t copy_matrix(matrix_t* m);

void print_matrix(matrix_t* m);

void free_matrix(matrix_t* m);

#endif

#include "matrix.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>

// row and col unsigned?
void create_matrix(matrix_t* m, const int row, const int col) {
    assert(m != NULL);
    assert(row > 0 && col > 0);
    m->row = row;
    m->col = col;
    m->data = calloc(row * col, sizeof(float));
}

// random MxN matrix within [-range,range]
void rand_matrix(matrix_t* m, const int row, const int col, const int range) {
    create_matrix(m, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            m->data[i*m->col + j] = (float) (rand() % (2 * range + 1)) - range;
        }
    }
}

void identity_matrix(matrix_t* m, const int row, const int col) {
    assert(row == col);
    create_matrix(m, row, col);
    for (int i = 0; i < row; i++) {
        m->data[i*m->col + i] = 1.0f;
    }
}

matrix_t mult_matrix(const matrix_t* m, const matrix_t *n) {
    assert(m != NULL && n != NULL);
    assert(m->col == n->row);
    matrix_t prod;
    create_matrix(&prod, m->row, n->col);
    for (int i = 0; i < prod.row; i++) {
        for (int k = 0; k < m->col; k++) {
            for (int j = 0; j < prod.col; j++) {
                // prod.row == m->row
                // prod.col == n->col
                // m->col == n->row
                // 2D equivalent: prod[i][j] += (m[i][k] * n[k][j]);
                // iterate n by col major & m by row major summing + product
                prod.data[i*prod.col + j] += (m->data[i*m->col + k] * n->data[k*n->row + j]);
            }
        }
    }
    return prod;
}

matrix_t scalar_mult_matrix(const matrix_t* m, const float scalar) {
    assert(m != NULL);
    matrix_t prod;
    create_matrix(&prod, m->row, m->col);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            prod.data[i*m->col + j] = scalar * m->data[i*m->col + j];
        }
    }
    return prod;
}

// consider alt functions where we modify m directly (i.e. m is sum)
matrix_t add_matrix(const matrix_t* m, const matrix_t* n) {
    assert(m != NULL && n != NULL);
    assert((m->row == n->row) && (m->col == n->col));
    matrix_t sum;
    create_matrix(&sum, m->row, m->col);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            int index = i*m->col + j;
            sum.data[index] = m->data[index] + n->data[index];
        }
    }
    return sum;
}

// weighted sum
matrix_t axpy_matrix(const float scalar, const matrix_t* m, const matrix_t* n) {
    assert(m != NULL && n != NULL);
    assert((m->row == n->row) && (m->col == n->col));
    matrix_t scaled = scalar_mult_matrix(m, scalar);
    return add_matrix(&scaled, n);
}

matrix_t transpose_matrix(const matrix_t* m) {
    assert(m != NULL);
    matrix_t t;
    create_matrix(&t, m->col, m->row);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            t.data[j*m->row + i] = m->data[i*m->col + j];
        }
    }
    return t;
}

// should still work for non-square matrices
float trace_matrix(const matrix_t* m) {
    assert(m != NULL);
    float trace = 0.0f;
    for (int i = 0; i < m->row; i++) {
        trace += m->data[i*m->col + i];
    }
    return trace;
}

// calculates L^n norm of matrix given a degree n
float norm_matrix(const matrix_t* m, const int n) {
    assert(m != NULL && n > 0);
    float norm = 0.0f;
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            norm += powf(m->data[i*m->col + j], n);
        }
    }
    return powf(norm, 1.0f/n);
}

// Can use gaussian elimination to convert m to 
// upper triangular matrix U det(U) = product of diagonal
// so det(m) = -1^m * det(U) where m is number of row changes made
// to convert m to U
float determinant_matrix(const matrix_t* m) {
    assert(m != NULL);
    assert(m->row == m->col);
    // TODO
    // convert m to upper triangular using row reduction 
    return 0.0f;
}

// calculate inverse
// inverse = (1/det(m)) * m
matrix_t inverse_matrix(const matrix_t* m) {
    assert(m != NULL);
    float determinant = determinant_matrix(m);
    return scalar_mult_matrix(m, 1 / determinant);
}

matrix_t copy_matrix(const matrix_t* m) {
    assert(m != NULL);
    matrix_t c;
    create_matrix(&c, m->row, m->col);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            c.data[i*c.col + j] = m->data[i*m->col + j];
        }
    }
    return c;
}

// print to stream
void print_matrix(FILE* stream, const matrix_t* m) {
    assert(m != NULL);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            if (j == 0) {
                fprintf(stream, "| ");
            }
            fprintf(stream, "%.3f ", m->data[i*m->col + j]);
        }
        fprintf(stream, "|\n");
    }
}

void free_matrix(matrix_t* m) {
    if (m == NULL) {
        fprintf(stderr, "matrix is NULL\n");
        return;
    }
    if (m->row < 1 || m->col < 1 || m->data == NULL) {
        fprintf(stderr, "matrix data NULL or row/col 0\n");
        return;
    }
    free(m->data);
    m->row = 0;
    m->col = 0;
}

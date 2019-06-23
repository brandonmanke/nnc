#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

void create_matrix(matrix_t* m, const int row, const int col) {
    m->row = row;
    m->col = col;
    m->data = calloc(row * col, sizeof(float));
}

// random MxN matrix within [-range,range]
void rand_matrix(matrix_t* m, const int row, const int col, const int range) {
    create_matrix(m, row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            float div = (RAND_MAX / range);
            m->data[i*m->col + j] = (float) (rand() % (2 * range + 1)) - range;
        }
    }
}

matrix_t transpose_matrix(matrix_t* m) {
    matrix_t t;
    create_matrix(&t, m->col, m->row);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            t.data[j*m->row + i] = m->data[i*m->col + j];
        }
    }
    return t;
}

matrix_t copy_matrix(matrix_t* m) {
    matrix_t c;
    create_matrix(&c, m->row, m->col);
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            c.data[i*c.col + j] = m->data[i*m->col + j];
        }
    }
    return c;
}


// print to stdout
void print_matrix(matrix_t* m) {
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->col; j++) {
            if (j == 0) {
                printf("| ");
            }
            printf("%.3f ", m->data[i*m->col + j]);
        }
        printf("|\n");
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

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "../types.h"

#define ALIGNMENT 64

typedef struct matrix_s {
    size_t rows;
    size_t cols;
    size_t size;
    f64 *data;
} matrix_t;

matrix_t *matrix_rand_init(const size_t rows, const size_t cols);
void matrix_free(matrix_t *m);
i32 matrix_write(matrix_t *m, const char *filename);
matrix_t *matrix_read(const char *filename);
matrix_t *matrix_multiply(matrix_t *a, matrix_t *b);
f64 matrix_reduction(matrix_t *m);
i32 matrix_scale(matrix_t *a, const f64 c);

#endif

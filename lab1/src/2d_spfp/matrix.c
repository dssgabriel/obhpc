#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "matrix.h"

static inline
matrix_t *matrix_init(const size_t rows, const size_t cols) {
    matrix_t *m = aligned_alloc(ALIGNMENT, sizeof(matrix_t));
    if (!m) {
        return NULL;
    }

    m->rows = rows;
    m->cols = cols;
    m->data = (f32**)(aligned_alloc(ALIGNMENT, rows * sizeof(f32*)));
	if (!m->data) {
    	return NULL;
	}

	for (size_t i = 0; i < rows; i++) {
    	m->data[i] = (f32*)(aligned_alloc(ALIGNMENT, cols * sizeof(f32)));
	}
	if (!*m->data) {
    	return NULL;
	}

	return m;
}


///
matrix_t *matrix_rand_init(const size_t rows, const size_t cols) {
    matrix_t *m = matrix_init(rows, cols);
    if (!m) {
        return NULL;
    }

	srand(getpid());
	for (size_t i = 0; i < m->rows; i++) {
    	for (size_t j = 0; j < m->cols; j++) {
        	f32 value = ((f32)(rand() / (f32)(RAND_MAX)) * m->rows * m->cols);
        	u8 sign = rand() % 2;

    		if (sign) {
        		m->data[i][j] = value;
    		} else {
        		m->data[i][j] = -value;
    		}
    	}
	}

    return m;
}

void matrix_free(matrix_t* m) {
    if (!m) {
        printf("error: matrix is already null\n");
        return;
    }

	for (size_t i = 0; i < m->rows; i++) {
    	free(m->data[i]);
	}
    free(m->data);
    free(m);
}

i32 matrix_write(matrix_t *m, const char *filename) {
    if (!m || !filename) {
        printf("error: invalid function arguments (matrix or filename is null)\n");
        exit(EXIT_FAILURE);
    }

	FILE *fp = fopen(filename, "wb");
	if (!fp) {
    	printf("error: failed to open file %s\n", filename);
    	exit(EXIT_FAILURE);
	}

	fprintf(fp, "%lu %lu\n", m->rows, m->cols);
	for (size_t i = 0; i < m->rows; i++) {
    	for (size_t j = 0; j < m->cols; j++) {
        	fprintf(fp, "%f ", m->data[i][j]);
    	}
	}

	fclose(fp);
	return 1;
}

matrix_t *matrix_read(const char *filename) {
    if (!filename) {
        printf("error: invalid function argument (filename is null)\n");
        exit(EXIT_FAILURE);
    }

	f32 value = 0.0;
	size_t rows = 0, cols = 0;
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
    	printf("error: failed to open file %s\n", filename);
    	exit(EXIT_FAILURE);
    }

    fscanf(fp, "%lu %lu", &rows, &cols);
    if (!rows || !cols) {
        printf("error: failed to read from file %s\n", filename);
        exit(EXIT_FAILURE);
    }

	matrix_t *m = matrix_init(rows, cols);
	if (!m) {
    	return NULL;
	}

	for (size_t i = 0; i < m->rows; i++) {
    	for (size_t j = 0; j < m->cols; j++) {
        	fscanf(fp, "%f ", &value);
        	m->data[i][j] = value;
    	}
	}

	fclose(fp);
    return m;
}

inline
matrix_t *matrix_multiply(matrix_t *a, matrix_t *b) {
    if (!a || !b) {
        printf("error: invalid function arguments (one or both matrices are null)\n");
        exit(EXIT_FAILURE);
    }

    if (a->cols != b->rows) {
        printf("error: cannot multiply matrices (A.rows != B.cols)\n");
        exit(EXIT_FAILURE);
    }

    matrix_t *c = matrix_init(a->rows, b->cols);
    if (!c) {
        return NULL;
    }

	for (size_t i = 0; i < a->rows; i++) {
    	for (size_t j = 0; j < b->rows; j++) {
        	float loc = a->data[i][j];
            for (size_t k = 0; k < b->cols; k++) {
                c->data[i][k] += loc * b->data[j][k];
            }
        }
    }

    return c;
}

inline
f32 matrix_reduction(matrix_t *m) {
    if (!m) {
        printf("error: invalid function argument (matrix is null)\n");
        exit(EXIT_FAILURE);
    }

    f32 acc = 0.0;
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            acc += m->data[i][j];
        }
    }

    return acc;
}

inline
i32 matrix_scale(matrix_t *m, const f32 c) {
    if (!m) {
        printf("error: invalid function argument (matrix is null)\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            m->data[i][j] *= c;
        }
    }

    return 1;
}

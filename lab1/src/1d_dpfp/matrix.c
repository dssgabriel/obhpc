#include <omp.h>
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
    m->size = rows * cols;
    m->data = (f64*)(aligned_alloc(ALIGNMENT, rows * cols * sizeof(f64)));
	if (!m->data) {
    	return NULL;
	}

	return m;
}

matrix_t *matrix_rand_init(const size_t rows, const size_t cols) {
    matrix_t *m = matrix_init(rows, cols);
    if (!m) {
        return NULL;
    }

    // seed with `getpid()` rather than `time()`
	srand(getpid());
	for (size_t i = 0; i < m->size; i++) {
    	f64 value = ((f64)(rand() / (f64)(RAND_MAX)) * m->size);
    	u8 sign = rand() % 2;

		// create random negative values
		if (sign) {
    		m->data[i] = value; 
		} else {
    		m->data[i] = -value; 
		}
	}

    return m;
}

void matrix_free(matrix_t* m) {
    if (!m) {
        printf("error: matrix is already null\n");
        return;
    }

    free(m->data);
    free(m);
}

i32 matrix_write(matrix_t *m, const char *filename) {
    if (!m || !filename) {
        printf("error: invalid function arguments (matrix or filename is null)\n");
        exit(EXIT_FAILURE);
    }

	// open file in write binary mode
	FILE *fp = fopen(filename, "wb");
	if (!fp) {
    	printf("error: failed to open file %s\n", filename);
    	exit(EXIT_FAILURE);
	}

	// write matrix dimensions to file
	fprintf(fp, "%lu %lu\n", m->rows, m->cols);
	for (size_t i = 0; i < m->size; i++) {
    	// write values to file
    	fprintf(fp, "%lf ", m->data[i]);
	}

	fclose(fp);
	return 1;
}

matrix_t *matrix_read(const char *filename) {
    if (!filename) {
        printf("error: invalid function argument (filename is null)\n");
        exit(EXIT_FAILURE);
    }

    f64 value = 0.0;
	size_t rows = 0, cols = 0;

	// open file in read binary mode
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
    	printf("error: failed to open file %s\n", filename);
    	exit(EXIT_FAILURE);
    }

	// read matrix dimensions from file
    fscanf(fp, "%lu %lu", &rows, &cols);
    if (!rows || !cols) {
        printf("error: failed to read from file %s\n", filename);
        exit(EXIT_FAILURE);
    }

	matrix_t *m = matrix_init(rows, cols);
	if (!m) {
    	return NULL;
	}

	for (size_t i = 0; i < m->size; i++) {
    	// read values from file
    	fscanf(fp, "%lf ", &value);
        m->data[i] = value;
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

	#pragma omp parallel for
	for (size_t i = 0; i < a->rows; i++) {
    	for (size_t j = 0; j < b->rows; j++) {
        	float loc = a->data[i * a->cols + j];
            for (size_t k = 0; k < b->cols; k++) {
                c->data[i * c->cols + k] += loc * b->data[j * b->cols + k];
            }
        }
    }

    return c;
}

inline
f64 matrix_reduction(matrix_t *m) {
    if (!m) {
        printf("error: invalid function argument (matrix is null)\n");
        exit(EXIT_FAILURE);
    }

    f64 acc = 0.0;
    for (size_t i = 0; i < m->size; i++) {
        acc += m->data[i];
    }

    return acc;
}

inline
i32 matrix_scale(matrix_t *a, const f64 c) {
    if (!a) {
        printf("error: invalid function argument (matrix is null)\n");
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < a->size; i++) {
        a->data[i] *= c;
    }

    return 1;
}

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        return printf("usage: %s MATRIX1 MATRIX2 MATRIX3\n", argv[0]), 1;
    }

	matrix_t* a = matrix_read(argv[1]);
	matrix_t* b = matrix_read(argv[2]);
	if (!a || !b) {
    	return printf("error: failed to read matrices from files\n"), 2;
	}

	matrix_t* c = matrix_multiply(a, b);
	if (!c) {
    	return printf("error: failed to multiply matrices\n"), 3;
	}

	i32 ret = matrix_write(c, argv[3]);
	if (ret < 0) {
    	return printf("error: failed to write matrix to file %s\n", argv[3]), 4;
	}

	matrix_free(a);
	matrix_free(b);
	matrix_free(c);
    return 0;
}

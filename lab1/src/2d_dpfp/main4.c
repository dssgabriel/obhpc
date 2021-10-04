#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        return printf("usage: %s MATRIX CONSTANT\n", argv[0]), 1;
    }

	matrix_t* m = matrix_read(argv[1]);
	if (!m) {
    	return printf("error: failed to read matrix from file\n"), 2;
	}

	f64 c = atof(argv[2]);
	matrix_scale(m, c);

	i32 ret = matrix_write(m, argv[1]);
	if (ret < 0) {
    	return printf("error: failed to write matrix to file %s\n", argv[1]), 3;
	}

	matrix_free(m);
    return 0;
}

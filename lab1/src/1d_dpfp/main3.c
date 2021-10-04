#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        return printf("usage: %s MATRIX\n", argv[0]), 1;
    }

	matrix_t* m = matrix_read(argv[1]);
	if (!m) {
    	return printf("error: failed to read matrix from file\n"), 2;
	}

	f64 reduc = matrix_reduction(m);
	printf("Reduction of %s: %lf\n", argv[1], reduc);

	matrix_free(m);
    return 0;
}

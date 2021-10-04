#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        return printf("usage: %s NB_ROWS NB_COLS OUTPUT_FILE\n", argv[0]), 1;
    }

    size_t rows = atoll(argv[1]);
    size_t cols = atoll(argv[2]);

	matrix_t* m = matrix_rand_init(rows, cols);
	if (!m) {
    	return printf("error: failed to allocate memory for matrix\n"), 2;
	}

	i32 ret = matrix_write(m, argv[3]);
	if (ret < 0) {
    	return printf("error: failed to write to file %s\n", argv[3]), 3;
	}

	matrix_free(m);
    return 0;
}

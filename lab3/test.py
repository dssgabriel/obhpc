import numpy as np
import sys
import time

import mblas

# Python matrix multiplication
def sgemm_py(A, B, C, n):
    for i in range(0, n):
        for j in range(0, n):
            loc = A[i * n + j]
            for k in range(0, n):
                C[i * n + k] += loc * B[j * n + k]

# Time measurement of Python sgemm
def measure_py(A, B, n):
    C = np.zeros((n * n,), dtype=np.float32)

    before = time.perf_counter()
    sgemm_py(A, B, C, n)
    after = time.perf_counter()

    return after - before

# Time measurement of Numpy sgemm
def measure_np(A, B, n):
    C = np.zeros((n, n), dtype=np.float32)
    A = A.reshape(n, n)
    B = B.reshape(n, n)

    before = time.perf_counter()
    C = np.dot(A, B)
    after = time.perf_counter()

    return after - before

# Time measurement of C sgemm
def measure_c(A, B, n):
    C = np.zeros((n * n,), dtype=np.float32)

    before = time.perf_counter()
    mblas.sgemm_c(A, B, C, n)
    after = time.perf_counter()

    return after - before

# Main function
def main():
    size = int(sys.argv[1])

    A = np.random.rand(size * size).astype(np.float32)
    B = np.random.rand(size * size).astype(np.float32)

    elapsed_py = measure_py(A, B, size)
    elapsed_np = measure_np(A, B, size)
    elapsed_c = measure_c(A, B, size)
    #elapsed_avx2 = measure_avx(A, B, size)
    #elapsed_avx512 = measure_avx(A, B, size)

    print("py / c:  ", elapsed_py / elapsed_c);
    print("py / np: ", elapsed_py / elapsed_np);
    print("np / c:  ", elapsed_np / elapsed_c);

if __name__ == "__main__":
    main()

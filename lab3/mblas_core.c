#include <stdlib.h>
#include <unistd.h>

#include "mblas_core.h"

void sgemm(f32 *A, f32 *B, f32 *C, u64 n) {
	for (u64 i = 0; i < n; i++) {
    	for (u64 j = 0; j < n; j++) {
        	f32 loc = A[i * n + j];
            for (u64 k = 0; k < n; k++) {
                C[i * n + k] += loc * B[j * n + k];
            }
        }
    }
}

// f32 *sgemm_AVX(f32 *a, f32 *b, u64 ar, u64 acbr, u64 bc) {}

// f32 *sgemm_AVC512(f32 *a, f32 *b, u64 ar, u64 acbr, u64 bc) {}

// 1 cache line
/*
float dotprod_f32_AVX(
    float *a,
    float *b,
	unsigned long long n
) {
    unsigned long long _n_ = n - (n & 15);
    float r[8] __attribute__((aligned(ALIGN)));
    unsigned long long s = sizeof(float) * _n_;

    __asm__ volatile(
        "xor %%rcx, %%rcx;\n"

        "vxorpd %%ymm0, %%ymm0, %%ymm0;\n"
        "vxorpd %%ymm1, %%ymm1, %%ymm1;\n"

        "1:;\n"

        "vmovups   (%[_a_], %%rcx), %%ymm2;\n"
        "vmovups 32(%[_a_], %%rcx), %%ymm3;\n"

        "vfmadd231ps   (%[_b_], %%rcx), %%ymm2, %%ymm0;\n"
        "vfmadd231ps 32(%[_b_], %%rcx), %%ymm3, %%ymm1;\n"

        "add $64, %%rcx;\n"
        "cmp %[_s_], %%rcx;\n"
        "jl 1b;\n"

        "vaddps %%ymm1, %%ymm0, %%ymm0;\n"

        "vmovaps %%ymm0, (%[_r_]);\n"

        : //output
        : //input
         [_a_] "r" (a),
         [_b_] "r" (b),
         [_s_] "r" (s),
         [_r_] "r" (r)
        : //clobber
         "cc", "memory", "rcx",
         "ymm0", "ymm1", "ymm2", "ymm3"
     );

    for (unsigned long long i = _n_; i < n; i++) {
        r[0] += a[i];
    }
  
    return (r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] + r[7]);
}
*/

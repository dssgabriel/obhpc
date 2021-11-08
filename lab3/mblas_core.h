#pragma once

#include "types.h"

#define ALIGN 64

void sgemm(f32 *A, f32 *B, f32 *C, u64 n);
// void sgemm_avx2(f32 *A, f32 *B, f32 *C, u64 n);
// void sgemm_avx512(f32 *A, f32 *B, f32 *C, u64 n);

#ifndef CLAW_JS_TESTS_NAIVE_IMPL_H
#define CLAW_JS_TESTS_NAIVE_IMPL_H

#include <stdlib.h>

int naive_cpu_matmul(float *A,
        unsigned long long *shape_A, // shape of matrix A
        float *B,
        unsigned long long *shape_B, //  shape of matrix B
        float *C) {

        if (shape_A[1] != shape_B[0]) return -1;

        size_t M = shape_A[0]; // row size of A
        size_t N = shape_B[1]; // col size of B
        size_t K = shape_A[1]; // col size of A, row size of B

        for (size_t m = 0; m < M; m++) {
                for (size_t n = 0; n < N; n++) {
                        float acc = 0;
                        for (size_t k = 0; k < K; k++) {
                                acc += A[k*M + m] * B[n*K + k];
                        }
                        C[n*M + m] = acc;
                }
        }
        return 0;
}

#endif // CLAW_JS_TESTS_NAIVE_IMPL_H
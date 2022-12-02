// =================================================================================================
//
// Matrices in column-major format
// A: K columns, M rows
// B: N columns, K rows
// C: N columns, M rows
//                         
//                   N     
//                o-----o  
//                |     |  
//              K | [B] |  
//                |     |  
//                o-----o  
//        K          N     
//    o-------o   o-----o  
//  M |  [A]  | M | [C] |  
//    |       |   |     |  
//    o-------o   o-----o  
//                         
//
// C-code for column-major matrix multiplication with alpha=1 and beta=0:
//
// for (int m=0; m<M; m++) {
//     for (int n=0; n<N; n++) {
//         float acc = 0.0f;
//         for (int k=0; k<K; k++) {
//             acc += A[k*M + m] * B[n*K + k];
//         }
//         C[n*M + m] = acc;
//     }
// }
// 
// Credits: Cedric Nugteren, @CNugteren on GH.
//
// =================================================================================================

#ifndef CLAW_JS_MATMUL_H
#define CLAW_JS_MATMUL_H

#include <stdint.h>
#include <stddef.h>

int matmul(float* A,
        size_t* shape_A, // shape of matrix A
        float* B,
        size_t* shape_B, //  shape of matrix B
        float* C)
{

    if (shape_A[1]!=shape_B[0]) return -1;

    size_t M = shape_A[0]; // row size of A
    size_t N = shape_B[1]; // col size of B
    size_t K = shape_A[1]; // col size of A, row size of B

    for (size_t m = 0; m<M; m++) {
        for (size_t n = 0; n<N; n++) {
            float acc = 0;
            for (size_t k = 0; k<K; k++) {
                acc += A[k*M+m]*B[n*K+k];
            }
            C[n*M+m] = acc;
        }
    }
    return 0;
}

#endif
#ifndef CLAW_JS_INCLUDE_CLAW_MATMUL_H
#define CLAW_JS_INCLUDE_CLAW_MATMUL_H

#include "defines.h"
#include "error.h"
#include "matrix.h"

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

claw_err claw_matmul(struct claw_mat *lhs, struct claw_mat *rhs, struct claw_mat *res);

#endif //CLAW_JS_INCLUDE_CLAW_MATMUL_H

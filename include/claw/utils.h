#ifndef CLAW_JS_UTILS_H
#define CLAW_JS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/*
void print_matrix(float* mat, size_t shape[2])
{

    printf("\n");
    for (size_t i = 0; i<shape[0]; i++) {
        printf("[ ");
        for (size_t j = 0; j<shape[1]-1; j++) {
            printf("%-7.1f", mat[i*shape[1]+j]);
        }
        printf("%.1f ]\n", mat[i*shape[1]+(shape[1]-1)]);
    }
    printf("Shape: ( %zu, %zu )", shape[0], shape[1]);
    printf("\n");
}
*/

size_t claw_dtype_byte_size(enum claw_dtype type);

#define CLK_DUR_IN_SEC(s, e) (((double)e - s) / CLOCKS_PER_SEC)

#endif //CLAW_JS_UTILS_H

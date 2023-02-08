#ifndef CLAW_JS_UTILS_H
#define CLAW_JS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"

size_t claw_dtype_byte_size(enum claw_dtype type);
double claw_get_rand_unit();
float claw_get_rand_unitf();

#define CLK_DUR_IN_SEC(s, e) (((double)e - s) / CLOCKS_PER_SEC)
#define CLK_DUR_IN_MS(s, e) (CLK_DUR_IN_SEC(s, e) * 1000)

#endif //CLAW_JS_UTILS_H

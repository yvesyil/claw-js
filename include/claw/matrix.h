#ifndef CLAW_JS_MATRIX_H
#define CLAW_JS_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "error.h"

struct claw_mat {
	void *data;
	enum claw_dtype dtype;
	claw_dlen dlen[2];
};

claw_err claw_create_matrix(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			    enum claw_dtype dtype);

claw_err claw_create_ones(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			  enum claw_dtype dtype);

claw_err claw_free(struct claw_mat *mat);

void claw_print_matrix(FILE *fp, struct claw_mat *mat);

#endif // CLAW_JS_MATRIX_H

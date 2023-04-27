#ifndef CLAW_JS_MATRIX_H
#define CLAW_JS_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "error.h"
#include "utils.h"

#define CLAW_MATRIX_BSIZE(mat) mat->dlen[0] * mat->dlen[1] * claw_dtype_byte_size(mat->dtype)

struct claw_mat {
	void *data;
	enum claw_dtype dtype;
	claw_dlen dlen[2];
};


claw_err claw_create_matrix(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			    enum claw_dtype dtype);

claw_err claw_create_matrix_fill(struct claw_mat *mat, claw_dlen row,
				 claw_dlen col, enum claw_dtype dtype,
				 void *val);
/**
 * Creates a new matrix with values between 0 and 1 inclusive (unit interval).
 * @param mat
 * @param row
 * @param col
 * @param dtype
 * @return
 */
claw_err claw_create_matrix_rand_unit(struct claw_mat *mat, claw_dlen row,
				      claw_dlen col, enum claw_dtype dtype);

claw_err claw_create_matrix_identity(struct claw_mat *mat, claw_dlen row,
				     claw_dlen col, enum claw_dtype dtype);

claw_err claw_matrix_get_idx(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			     void *val);
claw_err claw_matrix_set_idx(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			     void *val);

claw_err claw_matrix_transpose(struct claw_mat *mat);

claw_err claw_matrix_cast_inplace(struct claw_mat *mat, enum claw_dtype dtype);
claw_err claw_matrix_copy(struct claw_mat *mat, struct claw_mat *res);

claw_err claw_free(struct claw_mat *mat);

void claw_print_matrix(FILE *fp, struct claw_mat *mat);
void claw_print_matrix_stdout(struct claw_mat *mat);

#endif // CLAW_JS_MATRIX_H

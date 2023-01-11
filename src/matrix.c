#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

#define DEBUG

claw_err claw_create_matrix(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			   enum ClawDType dtype)
{
	mat->dlen[0] = row;
	mat->dlen[1] = col;
	mat->dtype = dtype;

	return 0;
}

claw_err claw_create_ones(struct ClawMat *mat, claw_dlen row, claw_dlen col, enum ClawDType dtype)
{
	claw_err err = claw_create_matrix(mat, row, col, dtype);
	if (err != 0) {
		return err;
	}

	switch (mat->dtype) {
	case CLAW_INT8:
		_CREATE_ONES(int8_t, mat);
		break;
	case CLAW_INT16:
		_CREATE_ONES(int16_t, mat);
		break;
	case CLAW_INT32:
		_CREATE_ONES(int32_t, mat);
		break;
	case CLAW_INT64:
		_CREATE_ONES(int64_t, mat);
		break;
	case CLAW_FLT32:
		_CREATE_ONES(float, mat);
		break;
	case CLAW_FLT64:
		_CREATE_ONES(double, mat);
		break;
	}

	return 0;
}

claw_err claw_matmul(struct ClawMat *a, struct ClawMat *b, struct ClawMat *c)
{
}

claw_err claw_free(struct ClawMat *mat)
{
	free(mat->data);
}
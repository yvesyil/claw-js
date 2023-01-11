#include <stdlib.h>
#include <stdio.h>

#include "../include/claw/matrix.h"

void claw_print_matrix(FILE *fp, struct ClawMat *mat)
{
	fprintf(fp, "\n");
	switch (mat->dtype) {
	case CLAW_INT8:
		__CLAW_PRINT_MAT(fp, int8_t, mat, "hhd");
		break;
	case CLAW_UINT8:
		__CLAW_PRINT_MAT(fp, uint8_t, mat, "hhu");
		break;
	case CLAW_INT16:
		__CLAW_PRINT_MAT(fp, int16_t, mat, "hd");
		break;
	case CLAW_UINT16:
		__CLAW_PRINT_MAT(fp, uint16_t, mat, "hu");
		break;
	case CLAW_INT32:
		__CLAW_PRINT_MAT(fp, int32_t, mat, "d");
		break;
	case CLAW_UINT32:
		__CLAW_PRINT_MAT(fp, uint32_t, mat, "u");
		break;
	case CLAW_INT64:
		__CLAW_PRINT_MAT(fp, int64_t, mat, "lld");
		break;
	case CLAW_UINT64:
		__CLAW_PRINT_MAT(fp, uint64_t, mat, "llu");
		break;
	case CLAW_FLT32:
		__CLAW_PRINT_MAT(fp, float, mat, ".1f");
		break;
	case CLAW_FLT64:
		__CLAW_PRINT_MAT(fp, double, mat, ".2lf");
		break;
	}
	fprintf(fp, "\n");
}

claw_err claw_create_matrix(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			    enum ClawDType dtype)
{
	mat->data = NULL;
	mat->dlen[0] = row;
	mat->dlen[1] = col;
	mat->dtype = dtype;

	return 0;
}

claw_err claw_create_ones(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			  enum ClawDType dtype)
{
	claw_err err = claw_create_matrix(mat, row, col, dtype);
	if (err != 0) {
		return err;
	}

	switch (mat->dtype) {
	case CLAW_INT8:
		__CLAW_CREATE_ONES(int8_t, mat);
		break;
	case CLAW_UINT8:
		__CLAW_CREATE_ONES(uint8_t, mat);
		break;
	case CLAW_INT16:
		__CLAW_CREATE_ONES(int16_t, mat);
		break;
	case CLAW_UINT16:
		__CLAW_CREATE_ONES(uint16_t, mat);
		break;
	case CLAW_INT32:
		__CLAW_CREATE_ONES(int32_t, mat);
		break;
	case CLAW_UINT32:
		__CLAW_CREATE_ONES(uint32_t, mat);
		break;
	case CLAW_INT64:
		__CLAW_CREATE_ONES(int64_t, mat);
		break;
	case CLAW_UINT64:
		__CLAW_CREATE_ONES(uint64_t, mat);
		break;
	case CLAW_FLT32:
		__CLAW_CREATE_ONES(float, mat);
		break;
	case CLAW_FLT64:
		__CLAW_CREATE_ONES(double, mat);
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
	return 0;
}
#ifndef CLAW_JS_MATRIX_H
#define CLAW_JS_MATRIX_H

#include "utils.h"

enum ClawDType {
	CLAW_INT8,
	CLAW_UINT8,
	CLAW_INT16,
	CLAW_UINT16,
	CLAW_INT32,
	CLAW_UINT32,
	CLAW_INT64,
	CLAW_UINT64,
	CLAW_FLT32,
	CLAW_FLT64,
};

typedef unsigned long long claw_dlen;

typedef int claw_err;

struct ClawMat {
	void *data;
	enum ClawDType dtype;
	claw_dlen *dlen; // size 2
};

claw_err claw_create_matrix(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			    enum ClawDType dtype);
claw_err claw_create_ones(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			  enum ClawDType dtype);
claw_err claw_matmul(struct ClawMat *a, struct ClawMat *b, struct ClawMat *c);
claw_err claw_free(struct ClawMat *mat);

#define _CREATE_ONES(type, mat)                                             \
	do {                                                                \
		mat->data =                                                 \
			malloc(mat->dlen[0] * mat->dlen[1] * sizeof(type)); \
		for (size_t i = 0;                                          \
		     i < mat->dlen[0] * mat->dlen[1] * sizeof(type); i++) { \
			CLAW_INDEX(type, mat->data, i) = 1;                 \
		}                                                           \
	} while (0);

#endif // CLAW_JS_MATRIX_H

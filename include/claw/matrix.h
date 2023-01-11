#ifndef CLAW_JS_MATRIX_H
#define CLAW_JS_MATRIX_H

#include "defines.h"
#include "error.h"

struct ClawMat {
	void *data;
	enum ClawDType dtype;
	claw_dlen dlen[2];
};

claw_err claw_create_matrix(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			    enum ClawDType dtype);
claw_err claw_create_ones(struct ClawMat *mat, claw_dlen row, claw_dlen col,
			  enum ClawDType dtype);
claw_err claw_matmul(struct ClawMat *a, struct ClawMat *b, struct ClawMat *c);
claw_err claw_free(struct ClawMat *mat);
void claw_print_matrix(FILE *fp, struct ClawMat *mat);

#define CLAW_INDEX(type, data, idx) *((type *)(data) + idx)

#define __CLAW_CREATE_ONES(type, mat)                                             \
	do {                                                                \
		mat->data =                                                 \
			malloc(mat->dlen[0] * mat->dlen[1] * sizeof(type)); \
		for (size_t i = 0;                                          \
		     i < mat->dlen[0] * mat->dlen[1] * sizeof(type); i++) { \
			CLAW_INDEX(type, mat->data, i) = 1;                 \
		}                                                           \
	} while (0);

#define __CLAW_PRINT_MAT(fp, size, mat, ph)                                      \
	do {                                                               \
		for (size_t i = 0; i < mat->dlen[0]; i++) {                \
			fprintf(fp, "[ ");                                 \
			for (size_t j = 0; j < mat->dlen[1] - 1; j++) {    \
				fprintf(fp, "%-7" ph,                     \
					CLAW_INDEX(size, mat->data,        \
						   mat->dlen[1] * i + j)); \
			}                                                  \
			fprintf(fp, "%" ph " ]\n",                        \
				CLAW_INDEX(size, mat->data,                \
					   mat->dlen[1] * i +              \
						   (mat->dlen[1] - 1)));   \
		}                                                          \
	} while (0);

#endif // CLAW_JS_MATRIX_H

#include "claw/matrix.h"
#include "claw/utils.h"

#define CLAW_INDEX(type, data, idx) *((type *)(data) + idx)

#define __CLAW_CREATE_ONES(type, mat)                                       \
	do {                                                                \
		mat->data =                                                 \
			malloc(mat->dlen[0] * mat->dlen[1] * sizeof(type)); \
		for (size_t i = 0;                                          \
		     i < mat->dlen[0] * mat->dlen[1]; i++) {               \
			CLAW_INDEX(type, mat->data, i) = 1;                 \
		}                                                           \
	} while (0);

#define __CLAW_PRINT_MAT(fp, size, mat, ph)                                \
	do {                                                               \
		for (size_t i = 0; i < mat->dlen[0]; i++) {                \
			fprintf(fp, "[ ");                                 \
			for (size_t j = 0; j < mat->dlen[1] - 1; j++) {    \
				fprintf(fp, "%-7" ph,                      \
					CLAW_INDEX(size, mat->data,        \
						   mat->dlen[1] * i + j)); \
			}                                                  \
			fprintf(fp, "%" ph " ]\n",                         \
				CLAW_INDEX(size, mat->data,                \
					   mat->dlen[1] * i +              \
						   (mat->dlen[1] - 1)));   \
		}                                                          \
	} while (0);

void claw_print_matrix(FILE *fp, struct claw_mat *mat)
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

claw_err claw_create_matrix(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			    enum claw_dtype dtype)
{
	mat->data = malloc(row * col * claw_dtype_byte_size(dtype));
	mat->dlen[0] = row;
	mat->dlen[1] = col;
	mat->dtype = dtype;

	return CLAW_SUCCESS;
}

claw_err claw_create_ones(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			  enum claw_dtype dtype)
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

	return CLAW_SUCCESS;
}

claw_err claw_free(struct claw_mat *mat)
{
	free(mat->data);
	return CLAW_SUCCESS;
}
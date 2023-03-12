#include "claw/matrix.h"
#include "claw/utils.h"

#include <string.h>

#define CLAW_INDEX(type, data, idx) *((type *)(data) + idx)

#define CREATE_FILL(type, mat, val)                                         \
	do {                                                                \
		mat->data =                                                 \
			malloc(mat->dlen[0] * mat->dlen[1] * sizeof(type)); \
		for (size_t i = 0; i < mat->dlen[0] * mat->dlen[1]; i++) {  \
			CLAW_INDEX(type, mat->data, i) = val;               \
		}                                                           \
	} while (0);

#define __PRINT_INNER(fp, type, mat, ph, flag)                              \
	do {                                                                \
		if (flag) {                                                 \
			for (size_t j = 0; j < 8; j++) {                    \
				fprintf(fp, "%-7" ph,                       \
					CLAW_INDEX(type, mat->data,         \
						   mat->dlen[1] * i + j));  \
			}                                                   \
			fprintf(fp, "%-7s", "...");                         \
			for (size_t j = mat->dlen[1] - 8; j < mat->dlen[1]; \
			     j++) {                                         \
				fprintf(fp, "%-7" ph,                       \
					CLAW_INDEX(type, mat->data,         \
						   mat->dlen[1] * i + j));  \
			}                                                   \
		} else {                                                    \
			for (size_t j = 0; j < mat->dlen[1]; j++) {         \
				fprintf(fp, "%-7" ph,                       \
					CLAW_INDEX(type, mat->data,         \
						   mat->dlen[1] * i + j));  \
			}                                                   \
		}                                                           \
		fprintf(fp, "\n");                                          \
	} while (0);

#define PRINT_MAT(fp, type, mat, ph, flags)                                 \
	do {                                                                \
		if (flags[0]) {                                             \
			for (size_t i = 0; i < 8; i++) {                    \
				__PRINT_INNER(fp, type, mat, ph, flags[1])  \
			}                                                   \
			for (size_t a = 0; a < 1; a++) {                    \
				for (size_t i = 0; i < 8; i++) {            \
					fprintf(fp, "%-7s", "...");         \
				}                                           \
				if (flags[1]) {                             \
					fprintf(fp, "%-7s", "...");         \
				}                                           \
				for (size_t i = 8; i < 16; i++) {           \
					fprintf(fp, "%-7s", "...");         \
				}                                           \
				fprintf(fp, "\n");                          \
			}                                                   \
			for (size_t i = mat->dlen[0] - 8; i < mat->dlen[0]; \
			     i++) {                                         \
				__PRINT_INNER(fp, type, mat, ph, flags[1])  \
			}                                                   \
		} else {                                                    \
			for (size_t i = 0; i < mat->dlen[0]; i++) {         \
				__PRINT_INNER(fp, type, mat, ph, flags[1])  \
			}                                                   \
		}                                                           \
	} while (0);

#define FILL_DIAGONAL(type, mat, val)                          \
	do {                                                   \
		claw_dlen s = mat->dlen[0];                    \
		for (claw_dlen i = 0; i < s * s; i += s + 1) { \
			CLAW_INDEX(type, mat->data, i) = val;  \
		}                                              \
	} while (0);

void claw_print_matrix(FILE *fp, struct claw_mat *mat)
{
	bool flags[] = { false, false };
	if (mat->dlen[0] > 16) {
		flags[0] = true;
	}
	if (mat->dlen[1] > 16) {
		flags[1] = true;
	}

	fprintf(fp, "\n");
	switch (mat->dtype) {
	case CLAW_INT8:
		PRINT_MAT(fp, int8_t, mat, "hhd", flags);
		break;
	case CLAW_UINT8:
		PRINT_MAT(fp, uint8_t, mat, "hhu", flags);
		break;
	case CLAW_INT16:
		PRINT_MAT(fp, int16_t, mat, "hd", flags);
		break;
	case CLAW_UINT16:
		PRINT_MAT(fp, uint16_t, mat, "hu", flags);
		break;
	case CLAW_INT32:
		PRINT_MAT(fp, int32_t, mat, "d", flags);
		break;
	case CLAW_UINT32:
		PRINT_MAT(fp, uint32_t, mat, "u", flags);
		break;
	case CLAW_INT64:
		PRINT_MAT(fp, int64_t, mat, "lld", flags);
		break;
	case CLAW_UINT64:
		PRINT_MAT(fp, uint64_t, mat, "llu", flags);
		break;
	case CLAW_FLT32:
		PRINT_MAT(fp, float, mat, ".1f", flags);
		break;
	case CLAW_FLT64:
		PRINT_MAT(fp, double, mat, ".2lf", flags);
		break;
	}
	fprintf(fp, "\n");
}

void claw_print_matrix_stdout(struct claw_mat *mat)
{
	claw_print_matrix(stdout, mat);
}

claw_err claw_create_matrix(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			    enum claw_dtype dtype)
{
	//free(mat->data);
	mat->data = calloc(row * col, claw_dtype_byte_size(dtype));
	mat->dlen[0] = row;
	mat->dlen[1] = col;
	mat->dtype = dtype;

	return CLAW_SUCCESS;
}

claw_err claw_create_matrix_fill(struct claw_mat *mat, claw_dlen row,
				 claw_dlen col, enum claw_dtype dtype,
				 void *val)
{
	claw_err err = claw_create_matrix(mat, row, col, dtype);

	switch (mat->dtype) {
	case CLAW_INT8:
		CREATE_FILL(int8_t, mat, *(int8_t *)val);
		break;
	case CLAW_UINT8:
		CREATE_FILL(uint8_t, mat, *(uint8_t *)val);
		break;
	case CLAW_INT16:
		CREATE_FILL(int16_t, mat, *(int16_t *)val);
		break;
	case CLAW_UINT16:
		CREATE_FILL(uint16_t, mat, *(uint16_t *)val);
		break;
	case CLAW_INT32:
		CREATE_FILL(int32_t, mat, *(int32_t *)val);
		break;
	case CLAW_UINT32:
		CREATE_FILL(uint32_t, mat, *(uint32_t *)val);
		break;
	case CLAW_INT64:
		CREATE_FILL(int64_t, mat, *(int64_t *)val);
		break;
	case CLAW_UINT64:
		CREATE_FILL(uint64_t, mat, *(uint64_t *)val);
		break;
	case CLAW_FLT32:
		CREATE_FILL(float, mat, *(float *)val);
		break;
	case CLAW_FLT64:
		CREATE_FILL(double, mat, *(double *)val);
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_matrix_get_idx(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			     void *val)
{
	if (mat->dlen[0] <= row || mat->dlen[1] <= col) {
		return CLAW_MATRIX_E_INDEX_OUT_OF_BOUNDS;
	}

	switch (mat->dtype) {
	case CLAW_INT8:
		*(int8_t *)val =
			CLAW_INDEX(int8_t, mat->data, mat->dlen[0] * row + col);
		break;
	case CLAW_UINT8:
		*(uint8_t *)val = CLAW_INDEX(uint8_t, mat->data,
					     mat->dlen[0] * row + col);
		break;
	case CLAW_INT16:
		*(int16_t *)val = CLAW_INDEX(int16_t, mat->data,
					     mat->dlen[0] * row + col);
		break;
	case CLAW_UINT16:
		*(uint16_t *)val = CLAW_INDEX(uint16_t, mat->data,
					      mat->dlen[0] * row + col);
		break;
	case CLAW_INT32:
		*(int32_t *)val = CLAW_INDEX(int32_t, mat->data,
					     mat->dlen[0] * row + col);
		break;
	case CLAW_UINT32:
		*(uint32_t *)val = CLAW_INDEX(uint32_t, mat->data,
					      mat->dlen[0] * row + col);
		break;
	case CLAW_INT64:
		*(int64_t *)val = CLAW_INDEX(int64_t, mat->data,
					     mat->dlen[0] * row + col);
		break;
	case CLAW_UINT64:
		*(uint64_t *)val = CLAW_INDEX(uint64_t, mat->data,
					      mat->dlen[0] * row + col);
		break;
	case CLAW_FLT32:
		*(float *)val =
			CLAW_INDEX(float, mat->data, mat->dlen[0] * row + col);
		break;
	case CLAW_FLT64:
		*(double *)val =
			CLAW_INDEX(double, mat->data, mat->dlen[0] * row + col);
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_matrix_set_idx(struct claw_mat *mat, claw_dlen row, claw_dlen col,
			     void *val)
{
	if (mat->dlen[0] <= row || mat->dlen[1] <= col) {
		return CLAW_MATRIX_E_INDEX_OUT_OF_BOUNDS;
	}

	switch (mat->dtype) {
	case CLAW_INT8:
		CLAW_INDEX(int8_t, mat->data, mat->dlen[0] * row + col) =
			*(int8_t *)val;
		break;
	case CLAW_UINT8:
		CLAW_INDEX(uint8_t, mat->data, mat->dlen[0] * row + col) =
			*(uint8_t *)val;
		break;
	case CLAW_INT16:
		CLAW_INDEX(int16_t, mat->data, mat->dlen[0] * row + col) =
			*(int16_t *)val;
		break;
	case CLAW_UINT16:
		CLAW_INDEX(uint16_t, mat->data, mat->dlen[0] * row + col) =
			*(uint16_t *)val;
		break;
	case CLAW_INT32:
		CLAW_INDEX(int32_t, mat->data, mat->dlen[0] * row + col) =
			*(int32_t *)val;
		break;
	case CLAW_UINT32:
		CLAW_INDEX(uint32_t, mat->data, mat->dlen[0] * row + col) =
			*(uint32_t *)val;
		break;
	case CLAW_INT64:
		CLAW_INDEX(int64_t, mat->data, mat->dlen[0] * row + col) =
			*(int64_t *)val;
		break;
	case CLAW_UINT64:
		CLAW_INDEX(uint64_t, mat->data, mat->dlen[0] * row + col) =
			*(uint64_t *)val;
		break;
	case CLAW_FLT32:
		CLAW_INDEX(float, mat->data, mat->dlen[0] * row + col) =
			*(float *)val;
		break;
	case CLAW_FLT64:
		CLAW_INDEX(double, mat->data, mat->dlen[0] * row + col) =
			*(double *)val;
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_create_matrix_rand_unit(struct claw_mat *mat, claw_dlen row,
				      claw_dlen col, enum claw_dtype dtype)
{
	if (dtype != CLAW_FLT32 && dtype != CLAW_FLT64) {
		return CLAW_MATRIX_E_INVALID_DTYPE;
	}

	claw_err err = claw_create_matrix(mat, row, col, dtype);

	switch (mat->dtype) {
	case CLAW_FLT32:
		CREATE_FILL(float, mat, claw_get_rand_unitf());
		break;
	case CLAW_FLT64:
		CREATE_FILL(double, mat, claw_get_rand_unit());
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_create_matrix_identity(struct claw_mat *mat, claw_dlen row,
				     claw_dlen col, enum claw_dtype dtype)
{
	if (row != col) {
		return CLAW_MATRIX_E_INVALID_DIMS;
	}

	claw_err err = claw_create_matrix(mat, row, col, dtype);

	switch (mat->dtype) {
	case CLAW_INT8:
		FILL_DIAGONAL(int8_t, mat, 1);
		break;
	case CLAW_UINT8:
		FILL_DIAGONAL(uint8_t, mat, 1);
		break;
	case CLAW_INT16:
		FILL_DIAGONAL(int16_t, mat, 1);
		break;
	case CLAW_UINT16:
		FILL_DIAGONAL(uint16_t, mat, 1);
		break;
	case CLAW_INT32:
		FILL_DIAGONAL(int32_t, mat, 1);
		break;
	case CLAW_UINT32:
		FILL_DIAGONAL(uint32_t, mat, 1);
		break;
	case CLAW_INT64:
		FILL_DIAGONAL(int64_t, mat, 1);
		break;
	case CLAW_UINT64:
		FILL_DIAGONAL(uint64_t, mat, 1);
		break;
	case CLAW_FLT32:
		FILL_DIAGONAL(float, mat, 1);
		break;
	case CLAW_FLT64:
		FILL_DIAGONAL(double, mat, 1);
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_matrix_copy(struct claw_mat *mat, struct claw_mat *res)
{
	if (mat == res) {
		return CLAW_OP_E_UNNECESSARY;
	}

	claw_create_matrix(res, mat->dlen[0], mat->dlen[1], mat->dtype);
	size_t mat_bsize = CLAW_MATRIX_BSIZE(mat);
	memcpy(mat->data, res->data, mat_bsize);

	return CLAW_SUCCESS;
}

claw_err claw_matrix_cast_inplace(struct claw_mat *mat, enum claw_dtype dtype)
{
	if (mat->dtype == dtype) {
		return CLAW_OP_E_UNNECESSARY;
	}

	struct claw_mat cp;
	claw_create_matrix(&cp, mat->dlen[0], mat->dlen[1], dtype);

	void *val;
	for (claw_dlen i = 0; i < mat->dlen[0]; i++) {
		for (claw_dlen j = 0; j < mat->dlen[1]; j++) {
			claw_matrix_get_idx(mat, i, j, val);
			claw_matrix_set_idx(&cp, i, j, val);
		}
	}

	mat->dtype = dtype;
	mat->data = cp.data;

	return CLAW_SUCCESS;
}

claw_err claw_free(struct claw_mat *mat)
{
	free(mat->data);
	return CLAW_SUCCESS;
}

#undef CREATE_FILL
#undef __PRINT_INNER
#undef PRINT_MAT
#undef CLAW_INDEX
#undef FILL_DIAGONAL
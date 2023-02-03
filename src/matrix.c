#include "claw/matrix.h"
#include "claw/utils.h"

#define CLAW_INDEX(type, data, idx) *((type *)(data) + idx)

#define CREATE_FILL(type, mat, val)                                  \
	do {                                                                \
		mat->data =                                                 \
			malloc(mat->dlen[0] * mat->dlen[1] * sizeof(type)); \
		for (size_t i = 0; i < mat->dlen[0] * mat->dlen[1]; i++) {  \
			CLAW_INDEX(type, mat->data, i) = *val;              \
		}                                                           \
	} while (0);

#define PRINT_MAT(fp, size, mat, ph)                                \
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
		PRINT_MAT(fp, int8_t, mat, "hhd");
		break;
	case CLAW_UINT8:
		PRINT_MAT(fp, uint8_t, mat, "hhu");
		break;
	case CLAW_INT16:
		PRINT_MAT(fp, int16_t, mat, "hd");
		break;
	case CLAW_UINT16:
		PRINT_MAT(fp, uint16_t, mat, "hu");
		break;
	case CLAW_INT32:
		PRINT_MAT(fp, int32_t, mat, "d");
		break;
	case CLAW_UINT32:
		PRINT_MAT(fp, uint32_t, mat, "u");
		break;
	case CLAW_INT64:
		PRINT_MAT(fp, int64_t, mat, "lld");
		break;
	case CLAW_UINT64:
		PRINT_MAT(fp, uint64_t, mat, "llu");
		break;
	case CLAW_FLT32:
		PRINT_MAT(fp, float, mat, ".1f");
		break;
	case CLAW_FLT64:
		PRINT_MAT(fp, double, mat, ".2lf");
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
	mat->data = malloc(row * col * claw_dtype_byte_size(dtype));
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
		CREATE_FILL(int8_t, mat, (int8_t *)val);
		break;
	case CLAW_UINT8:
		CREATE_FILL(uint8_t, mat, (uint8_t *)val);
		break;
	case CLAW_INT16:
		CREATE_FILL(int16_t, mat, (int16_t *)val);
		break;
	case CLAW_UINT16:
		CREATE_FILL(uint16_t, mat, (uint16_t *)val);
		break;
	case CLAW_INT32:
		CREATE_FILL(int32_t, mat, (int32_t *)val);
		break;
	case CLAW_UINT32:
		CREATE_FILL(uint32_t, mat, (uint32_t *)val);
		break;
	case CLAW_INT64:
		CREATE_FILL(int64_t, mat, (int64_t *)val);
		break;
	case CLAW_UINT64:
		CREATE_FILL(uint64_t, mat, (uint64_t *)val);
		break;
	case CLAW_FLT32:
		CREATE_FILL(float, mat, (float *)val);
		break;
	case CLAW_FLT64:
		CREATE_FILL(double, mat, (double *)val);
		break;
	}

	return CLAW_SUCCESS;
}

claw_err claw_free(struct claw_mat *mat)
{
	free(mat->data);
	return CLAW_SUCCESS;
}

#undef CREATE_FILL
#undef PRINT_MAT

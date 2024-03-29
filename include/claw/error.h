#ifndef CLAW_JS_INCLUDE_CLAW_ERROR_H
#define CLAW_JS_INCLUDE_CLAW_ERROR_H

typedef enum {
	CLAW_SUCCESS = 0,

	// backend errors
	CLAW_OPENCL_E_INTERNAL_IMPL = -100,
	CLAW_OPENCL_E_KERNEL_NOT_FOUND = -101,

	// matrix erros
	CLAW_MATRIX_E_INDEX_OUT_OF_BOUNDS = -200,
	CLAW_MATRIX_E_INVALID_DTYPE = -201,
	CLAW_MATRIX_E_INVALID_DIMS = -202,
	CLAW_MATRIX_E_DTYPE_MISMATCH= -203,
	CLAW_MATRIX_E_DIM_MISMATCH = -204,

	// operation errors
	CLAW_OP_E_UNNECESSARY = -250,
} claw_err;

const char *claw_get_err_str(claw_err err);

#endif //CLAW_JS_INCLUDE_CLAW_ERROR_H

#ifndef CLAW_JS_INCLUDE_CLAW_ERROR_H
#define CLAW_JS_INCLUDE_CLAW_ERROR_H

typedef enum {
	CLAW_SUCCESS = 0,
	CLAW_MATMUL_E_DIM_MISMATCH = -100,
	CLAW_OPENCL_E_KERNEL_NOT_FOUND = -200,
} claw_err;

const char *claw_get_err_str(claw_err err);

#endif //CLAW_JS_INCLUDE_CLAW_ERROR_H

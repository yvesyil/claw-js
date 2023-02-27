#include "claw/error.h"

const char *claw_get_err_str(claw_err err)
{
	switch (err) {
	case CLAW_SUCCESS:
		return "CLAW_SUCCESS";
	case CLAW_MATRIX_E_DIM_MISMATCH:
		return "CLAW_MATMUL_E_DIM_MISMATCH";
	case CLAW_OPENCL_E_KERNEL_NOT_FOUND:
		return "CLAW_OPENCL_E_KERNEL_NOT_FOUND";
	case CLAW_OPENCL_E_INTERNAL_IMPL:
		return "CLAW_OPENCL_E_INTERNAL_IMPL";
	default:
		return "Unknown Claw.js Error";
	}
}
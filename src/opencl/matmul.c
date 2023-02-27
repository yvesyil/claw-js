#include "claw/matmul.h"
#include "claw/utils.h"
#include "common.h"
#include "clblast_c.h"

extern struct claw_opencl_ctx ctx;

claw_err claw_matmul(struct claw_mat *lhs, struct claw_mat *rhs,
		     struct claw_mat *res)
{
	if (lhs->dlen[1] != rhs->dlen[0]) {
		return CLAW_MATRIX_E_DIM_MISMATCH;
	}

	if (lhs->dtype != rhs->dtype) {
		return CLAW_MATRIX_E_DTYPE_MISMATCH;
	}

	if (res == NULL || res->dlen[0] != lhs->dlen[0] || res->dlen[1] != rhs->dlen[1] || res->dtype != lhs->dtype) {
		claw_create_matrix(res, lhs->dlen[0], rhs->dlen[1], lhs->dtype);
	}

	cl_int *err = &ctx.err;

	size_t lhs_bsize = CLAW_MATRIX_BSIZE(lhs);
	size_t rhs_bsize = CLAW_MATRIX_BSIZE(rhs);
	size_t res_bsize = CLAW_MATRIX_BSIZE(res);

	// allocate buffer space

	cl_mem lhs_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, lhs_bsize, NULL, err);
	cl_mem rhs_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, rhs_bsize, NULL, err);
	cl_mem res_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, res_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// write data to buffers
	cl_command_queue *cmd_q = &ctx.cmd_q;

	*err = clEnqueueWriteBuffer(*cmd_q, lhs_mem, CL_TRUE, 0, lhs_bsize,
				    lhs->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, rhs_mem, CL_TRUE, 0, rhs_bsize,
				    rhs->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, res_mem, CL_TRUE, 0, res_bsize,
				    res->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	CLBlastStatusCode status = CLBlastSgemm(
		CLBlastLayoutRowMajor, CLBlastTransposeNo, CLBlastTransposeNo,
		lhs->dlen[0], rhs->dlen[1], lhs->dlen[1], 1, lhs_mem, 0,
		lhs->dlen[1], rhs_mem, 0, rhs->dlen[1], 0, res_mem, 0,
		res->dlen[1], cmd_q, NULL);

	if (status != CLBlastSuccess) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// read to resulting matrix from dev
	*err = clEnqueueReadBuffer(*cmd_q, res_mem, CL_TRUE, 0, res_bsize,
				   res->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// cleanup
	*err = clReleaseMemObject(lhs_mem);
	*err = clReleaseMemObject(rhs_mem);
	*err = clReleaseMemObject(res_mem);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	return CLAW_SUCCESS;
}

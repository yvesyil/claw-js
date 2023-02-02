#include "claw/matmul.h"
#include "claw/utils.h"
#include "common.h"
#include "clblast_c.h"

static claw_err manage_buffers(struct claw_mat *lhs, struct claw_mat *rhs,
			       struct claw_mat *res)
{
	cl_int *err = &claw_opencl_context.err;

	size_t lhs_bsize =
		lhs->dlen[0] * lhs->dlen[1] * claw_dtype_byte_size(lhs->dtype);
	size_t rhs_bsize =
		rhs->dlen[0] * rhs->dlen[1] * claw_dtype_byte_size(rhs->dtype);
	size_t res_bsize =
		res->dlen[0] * res->dlen[1] * claw_dtype_byte_size(res->dtype);

	// allocate buffer space
	cl_context *ctx = &claw_opencl_context.ctx;

	cl_mem lhs_mem =
		clCreateBuffer(*ctx, CL_MEM_READ_WRITE, lhs_bsize, NULL, err);
	cl_mem rhs_mem =
		clCreateBuffer(*ctx, CL_MEM_READ_WRITE, rhs_bsize, NULL, err);
	cl_mem res_mem =
		clCreateBuffer(*ctx, CL_MEM_READ_WRITE, res_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// write data to buffers
	cl_command_queue *cmd_q = &claw_opencl_context.cmd_q;

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

claw_err claw_matmul(struct claw_mat *lhs, struct claw_mat *rhs,
		     struct claw_mat *res)
{
	claw_err err;

	if (lhs->dlen[1] != rhs->dlen[0]) {
		err = CLAW_MATMUL_E_DIM_MISMATCH;
		fprintf(stderr, "%s", claw_get_err_str(err));
		return err;
	}

	claw_create_matrix(res, lhs->dlen[0], rhs->dlen[1], lhs->dtype);

	err = claw_opencl_init(&claw_opencl_context);
	if (err != CLAW_SUCCESS) {
		fprintf(stderr, "%s", claw_get_err_str(err));
		return err;
	}

	err = claw_opencl_setup_ctx_and_cmd_q(&claw_opencl_context);
	if (err != CLAW_SUCCESS) {
		fprintf(stderr, "%s %s", claw_get_err_str(err),
			opencl_get_err_str(claw_opencl_context.err));
		return err;
	}

	err = manage_buffers(lhs, rhs, res);
	if (err != CLAW_SUCCESS) {
		fprintf(stderr, "%s %s", claw_get_err_str(err),
			opencl_get_err_str(claw_opencl_context.err));
		return err;
	}

	claw_opencl_free_kernel(&claw_opencl_context);

	return CLAW_SUCCESS;
}

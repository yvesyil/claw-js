#include "claw/basic_ops.h"
#include "common.h"
#include "clblast_c.h"

extern struct claw_opencl_ctx ctx;

claw_err _claw_saxpy(struct claw_mat *m1, float alpha, struct claw_mat *m2)
{
	if (m1->dlen[0] != m2->dlen[0] && m1->dlen[1] != m2->dlen[1]) {
		return CLAW_MATRIX_E_INVALID_DIMS;
	}

	cl_int *err = &ctx.err;

	size_t m1_bsize = CLAW_MATRIX_BSIZE(m1);
	size_t m2_bsize = CLAW_MATRIX_BSIZE(m2);

	cl_mem m1_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, m1_bsize, NULL, err);
	cl_mem m2_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, m2_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	cl_command_queue *cmd_q = &ctx.cmd_q;

	*err = clEnqueueWriteBuffer(*cmd_q, m1_mem, CL_TRUE, 0, m1_bsize,
				    m1->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, m2_mem, CL_TRUE, 0, m2_bsize,
				    m2->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	CLBlastStatusCode status = CLBlastSaxpy(m1->dlen[0] * m1->dlen[1],
						alpha, m1_mem, 0, 1, m2_mem, 0,
						1, cmd_q, NULL);
	if (status != CLBlastSuccess) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clEnqueueReadBuffer(*cmd_q, m2_mem, CL_TRUE, 0, m2_bsize,
				   m2->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clReleaseMemObject(m1_mem);
	*err = clReleaseMemObject(m2_mem);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	return CLAW_SUCCESS;
}

claw_err claw_mataddmat(struct claw_mat *m1, struct claw_mat *m2)
{
	return _claw_saxpy(m1, 1.0f, m2);
}

claw_err claw_matsubmat(struct claw_mat *m1, struct claw_mat *m2)
{
	return _claw_saxpy(m1, -1.0f, m2);
}

claw_err claw_matscale(struct claw_mat *m, void *s)
{
	if (m->dtype != CLAW_FLT32) {
		return CLAW_MATRIX_E_INVALID_DTYPE;
	}

	cl_int *err = &ctx.err;

	size_t m_bsize = CLAW_MATRIX_BSIZE(m);

	cl_mem m_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, m_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	cl_command_queue *cmd_q = &ctx.cmd_q;

	*err = clEnqueueWriteBuffer(*cmd_q, m_mem, CL_TRUE, 0, m_bsize, m->data,
				    0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	CLBlastStatusCode status = CLBlastSscal(
		m->dlen[0] * m->dlen[1], *(float *)s, m_mem, 0, 1, cmd_q, NULL);
	if (status != CLBlastSuccess) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clEnqueueReadBuffer(*cmd_q, m_mem, CL_TRUE, 0, m_bsize, m->data,
				   0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clReleaseMemObject(m_mem);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	return CLAW_SUCCESS;
}

claw_err claw_hadamard(struct claw_mat *m1, struct claw_mat *m2,
		       struct claw_mat *res)
{
	if (m1->dlen[0] != m2->dlen[0] && m1->dlen[1] != m2->dlen[1]) {
		return CLAW_MATRIX_E_INVALID_DIMS;
	}

	if (res == NULL || res->dlen[0] != m1->dlen[0] || res->dlen[1] != m2->dlen[1] || res->dtype != m1->dtype) {
		claw_create_matrix(res, m1->dlen[0], m1->dlen[1], m1->dtype);
	}

	cl_int *err = &ctx.err;

	size_t m1_bsize = CLAW_MATRIX_BSIZE(m1);
	size_t m2_bsize = CLAW_MATRIX_BSIZE(m2);
	size_t res_bsize = m1_bsize;

	cl_mem m1_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, m1_bsize, NULL, err);
	cl_mem m2_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, m2_bsize, NULL, err);
	cl_mem res_mem =
		clCreateBuffer(ctx.ctx, CL_MEM_READ_WRITE, res_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	cl_command_queue *cmd_q = &ctx.cmd_q;

	*err = clEnqueueWriteBuffer(*cmd_q, m1_mem, CL_TRUE, 0, m1_bsize,
				    m1->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, m2_mem, CL_TRUE, 0, m2_bsize,
				    m2->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	CLBlastStatusCode status = CLBlastShad(m1->dlen[0] * m1->dlen[1], 1.0f,
					       m1_mem, 0, 1, m2_mem, 0, 1, 1.0f,
					       res_mem, 0, 1, cmd_q, NULL);
	if (status != CLBlastSuccess) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clEnqueueReadBuffer(*cmd_q, res_mem, CL_TRUE, 0, res_bsize,
				   res->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*err = clReleaseMemObject(m1_mem);
	*err = clReleaseMemObject(m2_mem);
	*err = clReleaseMemObject(res_mem);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	return CLAW_SUCCESS;
}
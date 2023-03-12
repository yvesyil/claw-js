#include "claw/basic_ops.h"
#include "common.h"
#include "clblast_c.h"

extern struct claw_opencl_ctx ctx;

claw_err claw_mataddmat(struct claw_mat *m1, struct claw_mat *m2)
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

	CLBlastStatusCode status = CLBlastSaxpy(m1->dlen[0] * m1->dlen[1], 1.0f,
						m1_mem, 0, 1, m2_mem, 0, 1,
						cmd_q, NULL);
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
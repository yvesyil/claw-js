#include "claw/matmul.h"
#include "claw/utils.h"
#include "common.h"

static claw_err _opencl_matmul_manage_buffers(struct claw_mat *lhs,
					      struct claw_mat *rhs,
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
		clCreateBuffer(*ctx, CL_MEM_READ_ONLY, lhs_bsize, NULL, err);
	cl_mem lhs_dlen_mem = clCreateBuffer(*ctx, CL_MEM_READ_ONLY,
					     2 * sizeof(size_t), NULL, err);
	cl_mem rhs_mem =
		clCreateBuffer(*ctx, CL_MEM_READ_ONLY, rhs_bsize, NULL, err);
	cl_mem rhs_dlen_mem = clCreateBuffer(*ctx, CL_MEM_READ_ONLY,
					     2 * sizeof(size_t), NULL, err);
	cl_mem res_mem =
		clCreateBuffer(*ctx, CL_MEM_WRITE_ONLY, res_bsize, NULL, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// write data to buffers
	cl_command_queue *cmd_q = &claw_opencl_context.cmd_q;

	*err = clEnqueueWriteBuffer(*cmd_q, lhs_mem, CL_TRUE, 0, lhs_bsize,
				    lhs->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, lhs_dlen_mem, CL_TRUE, 0,
				    2 * sizeof(size_t), lhs->dlen, 0, NULL,
				    NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, rhs_mem, CL_TRUE, 0, rhs_bsize,
				    rhs->data, 0, NULL, NULL);
	*err = clEnqueueWriteBuffer(*cmd_q, rhs_dlen_mem, CL_TRUE, 0,
				    2 * sizeof(size_t), rhs->dlen, 0, NULL,
				    NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	cl_program *prog = &claw_opencl_context.prog;
	const char *k_name = claw_opencl_context.active_kernel.name;

	cl_kernel kernel = clCreateKernel(*prog, k_name, err);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// set kernel arguments (buffers)
	cl_uint arg_idx = 0;
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), &lhs_mem);
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), &lhs_dlen_mem);
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), &rhs_mem);
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), &rhs_dlen_mem);
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), &res_mem);
	*err = clSetKernelArg(kernel, arg_idx++, sizeof(size_t),
			      &(lhs->dlen[1]));
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}
	// configure dev threads
	const size_t glob_witem_size[] = { res->dlen[0], res->dlen[1] };
	const size_t loc_witem_size[] = { WORK_GROUP_SIZE, WORK_GROUP_SIZE };

	*err = clEnqueueNDRangeKernel(*cmd_q, kernel, 2, NULL, glob_witem_size,
				      loc_witem_size, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// read to resulting matrix from dev
	*err = clEnqueueReadBuffer(*cmd_q, res_mem, CL_TRUE, 0, res_bsize,
				   res->data, 0, NULL, NULL);
	if (*err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	// cleanup
	*err = clReleaseKernel(kernel);
	*err = clReleaseMemObject(lhs_mem);
	*err = clReleaseMemObject(lhs_dlen_mem);
	*err = clReleaseMemObject(rhs_mem);
	*err = clReleaseMemObject(rhs_dlen_mem);
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
	err = claw_opencl_get_kernel_src(&claw_opencl_context, "matmul1");
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
	err = claw_opencl_setup_prog(&claw_opencl_context);
	if (err != CLAW_SUCCESS) {
		fprintf(stderr, "%s %s", claw_get_err_str(err),
			opencl_get_err_str(claw_opencl_context.err));
		return err;
	}

	err = _opencl_matmul_manage_buffers(lhs, rhs, res);
	if (err != CLAW_SUCCESS) {
		fprintf(stderr, "%s %s", claw_get_err_str(err),
			opencl_get_err_str(claw_opencl_context.err));
		return err;
	}

	claw_opencl_free_kernel(&claw_opencl_context);

	return CLAW_SUCCESS;
}

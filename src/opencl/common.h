#ifndef CLAW_JS_SRC_OPENCL_COMMON_H
#define CLAW_JS_SRC_OPENCL_COMMON_H

#include <string.h>

#include "claw/device.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE 0x100000
#define MAX_MATRIX_DIM_SIZE 65536

#define WORK_GROUP_SIZE 16

struct opencl_kernel {
	char *name;
	char *path;
	char *src;
	size_t src_size;
};

struct opencl_ctx {
	cl_int err;
	cl_device_id dev_id;
	cl_context ctx;
	cl_program prog;
	cl_command_queue cmd_q;
	struct opencl_kernel active_kernel;
};

extern struct opencl_ctx claw_opencl_context;

claw_err claw_opencl_init(struct opencl_ctx *context);

const char *opencl_get_err_str(cl_int err);

claw_err claw_opencl_get_kernel_src(struct opencl_ctx *context, const char *k_name);

claw_err claw_opencl_setup_ctx_and_cmd_q(struct opencl_ctx *context);

claw_err claw_opencl_setup_prog(struct opencl_ctx *context);

/*
cl_int claw_opencl_setup_buff_and_kernel(cl_context *ctx,
					 cl_command_queue cmd_q,
					 cl_program prog, const char *k_name,
					 ...);
					 */

claw_err claw_opencl_free_kernel(struct opencl_ctx *context);

#endif //CLAW_JS_SRC_OPENCL_COMMON_H

#ifndef CLAW_JS_SRC_OPENCL_COMMON_H
#define CLAW_JS_SRC_OPENCL_COMMON_H

#include "claw/device.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE 0x100000
#define MAX_MATRIX_DIM_SIZE 65536

#define WORK_GROUP_SIZE 16

const char *_opencl_get_error_string(cl_int error);

int claw_opencl_get_kernel_src(const char *ksrc, size_t src_size);

cl_int claw_opencl_setup_ctx_and_cmd_q(cl_device_id *dev_id, cl_context *ctx,
				       cl_command_queue *cmd_q);

cl_int claw_opencl_setup_prog(cl_device_id *dev_id, cl_context *ctx,
			      cl_program *prog, const char *ksrc,
			      size_t src_size);

cl_int claw_opencl_setup_buffers_and_kernel(cl_context *ctx,
					    cl_command_queue cmd_q,
					    cl_program prog, const char *kname,
					    ...);

#endif //CLAW_JS_SRC_OPENCL_COMMON_H

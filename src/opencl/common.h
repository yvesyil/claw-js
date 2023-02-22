#ifndef CLAW_JS_SRC_OPENCL_COMMON_H
#define CLAW_JS_SRC_OPENCL_COMMON_H

#include <string.h>

#include "claw/device.h"

#define MAX_SOURCE_SIZE 0x100000

extern struct claw_opencl_ctx claw_opencl_context;

claw_err claw_opencl_init(struct claw_opencl_ctx *context);

const char *opencl_get_err_str(cl_int err);

claw_err claw_opencl_set_kernel(struct claw_opencl_ctx *context, const char *k_name,
				const char *k_source);

claw_err claw_opencl_get_kernel_src(struct claw_opencl_ctx *context,
				    const char *k_name);

claw_err claw_opencl_setup_ctx_and_cmd_q(struct claw_opencl_ctx *context);

claw_err claw_opencl_setup_prog(struct claw_opencl_ctx *context);

claw_err claw_opencl_free_kernel(struct claw_opencl_ctx *context);

#endif //CLAW_JS_SRC_OPENCL_COMMON_H

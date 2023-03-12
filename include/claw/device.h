#ifndef CLAW_JS_INCLUDE_CLAW_DEVICE_H
#define CLAW_JS_INCLUDE_CLAW_DEVICE_H

#include <stdio.h>
#include "error.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

struct _opencl_kernel {
	char *name;
	char *path;
	char *src;
	size_t src_size;
};

struct claw_opencl_ctx {
	cl_int err;
	cl_device_id devices;
	cl_uint num_devices;
	cl_context ctx;
	cl_program prog;
	cl_command_queue cmd_q;
	struct _opencl_kernel active_kernel;
};

claw_err claw_init();

#endif //CLAW_JS_INCLUDE_CLAW_DEVICE_H

#ifndef CLAW_JS_INCLUDE_CLAW_ERROR_H
#define CLAW_JS_INCLUDE_CLAW_ERROR_H

typedef int claw_err;

// OpenCL related
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

const char *opencl_get_error_string(cl_int error);

#endif //CLAW_JS_INCLUDE_CLAW_ERROR_H

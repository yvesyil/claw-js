#include "claw/device.h"
#include "opencl/common.h"
#include "claw/error.h"

struct claw_opencl_ctx ctx;

// TODO: implement proper initialization
claw_err claw_init()
{
	return claw_opencl_init(&ctx);
}
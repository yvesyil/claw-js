#include "common.h"

struct opencl_ctx claw_opencl_context;

void _opencl_print_driver_version(cl_device_id *device_id)
{
	char *driver_version;
	clGetDeviceInfo(*device_id, CL_DRIVER_VERSION, sizeof(char *),
			&driver_version, NULL);
	printf("%s\n", driver_version);
}

void _opencl_query_platform_info(struct opencl_ctx *context)
{
	cl_uint num_platforms;

	context->err = clGetPlatformIDs(0, NULL, &num_platforms);

	if (num_platforms > 0) {
		cl_platform_id *platforms = (cl_platform_id *)malloc(
			num_platforms * sizeof(cl_platform_id));
		context->err = clGetPlatformIDs(num_platforms, platforms, NULL);
	}
}

void _opencl_query_device_info(struct opencl_ctx *context,
			       cl_platform_id platform_id)
{
	cl_uint *num_devices = &context->num_devices;

	context->err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 0,
				      NULL, num_devices);
	if (num_devices > 0) {
		context->devices = (cl_device_id *)malloc(*num_devices *
							  sizeof(cl_device_id));
		context->err =
			clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT,
				       *num_devices, context->devices, NULL);
	}
}

claw_err claw_opencl_init(struct opencl_ctx *context)
{
	return CLAW_SUCCESS;
}

claw_err claw_opencl_get_kernel_src(struct opencl_ctx *context,
				    const char *k_name)
{
	FILE *fp;
	char k_path[59] = "./opencl/kernel/";

	strcat(k_path, k_name);
	strcat(k_path, ".cl");

	context->active_kernel.name = k_name;
	context->active_kernel.path = k_path;

	fp = fopen(k_path, "r");
	if (!fp) {
		fprintf(stderr,
			claw_get_err_str(CLAW_OPENCL_E_KERNEL_NOT_FOUND));
		return CLAW_OPENCL_E_KERNEL_NOT_FOUND;
	}

	context->active_kernel.src = (char *)malloc(MAX_SOURCE_SIZE);
	context->active_kernel.src_size =
		fread(context->active_kernel.src, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	return CLAW_SUCCESS;
}

claw_err claw_opencl_setup_ctx_and_cmd_q(struct opencl_ctx *context)
{
	cl_device_id *devices = &context->devices;
	cl_context *ctx = &context->ctx;
	cl_command_queue *cmd_q = &context->cmd_q;

	cl_platform_id platform_id;
	cl_uint num_devs;
	cl_uint num_platforms;

	context->err = clGetPlatformIDs(1, &platform_id, &num_platforms);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	/*
	context->err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 0, NULL,
			     &num_devs);
	if (num_devs > 0) {
		devices = (cl_device_id*)malloc(num_devs * sizeof(cl_device_id));
		context->err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, num_devs, devices, NULL);
	}
	*/
	context->err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
				      devices, &num_devs);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*ctx = clCreateContext(NULL, 1, devices, NULL, NULL, &context->err);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	*cmd_q = clCreateCommandQueue(*ctx, *devices, 0, &context->err);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	return CLAW_SUCCESS;
}

claw_err claw_opencl_setup_prog(struct opencl_ctx *context)
{
	cl_device_id *dev_id = &context->devices;
	cl_context *ctx = &context->ctx;
	cl_program *prog = &context->prog;

	const char *k_src = context->active_kernel.src;
	size_t k_size = context->active_kernel.src_size;

	*prog = clCreateProgramWithSource(
		*ctx, 1, &k_src, (const size_t *)&k_size, &context->err);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	context->err = clBuildProgram(*prog, 1, dev_id, NULL, NULL, NULL);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	size_t log_size;
	context->err = clGetProgramBuildInfo(
		*prog, *dev_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}

	uint8_t *messages = (uint8_t *)malloc((1 + log_size) * sizeof(uint8_t));
	context->err = clGetProgramBuildInfo(
		*prog, *dev_id, CL_PROGRAM_BUILD_LOG, log_size, messages, NULL);
	if (context->err != CL_SUCCESS) {
		return CLAW_OPENCL_E_INTERNAL_IMPL;
	}
	messages[log_size] = '\0';
	//printf(">>> OpenCL compiler message: %s\n", messages);
	free(messages);

	return CLAW_SUCCESS;
}

claw_err claw_opencl_free_kernel(struct opencl_ctx *context)
{
	free(context->active_kernel.src);
	return CLAW_SUCCESS;
}

const char *opencl_get_err_str(cl_int err)
{
	switch (err) {
	// run-time and JIT compiler errors
	case 0:
		return "CL_SUCCESS";
	case -1:
		return "CL_DEVICE_NOT_FOUND";
	case -2:
		return "CL_DEVICE_NOT_AVAILABLE";
	case -3:
		return "CL_COMPILER_NOT_AVAILABLE";
	case -4:
		return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	case -5:
		return "CL_OUT_OF_RESOURCES";
	case -6:
		return "CL_OUT_OF_HOST_MEMORY";
	case -7:
		return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case -8:
		return "CL_MEM_COPY_OVERLAP";
	case -9:
		return "CL_IMAGE_FORMAT_MISMATCH";
	case -10:
		return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case -11:
		return "CL_BUILD_PROGRAM_FAILURE";
	case -12:
		return "CL_MAP_FAILURE";
	case -13:
		return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
	case -14:
		return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
	case -15:
		return "CL_COMPILE_PROGRAM_FAILURE";
	case -16:
		return "CL_LINKER_NOT_AVAILABLE";
	case -17:
		return "CL_LINK_PROGRAM_FAILURE";
	case -18:
		return "CL_DEVICE_PARTITION_FAILED";
	case -19:
		return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
	case -30:
		return "CL_INVALID_VALUE";
	case -31:
		return "CL_INVALID_DEVICE_TYPE";
	case -32:
		return "CL_INVALID_PLATFORM";
	case -33:
		return "CL_INVALID_DEVICE";
	case -34:
		return "CL_INVALID_CONTEXT";
	case -35:
		return "CL_INVALID_QUEUE_PROPERTIES";
	case -36:
		return "CL_INVALID_COMMAND_QUEUE";
	case -37:
		return "CL_INVALID_HOST_PTR";
	case -38:
		return "CL_INVALID_MEM_OBJECT";
	case -39:
		return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case -40:
		return "CL_INVALID_IMAGE_SIZE";
	case -41:
		return "CL_INVALID_SAMPLER";
	case -42:
		return "CL_INVALID_BINARY";
	case -43:
		return "CL_INVALID_BUILD_OPTIONS";
	case -44:
		return "CL_INVALID_PROGRAM";
	case -45:
		return "CL_INVALID_PROGRAM_EXECUTABLE";
	case -46:
		return "CL_INVALID_KERNEL_NAME";
	case -47:
		return "CL_INVALID_KERNEL_DEFINITION";
	case -48:
		return "CL_INVALID_KERNEL";
	case -49:
		return "CL_INVALID_ARG_INDEX";
	case -50:
		return "CL_INVALID_ARG_VALUE";
	case -51:
		return "CL_INVALID_ARG_SIZE";
	case -52:
		return "CL_INVALID_KERNEL_ARGS";
	case -53:
		return "CL_INVALID_WORK_DIMENSION";
	case -54:
		return "CL_INVALID_WORK_GROUP_SIZE";
	case -55:
		return "CL_INVALID_WORK_ITEM_SIZE";
	case -56:
		return "CL_INVALID_GLOBAL_OFFSET";
	case -57:
		return "CL_INVALID_EVENT_WAIT_LIST";
	case -58:
		return "CL_INVALID_EVENT";
	case -59:
		return "CL_INVALID_OPERATION";
	case -60:
		return "CL_INVALID_GL_OBJECT";
	case -61:
		return "CL_INVALID_BUFFER_SIZE";
	case -62:
		return "CL_INVALID_MIP_LEVEL";
	case -63:
		return "CL_INVALID_GLOBAL_WORK_SIZE";
	case -64:
		return "CL_INVALID_PROPERTY";
	case -65:
		return "CL_INVALID_IMAGE_DESCRIPTOR";
	case -66:
		return "CL_INVALID_COMPILER_OPTIONS";
	case -67:
		return "CL_INVALID_LINKER_OPTIONS";
	case -68:
		return "CL_INVALID_DEVICE_PARTITION_COUNT";

		// extension errors
	case -1000:
		return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
	case -1001:
		return "CL_PLATFORM_NOT_FOUND_KHR";
	case -1002:
		return "CL_INVALID_D3D10_DEVICE_KHR";
	case -1003:
		return "CL_INVALID_D3D10_RESOURCE_KHR";
	case -1004:
		return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
	case -1005:
		return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
	default:
		return "Unknown OpenCL error";
	}
}
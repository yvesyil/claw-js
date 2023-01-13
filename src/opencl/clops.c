#ifndef CLAW_JS_CLOPS_H
#define CLAW_JS_CLOPS_H

#include <stdint.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define WORK_GROUP_SIZE 16

cl_int opencl_setup_context_and_command_queue(cl_device_id* device_id,
        cl_context* ctx,
        cl_command_queue* command_queue)
{

    cl_platform_id platform_id = NULL;
    cl_uint num_devices;
    cl_uint num_platforms;

    cl_int err = clGetPlatformIDs(1, &platform_id, &num_platforms);
    if (err!=CL_SUCCESS) {
        return err;
    }

    err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, device_id, &num_devices);
    if (err!=CL_SUCCESS) {
        return err;
    }

    *ctx = clCreateContext(NULL, 1, device_id, NULL, NULL, &err);

    *command_queue = clCreateCommandQueue(*ctx, *device_id, 0, &err);

    return err;
}

cl_int opencl_setup_program(cl_context ctx,
        cl_program* prog,
        cl_device_id* device_id,
        const char* source_str,
        size_t source_size)
{

    cl_int err;
    *prog = clCreateProgramWithSource(ctx, 1,
            &source_str, (const size_t*) &source_size, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clBuildProgram(*prog, 1, device_id, NULL, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }

    size_t log_size;
    err = clGetProgramBuildInfo(*prog, *device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    if (err!=CL_SUCCESS) {
        return err;
    }

    uint8_t* messages = (uint8_t*) malloc((1+log_size)*sizeof(uint8_t));
    err = clGetProgramBuildInfo(*prog, *device_id, CL_PROGRAM_BUILD_LOG, log_size, messages, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }
    messages[log_size] = '\0';
    if (log_size>10) printf(">>> Compiler message: %s\n", messages);
    free(messages);

    return err;
}

cl_int opencl_setup_buffers_and_kernel(cl_context ctx,
        cl_command_queue cmd_queue,
        cl_program prog,
        const char* kernel_name,
        float* A,
        size_t* shapeA,
        float* B,
        size_t* shapeB,
        float* C,
        size_t* shapeC)
{

    cl_int err;
    cl_mem a_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
            shapeA[0]*shapeA[1]*sizeof(float), NULL, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }
    cl_mem shape_a_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
            2*sizeof(size_t), NULL, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }
    cl_mem b_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
            shapeB[0]*shapeB[1]*sizeof(float), NULL, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }
    cl_mem shape_b_mem_obj = clCreateBuffer(ctx, CL_MEM_READ_ONLY,
            2*sizeof(size_t), NULL, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }
    cl_mem c_mem_obj = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY,
            shapeC[0]*shapeC[1]*sizeof(float), NULL, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }

    err = clEnqueueWriteBuffer(cmd_queue, a_mem_obj, CL_TRUE, 0,
            shapeA[0]*shapeA[1]*sizeof(float), A, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clEnqueueWriteBuffer(cmd_queue, shape_a_mem_obj, CL_TRUE, 0,
            2*sizeof(size_t), shapeA, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clEnqueueWriteBuffer(cmd_queue, b_mem_obj, CL_TRUE, 0,
            shapeB[0]*shapeB[1]*sizeof(float), B, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clEnqueueWriteBuffer(cmd_queue, shape_b_mem_obj, CL_TRUE, 0,
            2*sizeof(size_t), shapeB, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(prog, kernel_name, &err);
    if (err!=CL_SUCCESS) {
        return err;
    }

    // Set the arguments of the kernel
    cl_uint arg_idx = 0;
    err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), (void*) &a_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), (void*) &shape_a_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), (void*) &b_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), (void*) &shape_b_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clSetKernelArg(kernel, arg_idx++, sizeof(cl_mem), (void*) &c_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clSetKernelArg(kernel, arg_idx++, sizeof(size_t), (void*) &(shapeA[1]));
    if (err!=CL_SUCCESS) {
        return err;
    }

    // Execute the OpenCL kernel on the list
    const size_t global_witem_size[] = {shapeC[0], shapeC[1]};
    const size_t local_witem_size[] = {WORK_GROUP_SIZE, WORK_GROUP_SIZE};

    err = clEnqueueNDRangeKernel(cmd_queue, kernel, 2,
            NULL, global_witem_size, local_witem_size, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }

    // Read the memory buffer C on the device to the local variable C
    err = clEnqueueReadBuffer(cmd_queue, c_mem_obj, CL_TRUE, 0,
            shapeC[0]*shapeC[1]*sizeof(float), C, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        return err;
    }

    // CLEANUP
    err = clFlush(cmd_queue);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clFinish(cmd_queue);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseKernel(kernel);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseProgram(prog);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseMemObject(a_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseMemObject(b_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseMemObject(c_mem_obj);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseCommandQueue(cmd_queue);
    if (err!=CL_SUCCESS) {
        return err;
    }
    err = clReleaseContext(ctx);

    return err;
}

#endif //CLAW_JS_CLOPS_H

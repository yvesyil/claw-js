#include <stdint.h>
#include <stdio.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "utils.h"
#include "clops.h"

#define MAX_SOURCE_SIZE         0x100000
#define MAX_MATRIX_DIM_SIZE     65536
#define MATRIX_SIZE             32 * 32


int main() {
    size_t shapeA[] = {MATRIX_SIZE, MATRIX_SIZE};
    size_t shapeB[] = {MATRIX_SIZE, MATRIX_SIZE};
    size_t shapeC[] = {shapeA[0], shapeB[1]};
    float *A = (float *) malloc(sizeof(float) * shapeA[0] * shapeA[1]);
    float *B = (float *) malloc(sizeof(float) * shapeB[0] * shapeB[1]);
    float *C = (float *) malloc(sizeof(float) * shapeC[0] * shapeC[1]);

    for (size_t i = 0; i < shapeA[0] * shapeA[1]; i++) {
        A[i] = 1.0f;
    }
    for (size_t i = 0; i < shapeB[0] * shapeB[1]; i++) {
        B[i] = 2.0f;
    }

    print_matrix(A, shapeA);

    FILE *fp;
    char *source1_str;
    char *source2_str;
    size_t source1_size;
    size_t source2_size;

    fp = fopen("../src/kernel/matmul1.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.");
        exit(1);
    }

    source1_str = (char *) malloc(MAX_SOURCE_SIZE);
    source1_size = fread(source1_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);


    fp = fopen("../src/kernel/matmul2.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.");
        exit(1);
    }

    source2_str = (char *) malloc(MAX_SOURCE_SIZE);
    source2_size = fread(source2_str, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);


    cl_device_id device_id;
    cl_context ctx;
    cl_program prog;
    cl_command_queue cmd_queue;

    cl_int err = openclSetupContextAndCommandQueue(&device_id,
                                                   &ctx, &cmd_queue);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }

    err = openclSetupProgram(ctx, &prog, &device_id, source1_str, source1_size);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }

    err = openclSetupBuffersAndKernel(ctx, cmd_queue, prog,
                                      "matmul1", A, shapeA, B, shapeB, C, shapeC);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }

    print_matrix(B, shapeB);
    print_matrix(C, shapeC);


    err = openclSetupContextAndCommandQueue(&device_id,
                                            &ctx, &cmd_queue);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }

    err = openclSetupProgram(ctx, &prog, &device_id, source2_str, source2_size);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }

    err = openclSetupBuffersAndKernel(ctx, cmd_queue, prog,
                                      "matmul2", A, shapeA, B, shapeB, C, shapeC);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }


    print_matrix(B, shapeB);
    print_matrix(C, shapeC);


    free(A);
    free(B);
    free(C);
}

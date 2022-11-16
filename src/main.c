#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "utils.h"
#include "matmul.h"
#include "clops.h"

#define MAX_SOURCE_SIZE         0x100000
#define MAX_MATRIX_DIM_SIZE     65536
#define MATRIX_SIZE             32 * 32

#define DUR_IN_SEC(s, e) (((double) e - s) / CLOCKS_PER_SEC)


int main() {
    size_t shape_A[] = {MATRIX_SIZE, MATRIX_SIZE};
    size_t shape_B[] = {MATRIX_SIZE, MATRIX_SIZE};
    size_t shape_C[] = {shape_A[0], shape_B[1]};
    float *A = (float *) malloc(sizeof(float) * shape_A[0] * shape_A[1]);
    float *B = (float *) malloc(sizeof(float) * shape_B[0] * shape_B[1]);
    float *C = (float *) malloc(sizeof(float) * shape_C[0] * shape_C[1]);

    for (size_t i = 0; i < shape_A[0] * shape_A[1]; i++) {
        A[i] = 1.0f;
    }
    for (size_t i = 0; i < shape_B[0] * shape_B[1]; i++) {
        B[i] = 2.0f;
    }


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

    clock_t start, end;

    // Using CPU
    start = clock();
    matmul(A, shape_A, B, shape_B, C);
    end = clock();

    double duration = DUR_IN_SEC(start, end);


    printf("CPU calculation duration in seconds: %f\n", duration);

    memset(C, 0, sizeof(float) * shape_C[0] * shape_C[1]);

    // Using GPU

    cl_device_id device_id;
    cl_context ctx;
    cl_program prog;
    cl_command_queue cmd_queue;

    start = clock();
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
                                      "matmul1", A, shape_A, B, shape_B, C, shape_C);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }
    end = clock();

    duration = DUR_IN_SEC(start, end);


    printf("GPU calculation (method 1) duration in seconds: %f\n", duration);

    memset(C, 0, sizeof(float) * shape_C[0] * shape_C[1]);

    // Using GPU (Method 2)

    start = clock();
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
                                      "matmul2", A, shape_A, B, shape_B, C, shape_C);
    if (err != CL_SUCCESS) {
        fprintf(stderr, "%s", openclGetErrorString(err));
        exit(err);
    }
    end = clock();

    duration = DUR_IN_SEC(start, end);


    printf("GPU calculation (method 2) duration in seconds: %f\n", duration);

    memset(C, 0, sizeof(float) * shape_C[0] * shape_C[1]);


    free(A);
    free(B);
    free(C);
}

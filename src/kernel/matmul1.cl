__kernel void matmul1(__global const float *A,
  __global const size_t *shapeA,
  __global const float *B,
  __global const size_t *shapeB,
  __global float *C,
  const size_t K /* col size of A, row size of B */ ) {

  const int row_index = get_global_id(0);
  const int col_index = get_global_id(1);

  float acc = 0.0f;

  for (size_t k = 0; k < K; k++) {
    acc += A[row_index + k * shapeA[0]] * B[col_index * K + k];
  }

  C[col_index * shapeA[0] + row_index] = acc;
}
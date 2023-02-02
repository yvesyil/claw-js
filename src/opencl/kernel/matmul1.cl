// TODO implement type agnostic kernel
__kernel void matmul1(__global const float *lhs,
  __global const size_t *lhs_dlen,
  __global const float *rhs,
  __global const size_t *rhs_dlen,
  __global float *res,
  const size_t K /* col size of lhs, row size of rhs */ ) {

  const int row_index = get_global_id(0);
  const int col_index = get_global_id(1);

  float acc = 0.0f;

  for (size_t k = 0; k < K; k++) {
    acc += lhs[row_index + k * lhs_dlen[0]] * rhs[col_index * K + k];
  }

  res[col_index * lhs_dlen[0] + row_index] = acc;
}
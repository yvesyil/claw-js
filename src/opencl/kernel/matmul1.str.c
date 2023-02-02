// auto generated file.
const char *_opencl_kernel_matmul1 = 
"// TODO implement type agnostic kernel\n"
"__kernel void matmul1(__global const float *lhs,\n"
"  __global const size_t *lhs_dlen,\n"
"  __global const float *rhs,\n"
"  __global const size_t *rhs_dlen,\n"
"  __global float *res,\n"
"  const size_t K /* col size of lhs, row size of rhs */ ) {\n"
"  const int row_index = get_global_id(0);\n"
"  const int col_index = get_global_id(1);\n"
"  float acc = 0.0f;\n"
"  for (size_t k = 0; k < K; k++) {\n"
"    acc += lhs[row_index + k * lhs_dlen[0]] * rhs[col_index * K + k];\n"
"  }\n"
"  res[col_index * lhs_dlen[0] + row_index] = acc;\n"
"}\n";
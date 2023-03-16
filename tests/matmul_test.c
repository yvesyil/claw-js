#include "unity/unity.h"
#include "../include/claw.h"
#include "time.h"
#include "naive_impl.h"

static struct claw_mat flt32_lhs;
static struct claw_mat flt32_rhs;
static struct claw_mat res;

void setUp()
{
	claw_create_matrix_identity(&flt32_lhs, 1024, 1024, CLAW_FLT32);
	claw_create_matrix_identity(&flt32_rhs, 1024, 1024, CLAW_FLT32);
}

void tearDown()
{
	claw_free(&flt32_lhs);
	claw_free(&flt32_rhs);
	claw_free(&res);
}

void matmul_test()
{
	struct claw_mat cpu_res;
	claw_create_matrix(&cpu_res, 1024, 1024, CLAW_FLT32);

	claw_err err = claw_matmul(&flt32_lhs, &flt32_rhs, &res);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

	naive_cpu_matmul((float *)flt32_lhs.data, flt32_lhs.dlen, (float *)flt32_rhs.data, flt32_rhs.dlen, (float *)cpu_res.data);

	char msg[256];
	for (size_t i = 0; i < res.dlen[0]; i++) {
		for (size_t j = 0; j < res.dlen[1]; j++) {
			float claw_val;
			float cpu_val;
			claw_matrix_get_idx(&res, i, j, &claw_val);
			claw_matrix_get_idx(&cpu_res, i, j, &cpu_val);

			sprintf(msg, "ERROR @ IDX %lu:%lu : ", i, j);
			strcat(msg, "values are not equal on index");
			TEST_ASSERT_TRUE_MESSAGE(claw_val == cpu_val, msg);
		}
	}
}

void matmul_benchmark_test()
{
	// warmup
	claw_matmul(&flt32_lhs, &flt32_rhs, &res);

	int sizes[] = {
		1 << 2,
		1 << 3,
		1 << 4,
		1 << 5,
		1 << 6,
		1 << 7,
		1 << 8,
		1 << 9,
	};
	int iterations = 10;
	double duration[10] = {0};

	for (int j = 0; j < iterations; j++) {
		for (int i = 0; i < sizeof(sizes) / sizeof(int); i++) {
			claw_create_matrix_rand_unit(&flt32_lhs, sizes[i], sizes[i], CLAW_FLT32);
			claw_create_matrix_rand_unit(&flt32_rhs, sizes[i], sizes[i], CLAW_FLT32);

			clock_t start = clock();
			claw_matmul(&flt32_lhs, &flt32_rhs, &res);
			clock_t end = clock();
			duration[i] += CLK_DUR_IN_MS(start, end);
		}
	}

	for (int i = 0; i < sizeof(sizes) / sizeof(int); i++) {
		printf("%.2f ms\n", duration[i] / iterations);
	}
}

int main()
{
	claw_init();
	UNITY_BEGIN();
	RUN_TEST(matmul_benchmark_test);
	RUN_TEST(matmul_test);
	return UNITY_END();
}
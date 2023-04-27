#include "unity/unity.h"
#include "../include/claw.h"
#include "time.h"

static struct claw_mat m1;
static struct claw_mat m2;

void setUp()
{
	claw_create_matrix_identity(&m1, 1024, 1024, CLAW_FLT32);
	claw_create_matrix_identity(&m2, 1024, 1024, CLAW_FLT32);
}

void tearDown()
{
	claw_free(&m1);
	claw_free(&m2);
}

void mataddmat_test()
{
	// warmup
	claw_mataddmat(&m1, &m2);

	clock_t start = clock();
	claw_mataddmat(&m1, &m2);
	clock_t end = clock();
	double duration = CLK_DUR_IN_MS(start, end);

	printf("\n%lf ms\n", duration);
}

void matsubmat_test()
{
	claw_matsubmat(&m1, &m2);
	claw_matsubmat(&m1, &m2);

	claw_print_matrix_stdout(&m2);
}

void matscale_test()
{
	claw_err err;

	float val = 69.0;
	err = claw_matscale(&m1, &val);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

	//claw_print_matrix_stdout(&m1);
}

void hadamard_test()
{
	claw_err err;
	struct claw_mat res;

	float val = 69.0;
	err = claw_matscale(&m1, &val);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));
	err = claw_matrix_set_idx(&m2, 3, 3, &val);
	err = claw_hadamard(&m1, &m2, &res);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

	claw_print_matrix_stdout(&res);
}

void matrix_copy_test()
{
	float val = 69;
	claw_create_matrix_fill(&m1, 1024, 1024, CLAW_FLT32, &val);
	claw_matrix_copy(&m1, &m2);

	float test_val;
	char msg[256];
	for (size_t i = 0; i < m1.dlen[0]; i++) {
		for (size_t j = 0; j < m1.dlen[1]; j++) {
			claw_matrix_get_idx(&m2, i, j, &test_val);
			sprintf(msg, "ERROR @ IDX %lu:%lu : ", i, j);
			strcat(msg, "value shoul've been equal to 69.");
			TEST_ASSERT_TRUE_MESSAGE(test_val == val, msg);
		}
	}
}

void matrix_cast_test()
{
	float val = 420;
	claw_create_matrix_fill(&m1, 1024, 1024, CLAW_FLT32, &val);
	claw_matrix_cast_inplace(&m1, CLAW_FLT64);

	double test_val;
	char msg[256];
	for (size_t i = 0; i < m1.dlen[0]; i++) {
		for (size_t j = 0; j < m1.dlen[1]; j++) {
			claw_matrix_get_idx(&m2, i, j, &test_val);
			sprintf(msg, "ERROR @ IDX %lu:%lu : ", i, j);
			strcat(msg, "value should've been equal to 420.");
			TEST_ASSERT_TRUE_MESSAGE(test_val == val, msg);
		}
	}
}

int main()
{
	claw_init();
	UNITY_BEGIN();
	RUN_TEST(mataddmat_test);
	RUN_TEST(matsubmat_test);
	RUN_TEST(matscale_test);
	RUN_TEST(hadamard_test);
	RUN_TEST(matrix_copy_test);
	RUN_TEST(matrix_cast_test);
	return UNITY_END();
}
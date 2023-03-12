#include "unity/unity.h"
#include "../include/claw.h"

static struct claw_mat flt32_mat;
static struct claw_mat flt64_mat;

void setUp()
{
	claw_create_matrix_rand_unit(&flt32_mat, 16, 8, CLAW_FLT32);
	claw_create_matrix_rand_unit(&flt32_mat, 5, 10, CLAW_FLT64);
}

void tearDown()
{
	claw_free(&flt32_mat);
}

void index_mat_flt32()
{
	float old_val;
	float new_val = 3;
	claw_err err;

	err = claw_matrix_get_idx(&flt32_mat, 1, 3, &old_val);
	printf("%f", old_val);

	err = claw_matrix_set_idx(&flt32_mat, 1, 3, &new_val);
	claw_print_matrix_stdout(&flt32_mat);
}

void index_mat_flt64()
{
	double old_val;
	double new_val = 3;
	claw_err err;

	err = claw_matrix_get_idx(&flt64_mat, 1, 3, &old_val);
	printf("%f", old_val);

	err = claw_matrix_set_idx(&flt64_mat, 1, 3, &new_val);
	claw_print_matrix_stdout(&flt64_mat);
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(index_mat_flt32);
	RUN_TEST(index_mat_flt64);
	return UNITY_END();
}

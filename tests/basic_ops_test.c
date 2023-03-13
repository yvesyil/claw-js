#include "unity/unity.h"
#include "../include/claw.h"
#include "time.h"

static struct claw_mat m1;
static struct claw_mat m2;

void setUp()
{
	claw_init();
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

	claw_print_matrix_stdout(&m2);
	printf("\n%lf ms\n", duration);
}

void matrix_copy_test()
{
	float val = (float)69;
	claw_create_matrix_fill(&m1, 1024, 1024, CLAW_FLT32, &val);
	claw_matrix_copy(&m1, &m2);
	claw_print_matrix_stdout(&m2);
}

void matrix_cast_test()
{
	float val = (float)420;
	claw_create_matrix_fill(&m1, 1024, 1024, CLAW_FLT32, &val);
	claw_matrix_cast_inplace(&m1, CLAW_FLT64);
	claw_print_matrix_stdout(&m1);
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(mataddmat_test);
	RUN_TEST(matrix_copy_test);
	RUN_TEST(matrix_cast_test);
	return UNITY_END();
}
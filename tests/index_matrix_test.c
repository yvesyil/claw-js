#include "unity/unity.h"
#include "../include/claw.h"

static struct claw_mat int8_mat;
static struct claw_mat uint8_mat;
static struct claw_mat int16_mat;
static struct claw_mat uint16_mat;
static struct claw_mat int32_mat;
static struct claw_mat uint32_mat;
static struct claw_mat int64_mat;
static struct claw_mat uint64_mat;
static struct claw_mat flt32_mat;
static struct claw_mat flt64_mat;

void setUp()
{
	int64_t val = 2;
	uint64_t uval = 2;
	claw_create_matrix_fill(&int8_mat, 10, 10, CLAW_INT8, &val);
	claw_create_matrix_fill(&uint8_mat, 10, 10, CLAW_UINT8, &uval);
	claw_create_matrix_fill(&int16_mat, 10, 10, CLAW_INT16, &val);
	claw_create_matrix_fill(&uint16_mat, 10, 10, CLAW_UINT16, &uval);
	claw_create_matrix_fill(&int32_mat, 10, 10, CLAW_INT32, &val);
	claw_create_matrix_fill(&uint32_mat, 10, 10, CLAW_UINT32, &uval);
	claw_create_matrix_fill(&int64_mat, 10, 10, CLAW_INT64, &val);
	claw_create_matrix_fill(&uint64_mat, 10, 10, CLAW_UINT64, &uval);
	claw_create_matrix_rand_unit(&flt32_mat, 10, 10, CLAW_FLT32);
	claw_create_matrix_rand_unit(&flt64_mat, 10, 10, CLAW_FLT64);
}

void tearDown()
{
	claw_free(&int8_mat);
	claw_free(&uint8_mat);
	claw_free(&int16_mat);
	claw_free(&uint16_mat);
	claw_free(&int32_mat);
	claw_free(&uint32_mat);
	claw_free(&int64_mat);
	claw_free(&uint64_mat);
	claw_free(&flt32_mat);
	claw_free(&flt64_mat);
}

void index_mat_int8()
{
}

void index_mat_uint8()
{
}

void index_mat_int16()
{
}

void index_mat_uint16()
{
}

void index_mat_int32()
{
}

void index_mat_uint32()
{
}

void index_mat_int64()
{
}

void index_mat_uint64()
{
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
	RUN_TEST(index_mat_int8);
	RUN_TEST(index_mat_uint8);
	RUN_TEST(index_mat_int16);
	RUN_TEST(index_mat_uint16);
	RUN_TEST(index_mat_int32);
	RUN_TEST(index_mat_uint32);
	RUN_TEST(index_mat_int64);
	RUN_TEST(index_mat_uint64);
	RUN_TEST(index_mat_flt32);
	RUN_TEST(index_mat_flt64);
	return UNITY_END();
}

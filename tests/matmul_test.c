#include "unity/unity.h"
#include "../include/claw.h"
#include "time.h"

static struct claw_mat int8_mat;
static struct claw_mat uint8_mat;
static struct claw_mat int16_mat;
static struct claw_mat uint16_mat;
static struct claw_mat int32_mat;

static struct claw_mat uint32_lhs;
static struct claw_mat uint32_rhs;

static struct claw_mat int64_mat;
static struct claw_mat uint64_mat;

static struct claw_mat flt32_lhs;
static struct claw_mat flt32_rhs;

static struct claw_mat flt64_mat;

static struct claw_mat res;

void setUp()
{
	claw_create_ones(&int8_mat, 10, 10, CLAW_INT8);
	claw_create_ones(&uint8_mat, 10, 10, CLAW_UINT8);
	claw_create_ones(&int16_mat, 10, 10, CLAW_INT16);
	claw_create_ones(&uint16_mat, 10, 10, CLAW_UINT16);
	claw_create_ones(&int32_mat, 10, 10, CLAW_INT32);

	claw_create_ones(&uint32_lhs, 10, 10, CLAW_UINT32);
	claw_create_ones(&uint32_rhs, 10, 10, CLAW_UINT32);

	claw_create_ones(&int64_mat, 10, 10, CLAW_INT64);
	claw_create_ones(&uint64_mat, 10, 10, CLAW_UINT64);

	claw_create_ones(&flt32_lhs, 1024, 1024, CLAW_FLT32);
	claw_create_ones(&flt32_rhs, 1024, 1024, CLAW_FLT32);

	claw_create_ones(&flt64_mat, 10, 10, CLAW_FLT64);
}

void tearDown()
{
	claw_free(&int8_mat);
	claw_free(&uint8_mat);
	claw_free(&int16_mat);
	claw_free(&uint16_mat);
	claw_free(&int32_mat);

	claw_free(&uint32_lhs);
	claw_free(&uint32_rhs);

	claw_free(&int64_mat);
	claw_free(&uint64_mat);
	claw_free(&flt32_lhs);
	claw_free(&flt32_rhs);
	claw_free(&flt64_mat);
}

void matmul_test()
{
	//claw_err err = claw_matmul(&uint32_lhs, &uint32_rhs, &res);
	for (size_t i = 0; i < 10; i++) {
		clock_t start = clock();
		claw_matmul(&flt32_lhs, &flt32_rhs, &res);
		clock_t end = clock();
		double duration = CLK_DUR_IN_MS(start, end);
		printf("%.2f ms\n", duration);
	}
	//TEST_ASSERT_TRUE(err == CLAW_SUCCESS);
}

int main()
{
	UNITY_BEGIN();
	RUN_TEST(matmul_test);
	return UNITY_END();
}
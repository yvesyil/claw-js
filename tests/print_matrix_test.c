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
	claw_create_matrix_fill(&int8_mat, 16, 10, CLAW_INT8, &val);
	claw_create_matrix_fill(&uint8_mat, 10, 16, CLAW_UINT8, &uval);
	claw_create_matrix_identity(&int16_mat, 6, 6, CLAW_INT16);
	claw_create_matrix_identity(&uint16_mat, 10, 10, CLAW_UINT16);
	claw_create_matrix_fill(&int32_mat, 10, 10, CLAW_INT32, &val);
	claw_create_matrix_fill(&uint32_mat, 25, 32, CLAW_UINT32, &uval);
	claw_create_matrix_identity(&int64_mat, 10, 10, CLAW_INT64);
	claw_create_matrix_fill(&uint64_mat, 60, 80, CLAW_UINT64, &uval);
	claw_create_matrix_rand_unit(&flt32_mat, 32, 32, CLAW_FLT32);
	claw_create_matrix_rand_unit(&flt64_mat, 100, 100, CLAW_FLT64);
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

void print_mat_int8()
{
	claw_print_matrix(stdout, &int8_mat);
	printf("shape: (%llu, %llu)\n", int8_mat.dlen[0], int8_mat.dlen[1]);
}

void print_mat_uint8()
{
	claw_print_matrix(stdout, &uint8_mat);
	printf("shape: (%llu, %llu)\n", uint8_mat.dlen[0], uint8_mat.dlen[1]);
}

void print_mat_int16()
{
	claw_print_matrix(stdout, &int16_mat);
	printf("shape: (%llu, %llu)\n", int16_mat.dlen[0], int16_mat.dlen[1]);
}

void print_mat_uint16()
{
	claw_print_matrix(stdout, &uint16_mat);
	printf("shape: (%llu, %llu)\n", uint16_mat.dlen[0], uint16_mat.dlen[1]);
}

void print_mat_int32()
{
	claw_print_matrix(stdout, &int32_mat);
	printf("shape: (%llu, %llu)\n", int32_mat.dlen[0], int32_mat.dlen[1]);
}

void print_mat_uint32()
{
	claw_print_matrix(stdout, &uint32_mat);
	printf("shape: (%llu, %llu)\n", uint32_mat.dlen[0], uint32_mat.dlen[1]);
}

void print_mat_int64()
{
	claw_print_matrix(stdout, &int64_mat);
	printf("shape: (%llu, %llu)\n", int64_mat.dlen[0], int64_mat.dlen[1]);
}

void print_mat_uint64()
{
	claw_print_matrix(stdout, &uint64_mat);
	printf("shape: (%llu, %llu)\n", uint64_mat.dlen[0], uint64_mat.dlen[1]);
}

void print_mat_flt32()
{
	claw_print_matrix(stdout, &flt32_mat);
	printf("shape: (%llu, %llu)\n", flt32_mat.dlen[0], flt32_mat.dlen[1]);
}

void print_mat_flt64()
{
	claw_print_matrix(stdout, &flt64_mat);
	printf("shape: (%llu, %llu)\n", flt64_mat.dlen[0], flt64_mat.dlen[1]);
}

int main()
{
	claw_init();
	UNITY_BEGIN();
	RUN_TEST(print_mat_int8);
	RUN_TEST(print_mat_uint8);
	RUN_TEST(print_mat_int16);
	RUN_TEST(print_mat_uint16);
	RUN_TEST(print_mat_int32);
	RUN_TEST(print_mat_uint32);
	RUN_TEST(print_mat_int64);
	RUN_TEST(print_mat_uint64);
	RUN_TEST(print_mat_flt32);
	RUN_TEST(print_mat_flt64);
	return UNITY_END();
}

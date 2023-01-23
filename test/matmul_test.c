#include "unity/unity.h"
#include "../include/Claw.h"

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
	claw_create_ones(&int8_mat, 10, 10, CLAW_INT8);
	claw_create_ones(&uint8_mat, 10, 10, CLAW_UINT8);
	claw_create_ones(&int16_mat, 10, 10, CLAW_INT16);
	claw_create_ones(&uint16_mat, 10, 10, CLAW_UINT16);
	claw_create_ones(&int32_mat, 10, 10, CLAW_INT32);
	claw_create_ones(&uint32_mat, 10, 10, CLAW_UINT32);
	claw_create_ones(&int64_mat, 10, 10, CLAW_INT64);
	claw_create_ones(&uint64_mat, 10, 10, CLAW_UINT64);
	claw_create_ones(&flt32_mat, 10, 10, CLAW_FLT32);
	claw_create_ones(&flt64_mat, 10, 10, CLAW_FLT64);
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

int main()
{
	UNITY_BEGIN();
	return UNITY_END();
}
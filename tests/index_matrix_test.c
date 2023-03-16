#include "unity/unity.h"
#include "../include/claw.h"

static struct claw_mat flt32_mat;
static struct claw_mat flt64_mat;

void setUp()
{
	float valf = 69;
	double vald = 69;
	claw_create_matrix_fill(&flt32_mat, 16, 8, CLAW_FLT32, &valf);
	claw_create_matrix_fill(&flt64_mat, 5, 10, CLAW_FLT64, &vald);
}

void tearDown()
{
	claw_free(&flt32_mat);
	claw_free(&flt64_mat);
}

void index_mat_flt32()
{
	float val;
	float new_val = 420;
	claw_err err;

	err = claw_matrix_set_idx(&flt32_mat, 1, 3, &new_val);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

	char msg[256];
	for (size_t i = 0; i < flt32_mat.dlen[0]; i++) {
		for (size_t j = 0; j < flt32_mat.dlen[1]; j++) {
			err = claw_matrix_get_idx(&flt32_mat, i, j, &val);
			TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

			sprintf(msg, "ERROR @ IDX %lu:%lu : ", i, j);
			if (i == 1 && j == 3) {
				strcat(msg, "value should've been equal to 420.");
				TEST_ASSERT_TRUE_MESSAGE(val == 420, msg);
			} else {
				strcat(msg, "value should've been equal to 69.");
				TEST_ASSERT_TRUE_MESSAGE(val == 69, msg);
			}
		}
	}
}

void index_mat_flt64()
{
	double val;
	double new_val = 420;
	claw_err err;

	err = claw_matrix_set_idx(&flt64_mat, 2, 6, &new_val);
	TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));
	
	char msg[256];
	for (size_t i = 0; i < flt64_mat.dlen[0]; i++) {
		for (size_t j = 0; j < flt64_mat.dlen[1]; j++) {
			err = claw_matrix_get_idx(&flt64_mat, i, j, &val);
			TEST_ASSERT_TRUE_MESSAGE(err == CLAW_SUCCESS, claw_get_err_str(err));

			sprintf(msg, "ERROR @ IDX %lu:%lu : ", i, j);
			if (i == 2 && j == 6) {
				strcat(msg, "value should've been equal to 420.");
				TEST_ASSERT_TRUE_MESSAGE(val == 420, msg);
			} else {
				strcat(msg, "value should've been equal to 69.");
				TEST_ASSERT_TRUE_MESSAGE(val == 69, msg);
			}
		}
	}
}

int main()
{
	claw_init();
	UNITY_BEGIN();
	RUN_TEST(index_mat_flt32);
	RUN_TEST(index_mat_flt64);
	return UNITY_END();
}

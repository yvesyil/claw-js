#include "claw/matmul.h"

claw_err claw_matmul(struct claw_mat *a, struct claw_mat *b, struct claw_mat *c)
{
	claw_err err;

	if (a->dlen[1] != b->dlen[0]) {
		err = CLAW_MATMUL_E_DIM_MISMATCH;
		fprintf(stderr, claw_get_err_str(err));
		return err;
	}

	return CLAW_SUCCESS;
}

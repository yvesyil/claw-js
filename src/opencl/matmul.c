#include "claw/matmul.h"

claw_err claw_matmul(struct claw_mat *a, struct claw_mat *b, struct claw_mat *c)
{
	if (a->dlen[1] != b->dlen[0]) {
		return CLAW_MATMUL_E_DIM_MISMATCH;
	}

	return CLAW_SUCCESS;
}

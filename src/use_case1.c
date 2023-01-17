#include <stdio.h>
#include "Claw.h"

int main()
{
	struct claw_mat a;
	struct claw_mat b;
	struct claw_mat c;
	claw_create_ones(&a, 1024, 1024, CLAW_UINT32);
	claw_create_ones(&b, 1024, 1024, CLAW_UINT32);

	claw_matmul(&a, &b, &c);

	claw_print_matrix(stdout, &c);

	claw_free(&a);
	claw_free(&b);
	claw_free(&c);
	return EXIT_SUCCESS;
}
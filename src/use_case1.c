//#include "claw_api.h"
#include <stdio.h>
#include "Claw.h"

int main()
{
	struct ClawMat a;
	struct ClawMat b;
	struct ClawMat c;
	struct ClawMat d;
	struct ClawMat e;
	claw_create_ones(&a, 6, 6, CLAW_INT8);
	claw_create_ones(&b, 6, 6, CLAW_INT16);
	claw_create_ones(&c, 6, 6, CLAW_UINT32);
	claw_create_ones(&d, 6, 6, CLAW_INT64);
	claw_create_ones(&e, 6, 6, CLAW_FLT64);

	claw_print_matrix(stdout, &a);
	claw_print_matrix(stdout, &b);
	claw_print_matrix(stdout, &c);
	claw_print_matrix(stdout, &d);
	claw_print_matrix(stdout, &e);

	claw_free(&a);
	claw_free(&b);
	claw_free(&c);
	claw_free(&d);
	claw_free(&e);
}
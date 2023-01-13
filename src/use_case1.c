//#include "claw_api.h"
#include <stdio.h>
#include "Claw.h"

int main()
{
	struct ClawMat a;
	struct ClawMat b;
	claw_create_ones(&a, 1024, 1024, CLAW_UINT32);
	claw_create_ones(&b, 1024, 1024, CLAW_UINT32);

	//claw_matmul();

	claw_free(&a);
	claw_free(&b);
}
#ifndef CLAW_JS_INCLUDE_CLAW_BASIC_OPS_H
#define CLAW_JS_INCLUDE_CLAW_BASIC_OPS_H

#include "error.h"
#include "matrix.h"

claw_err claw_mataddmat(struct claw_mat *m1, struct claw_mat *m2);
claw_err claw_mataddsca(struct claw_mat *m1, void *s);

claw_err claw_matsubmat(struct claw_mat *m1, struct claw_mat *m2);
claw_err claw_matsubsca(struct claw_mat *m1, void *s);

claw_err claw_matscale(struct claw_mat *m, void *s);

claw_err claw_hadamard(struct claw_mat *m1, struct claw_mat *m2, struct claw_mat *res);

#endif // CLAW_JS_INCLUDE_CLAW_BASIC_OPS_H
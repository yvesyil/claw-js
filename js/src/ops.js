import { Matrix } from "./matrix.js";
import { claw_matmul } from "./ffi.js";

export const matmul = (a, b) => {
	const c = new Matrix(a.rows, b.cols);
	claw_matmul(a._ref(), b._ref(), c._ref())
	return c;
}
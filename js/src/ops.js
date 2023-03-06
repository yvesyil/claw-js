import { Matrix } from "./matrix.js";
import * as ffi from "./ffi.js";

export const matmul = (a, b) => {
  const c = new Matrix(a.rows, b.cols);
  ffi.claw_matmul(a._ref(), b._ref(), c._ref());
  return c;
}

export const add = (a, b) => {
  if (a instanceof Matrix && b instanceof Matrix) {
    let c = a.copy();
    ffi.claw_mataddmat(b._ref(), c._ref());
    return c;
  }
}
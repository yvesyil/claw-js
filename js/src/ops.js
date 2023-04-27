import { Float32Matrix } from "./matrix.js";
import * as ffi from "./ffi.js";

export const matmul = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = new Float32Matrix(a.rows, b.cols);
    ffi.claw_matmul(a._ref(), b._ref(), c._ref());
    return c;
  } else {
    throw new Error('unsupported data type');
  }
}

export const add = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = a.copy();
    ffi.claw_mataddmat(b._ref(), c._ref());
    return c;
  } else {
    throw new Error('unsupported data type');
  }
}

export const sub = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = a.copy();
    ffi.claw_matsubmat(b._ref(), c._ref());
    return c;
  } {
    throw new Error('unsupported data type');
  }
}

export const hadamard = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = new Float32Matrix(a.rows, a.cols);
    ffi.claw_hadamard(a._ref(), b._ref(), c._ref());
    return c;
  } {
    throw new Error('unsupported data type');
  }
}
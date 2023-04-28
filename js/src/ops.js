const { Float32Matrix } = require("./matrix");
const ffi = require("./ffi");

const matmul = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = new Float32Matrix(a.rows, b.cols);
    ffi.claw_matmul(a._ref(), b._ref(), c._ref());
    return c;
  } else {
    throw new Error('unsupported data type');
  }
}

const add = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = a.copy();
    ffi.claw_mataddmat(b._ref(), c._ref());
    return c;
  } else {
    throw new Error('unsupported data type');
  }
}

const subtract = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = a.copy();
    ffi.claw_matsubmat(b._ref(), c._ref());
    return c;
  } {
    throw new Error('unsupported data type');
  }
}

const hadamard = (a, b) => {
  if (a instanceof Float32Matrix && b instanceof Float32Matrix) {
    const c = new Float32Matrix(a.rows, a.cols);
    ffi.claw_hadamard(a._ref(), b._ref(), c._ref());
    return c;
  } {
    throw new Error('unsupported data type');
  }
}

module.exports = {
  add,
  subtract,
  matmul,
  hadamard
};
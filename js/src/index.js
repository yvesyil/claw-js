import { matmul, add, sub, hadamard } from "./ops.js";
import { Float32Mat } from "./matrix.js";
import { claw_init } from "./ffi.js";

claw_init();

export default {
  Float32Mat,
  matmul,
  add,
  sub,
  hadamard,
};
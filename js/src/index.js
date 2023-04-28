const { matmul, add, sub, hadamard } = require("./ops");
const { Float32Matrix } = require("./matrix");
const { claw_init } = require("./ffi");

claw_init();

module.exports = {
  Float32Matrix,
  matmul,
  add,
  sub,
  hadamard,
};
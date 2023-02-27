import { matmul } from "./src/ops.js";
import { Float32Mat } from "./src/matrix.js";
import { claw_init } from "./src/ffi.js";

claw_init();

export default {
	Float32Mat,
	matmul,
};
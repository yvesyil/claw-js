import { matmul } from "./src/ops.js";
import { Float32Mat } from "./src/matrix.js";
import { claw_init } from "./src/ffi.js";

export default {
    context: claw_init(),
    Float32Mat,
    matmul,
};
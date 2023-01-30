import ffi from 'ffi-napi';
import ref from 'ref-napi';
import primitives from './primitives.js';
import * as dotenv from 'dotenv';
dotenv.config()

export const {
    claw_create_matrix,
    claw_create_ones,
    claw_matmul,
    claw_print_matrix_stdout
} = ffi.Library(process.env.LIBCLAW_PATH, {
    'claw_create_matrix': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int]],
    'claw_create_ones': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int]],
    'claw_matmul': [ref.types.int, [primitives._mat_ptr, primitives._mat_ptr, primitives._mat_ptr]],
    'claw_print_matrix_stdout': [ref.types.void, [primitives._mat_ptr]]
});

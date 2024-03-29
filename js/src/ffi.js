import ffi from 'ffi-napi';
import ref from 'ref-napi';
import primitives from './primitives.js';
import * as dotenv from 'dotenv';
import path from 'path';

const __dirname = path.resolve();

dotenv.config({ path: `${__dirname}/node_modules/claw-js/.env` });

export const {
  claw_init,

  // matrix
  claw_create_matrix,
  claw_create_matrix_fill,
  claw_create_matrix_rand_unit,
  claw_create_matrix_identity,
  claw_matrix_get_idx,
  claw_matrix_set_idx,
  claw_matrix_copy,

  // ops
  claw_matmul,
  claw_mataddmat,
  claw_print_matrix_stdout
} = ffi.Library(process.env.LIBCLAW_PATH, {
  'claw_init': [ref.types.int, []],

  // matrix
  'claw_create_matrix': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int]],
  'claw_create_matrix_fill': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int, ref.refType(ref.types.void)]],
  'claw_create_matrix_rand_unit': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int]],
  'claw_create_matrix_identity': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.types.int]],
  'claw_matrix_get_idx': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.refType(ref.types.void)]],
  'claw_matrix_set_idx': [ref.types.int, [primitives._mat_ptr, ref.types.ulonglong, ref.types.ulonglong, ref.refType(ref.types.void)]],
  'claw_matrix_copy': [ref.types.int, [primitives._mat_ptr, primitives._mat_ptr]],

  // ops
  'claw_matmul': [ref.types.int, [primitives._mat_ptr, primitives._mat_ptr, primitives._mat_ptr]],
  'claw_mataddmat': [ref.types.int, [primitives._mat_ptr, primitives._mat_ptr]],
  'claw_print_matrix_stdout': [ref.types.void, [primitives._mat_ptr]]
});

import util from 'util';
import ref from 'ref-napi';
import primitives from './primitives.js';
import * as ffi from './ffi.js';

export class Matrix {
  #_mat_obj;

  constructor(rows, cols) {
    this.rows = rows;
    this.cols = cols;
    this.#_mat_obj = new primitives._mat;
  }

  _ref() {
    return this.#_mat_obj.ref();
  }

  [util.inspect.custom](depth, opts) {
    ffi.claw_print_matrix_stdout(this._ref());
    return this;
  }

  print() {
    ffi.claw_print_matrix_stdout(this._ref());
    return this;
  }

  /**
   * @param {Matrix} mat
   */
  add(mat) {
    ffi.claw_mataddmat(mat._ref(), this._ref());
    return this;
  }
}


export class Float32Mat extends Matrix {
  constructor(rows, cols) {
    super(rows, cols);
  }

  fill(val = 0) {
    let buf = Buffer.alloc(4);
    buf.writeFloatLE(val);
    buf.type = ref.types.float;
    ffi.claw_create_matrix_fill(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32, buf);
    return this;
  }

  identity() {
    ffi.claw_create_matrix_identity(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
    return this;
  }

  rand(start = null, end = null) {
    if (start === null && end === null) {
      ffi.claw_create_matrix_rand_unit(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
    }
    return this;
  }

  get(row, col) {
    let buf = Buffer.alloc(4);
    buf.type = ref.types.float;
    ffi.claw_matrix_get_idx(this._ref(), row, col, buf);
    return buf.deref();
  }

  set(row, col, val) {
    let buf = Buffer.alloc(4);
    buf.writeFloatLE(val);
    buf.type = ref.types.float;
    ffi.claw_matrix_set_idx(this._ref(), row, col, buf);
    return this;
  }

  copy() {
    let cp = new Float32Mat(this.rows, this.cols).fill(111);
    ffi.claw_matrix_copy(this._ref(), cp._ref());
    return cp;
  }
}
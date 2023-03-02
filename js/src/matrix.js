import ref from 'ref-napi';
import primitives from './primitives.js';
import {
  claw_create_matrix,
  claw_create_matrix_fill, claw_create_matrix_identity,
  claw_create_matrix_rand_unit, claw_matrix_get_idx, claw_matrix_set_idx,
  claw_print_matrix_stdout
} from './ffi.js';

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

  print() {
    claw_print_matrix_stdout(this._ref());
  }
}


export class Float32Mat extends Matrix {
  constructor(rows, cols) {
    super(rows, cols);
    //claw_create_matrix(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
  }

  fill(val) {
    let buf = new Buffer(4);
    buf.writeFloatLE(val);
    buf.type = ref.types.float;
    claw_create_matrix_fill(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32, buf);
    return this;
  }

  identity() {
    claw_create_matrix_identity(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
    return this;
  }

  rand(start = null, end = null) {
    if (start === null && end === null)
      claw_create_matrix_rand_unit(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
    return this;
  }

  get(row, col) {
    let buf = new Buffer(4);
    buf.type = ref.types.float;
    claw_matrix_get_idx(this._ref(), row, col, buf);
    return buf.deref();
  }

  set(row, col, val) {
    let buf = new Buffer(4);
    buf.writeFloatLE(val);
    buf.type = ref.types.float;
    claw_matrix_set_idx(this._ref(), row, col, buf);
    return this;
  }
}
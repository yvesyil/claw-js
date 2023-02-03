import ref from 'ref-napi';
import primitives from './primitives.js';
import {claw_create_matrix, claw_create_matrix_fill, claw_print_matrix_stdout} from './ffi.js';

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
        claw_create_matrix(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32);
    }

    fill(n) {
        // TODO fix.
        let buf = new Buffer(4);
        buf.writeFloatLE(n);
        buf.type = ref.types.float;
        claw_create_matrix_fill(this._ref(), this.rows, this.cols, primitives._type.CLAW_FLT32, buf.ref());
        return this;
    }
}
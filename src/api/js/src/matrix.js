import primitives from './primitives.js';
import {claw_create_matrix, claw_create_ones, claw_print_matrix_stdout} from './ffi.js';

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


export class Uint32Mat extends Matrix {
    constructor(rows, cols) {
        super(rows, cols);
        claw_create_matrix(this._ref(), this.rows, this.cols, primitives._type.CLAW_UINT32);
    }

    fill(n) {
        if (n == 1) {
            claw_create_ones(this._ref(), this.rows, this.cols, primitives._type.CLAW_UINT32);
        } else {
            throw new Error('not implmeneted yet');
        }
        return this;
    }
}
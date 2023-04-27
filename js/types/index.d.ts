export declare const add: (a: Float32Matrix, b: Float32Matrix) => Float32Matrix;

export declare const sub: (a: Float32Matrix, b: Float32Matrix) => Float32Matrix;

export declare const matmul: (a: Float32Matrix, b: Float32Matrix) => Float32Matrix;

export declare const hadamard: (a: Float32Matrix, b: Float32Matrix) => Float32Matrix;

export declare class Matrix {
  constructor(rows: number, cols: number): Matrix;

  print(): void;

  shape(): number[];
}

export declare class Float32Matrix extends Matrix {
  constructor(rows: number, cols: number): Float32Matrix;

  fill(val: number = 0): Float32Matrix;

  identity(): Float32Matrix;

  random(start: number = null, end: number = null): Float32Matrix;

  get(row: number, col: number): number;

  set(row: number, col: number, val: number): Float32Matrix;

  copy(): Float32Matrix;

  add(mat: Float32Matrix): Float32Matrix;

  subtract(mat: Float32Matrix): Float32Matrix;

  T(): Float32Matrix;

  scale(val: number): Float32Matrix;
}
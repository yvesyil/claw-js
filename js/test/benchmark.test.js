const claw = require('../src/index');
const assert = require('assert');
const {naiveMatmul, naiveMatrix, getRandomInclusive} = require('./common');

describe('Benchmark Float32', () => {
  describe('1x784 * 784x100', () => {
    it('should be faster than naive multiply', () => {
      let a = new claw.Float32Matrix(1, 784).random();
      let b = new claw.Float32Matrix(784, 100).random();

      claw.matmul(a, b);

      a = new claw.Float32Matrix(1, 784).random();
      b = new claw.Float32Matrix(784, 100).random();

      let start = performance.now();
      let d = claw.matmul(a, b);
      let end = performance.now();
      let gpuTime = end - start;

      let x = naiveMatrix(1, 784, () => getRandomInclusive(0, 1));
      let y = naiveMatrix(784, 100, () => getRandomInclusive(0, 1));

      start = performance.now();
      let z = naiveMatmul(x, y);
      end = performance.now();
      let cpuTime = end - start;

      assert(gpuTime < cpuTime);
    });
  });
});
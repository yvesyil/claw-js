import claw from '../index.js';
import assert from 'assert';
import {naiveMatmul, naiveMatrix, getRandomInclusive} from './common.js';

describe('Benchmark Float32', () => {
  describe('1x784 * 784x100', () => {
    it('should be faster than naive multiply', () => {
      let a = new claw.Float32Mat(1, 784).fill(69);
      let b = new claw.Float32Mat(784, 100).fill(69);

      claw.matmul(a, b);

      a = new claw.Float32Mat(1, 784).fill(69);
      b = new claw.Float32Mat(784, 100).fill(69);

      let start = performance.now();
      let d = claw.matmul(a, b);
      let end = performance.now();
      let gpuTime = end - start;

      let x = naiveMatrix(1, 784, () => 69.0);
      let y = naiveMatrix(784, 100, () => 69.0);

      start = performance.now();
      let z = naiveMatmul(x, y);
      end = performance.now();
      let cpuTime = end - start;

      assert(gpuTime < cpuTime);
    });
  });
});
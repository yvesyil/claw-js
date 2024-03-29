import claw from '../index.js';
import assert from 'assert';

const mockValue = 69

describe('Matrix', () => {
  describe('#set', () => {
    it('should set the value in the given index to given value', () => {
      const a = new claw.Float32Mat(10, 10).fill(3);

      a.set(3, 8, mockValue); 
      
      for (let i = 0; i < a.rows; i++) {
        for (let j = 0; j < a.cols; j++) {
          let val = a.get(i, j);
          if (i === 3 && j === 8) {
            assert(val === mockValue, `the value should've been equal to ${mockValue}`);
          } else {
            assert(val !== mockValue && val === 3, `the value shouldn't have been equal to ${mockValue}`);
          }
        }
      }
    });
  });

  describe('#get', () => {
    it('should return the value in the given index', () => {
      const a = new claw.Float32Mat(6, 6).identity();

      for (let i = 0; i < a.rows; i++) {
        for (let j = 0; j < a.cols; j++) {
          let val = a.get(i, j);
          if (i === j) {
            assert(val === 1, `the value should've been equal to 1`);
          } else {
            assert(val === 0, `the value should've been equal to 0`);
          }
        }
      }
    });
  });

  describe('#add', () => {
    it('should add two matrices inplace', () => {
      const a = new claw.Float32Mat(6, 6).fill(2);
      const b = new claw.Float32Mat(6, 6).identity();

      a.add(b);

      for (let i = 0; i < a.rows; i++) {
        for (let j = 0; j < a.cols; j++) {
          let val = a.get(i, j);
          if (i === j) {
            assert(val === 3, `the value should've been equal to 3`);
          } else {
            assert(val === 2, `the value should've been equal to 2`);
          }
        }
      }
    })
  });

  describe('#copy', () => {
    it('should create a copy of the matrix', () => {
      const a = new claw.Float32Mat(6, 6).fill(mockValue);

      const b = a.copy();

      for (let i = 0; i < b.rows; i++) {
        for (let j = 0; j < b.cols; j++) {
          let val = b.get(i, j);
          assert(val === mockValue, `the value should've been equal to ${mockValue}`)
        }
      }
    });
  });
});

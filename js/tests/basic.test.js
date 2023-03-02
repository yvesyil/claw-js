import claw from '../index.js';

test('float matrix (32 x 32) matmul', () => {
  const a = new claw.Float32Mat(32, 32).fill(2);
  const b = new claw.Float32Mat(32, 32).fill(1);

  const c = claw.matmul(a, b);
  c.print();
});

test('float identity matrix', () => {
  const eye = new claw.Float32Mat(6, 6).identity();
  eye.print();
});
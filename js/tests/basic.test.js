import claw from '../index.js';

test('float matrix (32 x 32) matmul', () => {
  const a = new claw.Float32Mat(32, 32).fill(2);
  const b = new claw.Float32Mat(32, 32).fill(1);

  const c = claw.matmul(a, b);

  a.add(b);

});

test('float identity matrix', () => {
  const eye = new claw.Float32Mat(6, 6).identity();
  const fillMat = new claw.Float32Mat(6, 6).fill(1);
  eye.add(fillMat);
  console.log(eye);
  console.log(eye.get(5, 5));
  console.log(new claw.Float32Mat(2, 2).fill(1));
});
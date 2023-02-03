import claw from '../index.js';

test('uint32 matrix (32 x 32) matmul', () => {
    const a = new claw.Float32Mat(32, 32).fill(2);
    const b = new claw.Float32Mat(32, 32).fill(1);

    const c = claw.matmul(a, b);

    c.print();
});
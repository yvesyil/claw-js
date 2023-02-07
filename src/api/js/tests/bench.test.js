import claw from '../index.js';
import {testArray, testMatrixDot, getRandomInclusive} from './common.js';

test('float 1024 x 1024 matrix multiply 100x calls benchmark', () => {
    const size = 1024;
    let a = new claw.Float32Mat(size, size).rand();
    let b = new claw.Float32Mat(size, size).rand();

    let na = testArray(size, size, () => Math.random());
    let nb = testArray(size, size, () => Math.random());
    let c;
    let nc;

    console.time('claw matmul call1');
    c = claw.matmul(a, b);
    console.timeEnd('claw matmul call1');

    a = new claw.Float32Mat(size, size).rand();
    b = new claw.Float32Mat(size, size).rand();

    console.time('claw matmul call2');
    c = claw.matmul(a, b);
    console.timeEnd('claw matmul call2');

    console.time('matmul naive call1');
    nc = testMatrixDot(na, nb);
    console.timeEnd('matmul naive call1');

    na = testArray(size, size, () => Math.random());
    nb = testArray(size, size, () => Math.random());

    console.time('matmul naive call2');
    nc = testMatrixDot(na, nb);
    console.timeEnd('matmul naive call2');

});
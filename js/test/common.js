export function naiveMatmul(A, B) {
  let result = new Array(A.length).fill(0).map(row => new Array(B[0].length).fill(0));

  return result.map((row, i) => {
    return row.map((val, j) => {
      return A[i].reduce((sum, elm, k) => sum + (elm * B[k][j]), 0);
    })
  })
}

export function getRandomInclusive(min, max) {
  return (Math.random() * (max - min + 1) + min); // The maximum is inclusive and the minimum is inclusive
}


export function naiveMatrix(rows, cols, fn) {
  const arr = new Array(rows);
  for (let i = 0; i < arr.length; i++) {
    arr[i] = new Array(cols);
  }

  for (let i = 0; i < arr.length; i++) {
    for (let j = 0; j < arr[0].length; j++) {
      arr[i][j] = fn();
    }
  }
  return arr;
}

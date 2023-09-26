const array = [5, 1, 22, 25, 6, -1, 8, 10];
const sequence = [1, 6, -1, 10];

function isValidSubsequence(array, sequence) {
  let arrIndex = 0;
  let seqIndex = 0;
  while (arrIndex < array.length && seqIndex < sequence.length) {
    if (array[arrIndex] === sequence[seqIndex]) seqIndex++;
    arrIndex++;
  }
  return seqIndex === sequence.length;
}

console.log(isValidSubsequence(array, sequence));

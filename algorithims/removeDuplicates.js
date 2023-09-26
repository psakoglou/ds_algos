// remove duplicates from an array

const array = [1, 1, 2, 3, 4, 5, 5, 6];

function removeDuplicates(array) {
  const hashTable = {};
  const result = [];
  for (let i = 0; i < array.length; i++) {
    const element = array[i]; // store each index as element
    if (!hashTable[element]) {
      hashTable[element] = true;
      result.push(element);
    }
  }
  return result;
}

console.log(removeDuplicates(array));

const arrayStrings = ["Apple", "apple", "peach", "peach", "kiwi"];

function removeDuplicates(array) {
  const hashTable = {};
  const result = [];
  for (let i = 0; i < array.length; i++) {
    const element = array[i].toString(); // store each index as element and conver to string for uppercase
    const capitalElement =
      element.charAt(0).toUpperCase() + element.slice(1).toLowerCase();
    if (!hashTable[capitalElement]) {
      hashTable[capitalElement] = true;
      result.push(capitalElement);
    }
  }
  return result;
}

console.log(removeDuplicates(arrayStrings));

const s1 = "abcdefg123456"; // false
const s2 = "abcdefg123456a"; // true

function hasDuplicate(s) {
  const occurences = new Set();

  for (let i = 0; i < s.length; i++) {
    const value = s[i];
    if (occurences.has(value)) {
      return true;
    }
    occurences.add(value);
  }
  return false;
}

// array
function hasDuplicateSlow(s) {
  const occurences2 = [];

  for (let i = 0; i < s.length; i++) {
    const value = s[i];
    if (occurences2.includes(value)) {
      return true;
    }
    occurences2.push(value);
  }
  return false;
}

console.log(hasDuplicate(s1));
console.log(hasDuplicate(s2));
console.log(hasDuplicateSlow(s1));
console.log(hasDuplicateSlow(s2));

// how many times does a character occur in a string
function occurencesN(str, char) {
  let charN = 0;
  for (let i = 0; i < str.length; i++) {
    if (str[i] == char) {
      charN++;
    }
  }
  return charN;
}

console.log(occurencesN(s2, "a"));
console.log(occurencesN(s1, "a"));

// use occurancesN o(n2)
function hasDuplicate3(str) {
  for (let i = 0; i < str.length; i++) {
    if (occurencesN(str, str[i]) > 1) {
      return true;
    }
  }
  return false;
}

console.log(hasDuplicate3(s1));
console.log(hasDuplicate3(s2));

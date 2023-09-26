// create a function that returns true or false if an input is a palindrome
// example 1: input: 121 TRUE
// 1234321
// 12344321
// example 2: input: -121 FALSE
// example 3: input: 123 FALSE

// Interviewer small talk
// interviewer gives a problem description
// interviewer asks you if you saw this problem before
// interviewer asks you to spend a minute reading the desc
// he is waiting for you

// you:
// 1 minute: read the description
// 3-4 minutes: read back the description to the interviewer and
// rephrase the problem in 2-3 different ways
// make sure you are in an agreement and you ask questions if not
// this is high level i.e. what's the name of the function? what's the type of the input?
// what's the output? who's going to be using this? how fast do we want it to be?
// is it for a production system or just for internal use? how many users of this are there?
// etc.
// 2 minutes: analyze examples + keep notes
// 5-10 minutes: ideas and high level steps of how would you achieve this
// no details, mostly steps i.e. I want to covert the input, make sure it's valid
// i.e. I want to check it against its reversed input
// i.e. I will probably need to store it in an array as digits
// ask questions
// etc.
// 10 minutes: start writing code for each step
// 1-3 minutes: fine tune and test

// 1. conditional for negative numbers
// 2. turn int into an array
// 3. compare first index with last index, so on.

// 123
// digits = [1, 2, 3, 4, 4, 8, 2, 1]
//  index:   0  1  2  3  4  5  6  7
//     i              j
// length = 7 (number of elems)
// first elem is digits[0]
// second elem is digits[1]
// third elem is digits[2]
// it is not a palindrome

// function isPalindrome(n) {
//   if (n < 0) {
//     return false;
//   }

//   digits = [-1, 2, 1]; //convert_number_to_array(n); // 123 -> [1, 2, 3]
//   let i = 0;
//   let j = digits.length - 1;

//   while (i < j) {
//     if (digits[i] !== digits[j]) {
//       return false;
//     }
//     i++;
//     j--;
//   }
//   return true;

//   /*let ok = true;
//     while (i < j) {
//         ok = ok && digits[i] == digits[j]; // false && x -> false
//         i++;
//         j--;
//     }
//     return ok;*/
// }

// console.log(isPalindrome(1218));

// create a function that returns true or false if an input is a palindrome
// example 1: input: 121 TRUE
// 1234321
// 12344321
// example 2: input: -121 FALSE
// example 3: input: 123 FALSE

// compare the first element w/ the last elem and so on (2nd, 3rd until meets)
// compare the last element with the first elem, so on
// 12344321 true palindrome

// function isPalindrome(int) {
//   const digits = [1, 2, 3, 4, 4, 3, 2, 1];

//   let i = 0;
//   let j = digits.length - 1 // 7

//   // how to meet in the middle when index i crosses index j
//   while (i < j) {
//     if (int < 0) {
//       return false
//       // negatives are always bool false
//     }
//     if (digits[i] != digits[j]) {
//       return false;
//     }
//     j--
//     i++
//   }
//   return true;
// }

const input = 123219;

function isPalindrome(input) {
  input_string = input.toString();
  let i = 0;
  let j = input_string.length - 1;
  while (i < j) {
    if (input_string[i] != input_string[j]) {
      return false;
    }
    i++;
    j--;
  }
  return true;
}

console.log(isPalindrome(input));

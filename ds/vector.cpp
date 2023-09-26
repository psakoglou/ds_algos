#include <iostream>

#include <vector>


// array
// numbers = [1, 2, 3, 1, -2, 3]; (contiguous) i.e. 0x1 - 0x6 -> you only need to know the start address, and the length (address, address + length)
// what happens if I want to grow the array 
// then you need to create a new array in a new location, then copy the elements
// 1. create a new array with the new size: numbers2 = [ , , , , , , , , ] (also (address, address + length)
// 2. copy the elements: numbers2 = [1, 2, 3, 1, -2, 3, , ]
// 3. insert the new element you wanted
// numbers2 = [1, 2, 3, 1, -2, 3, 90, ]
class Vector { // vector == dynamic array
private:
	int* data; // the array variable (which is a pointer / start address) data[3] == *(data + 3)
	int index; // number of elements currently in array
	int capacity; // size of array
public:


	Vector() {
		data = new int[10]; // allocate 10 cells of type int (i.e. 40 bytes next to each other)
		index = 0;
		capacity = 10;
		std::cout << "ctor" << std::endl;
	}

	~Vector() {
		std::cout << "dtor" << std::endl;
		if (data != nullptr) {
			delete[] data;
		}
	}

	void expand() {
	
		// create a temp of same size as data
		int* temp = new int[capacity];

		// copy all data elements to temp
		for (int i = 0; i < index; i++){
			temp[i] = data[i];
		}

		// delete data
		delete[] data;

		// increase the capacity
		int new_capacity = capacity * 2;

		// allocate new_capacity 
		data = new int[new_capacity];

		// copy old elements
		for (int i = 0; i < index; i++) {
			data[i] = temp[i];
		}

		capacity = new_capacity;
		std::cout << "expanding to capacity: " << new_capacity << std::endl;

		// delete temp
		delete[] temp;

	}

	// data = [1, 2, 3, 4, 5, 6]
	// new_data = [[] [] [] [] [] [] [] [] [] [] [] []]
	// copy the old data to new data
	// new_data = [1, 2, 3, 4, 5, 6, [] [] [] [] [] []]
	// delete the old data
	// delete[] data; 
	// data = new_data
	void push_back(int elem) {
		if (index >= capacity && capacity > 0) {
			expand();
		}
		std::cout << "capacity: " << capacity << std::endl;
		std::cout << "insert at index: " << index << std::endl;
		data[index] = elem; // index = 0 => data[0] = 10
		index++;
		print();
		std::cout << "next element will be inserted at index: " << index << std::endl;

	}

	void pop_back(int elem) {

	}

	bool find(int elem) {
		return true;
	}

	// empty the vector but keep the capacity
	void clear() {

	}

	void print() {
		for (int i = 0; i < index; i++) {
			std::cout << data[i] << " ";
		}
		std::cout << std::endl;
	}

};
bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        // 121 -> {1, 2, 3}
        // 100 * 1 + 10 * 2 + 1 * 1
        // 1
        // 10
        // 100
        // 1000
        // 10000
        // ....
        // 38493 -> 10000 * 3 + 1000 * 8 + 100 * 4 + 10 * 9 + 1 * 3
        // 38493 % 10 -> 3
        // 38493 / 10 -> 3849
        // 3849 % 10 -> 9
        // 3849 / 10 -> 384
        // 384 % 10 -> 4
        // 384 / 10 -> 38
        // 38 % 10 -> 8
        // 38 / 10 -> 3
        // 
        // 
        std::vector<int> digits; 
		

        while (x > 0) { 
            int last_digit = x % 10;
            digits.insert(digits.begin(), last_digit);
            x = x / 10;
        }

        // x = 121
        // I want to put each digit in the x variable into a new array
        // std::vector digits = [1, 2, 1] (new array) 
        // create a new array of reversed digits array
        // std::vector reverse_digits = [6, 3, 0]
        // compare indexes of digits and new reveresed digit array

  
        std::vector<int> reverse = {};

        for (int i = digits.size() - 1; i >= 0; i--) {
            reverse.push_back(digits[i]);
        }

        for (int i = 0; i < digits.size(); i++ ) {
            if (digits[i] != reverse[i]) {
                return false;
            } 
        }

        return true; 
        // start, end, step
        // digits holds the elems -> container
        // a container has index to point to elements
        // index = 0 -> first element, digits[0]
        // index = size - 1 -> last element
    }
int main() {


	/*Vector v; 

	for (int i = 100; i < 200; i++) {
		std::cout << "inserting elem = " << i << std::endl;
		v.push_back(i);
	}
	v.print();*/

	std::cout << isPalindrome(123454321) << std::endl;

    

	return 0;
}

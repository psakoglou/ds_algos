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

	void resize() {

	}

	// data = [1, 2, 3, 4, 5, 6]
	// new_data = [[] [] [] [] [] [] [] [] [] [] [] []]
	// copy the old data to new data
	// new_data = [1, 2, 3, 4, 5, 6, [] [] [] [] [] []]
	// delete the old data
	// delete[] data; 
	// data = new_data
	void push_back(int elem) {
		if (index >= capacity) {
			resize();
			std::cout << "can't fit more elements" << std::endl;
			return;
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

int main() {

	Vector v; 
	for (int i = 100; i < 200; i = i + 5) {
		std::cout << "inserting elem = " << i << std::endl;
		v.push_back(i);
	}
	v.print();

	return 0;
}

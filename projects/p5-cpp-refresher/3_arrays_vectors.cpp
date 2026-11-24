// L3Harris_prac.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <memory>
#include <iomanip>
#include <limits>
#include <bitset>
#include <string>
#include <algorithm>
#include <array>
#include <typeinfo>
#include <vector>
#include <iterator>
#include <span>

//################# E3.12.1 C++ Arrays #################
/*
Array Engineering Strategy
Pointer + count — Flexible interfaces   --> void process(const int* arr, int count); processing arrays of varying sizes, working with C libraries, or handling buffers and memory regions.
Array reference — Fixed-size interfaces --> void process(const int (&arr)[5]);  enforcing size


C++ Raw Arrays — Pointer vs. Reference
Consideration				Pointer style	            Array-reference style
Syntax						int* arr					int (&arr)[5]
Array size preserved		❌ No						✅ Yes
Requires separate count		Usually						No
Accepts	varied array sizes	✅ Yes						❌ Fixed at 5
Can accept nullptr			✅ Yes						❌ No
Can access a subrange		✅ Yes						Less convenient
Array copied				No							No
Bounds checking				❌ No						❌ No
C API compatibility			✅ Excellent				❌ Not directly
Compile-time size checking	❌ No						✅ Yes

pointer style
void process(int arr[], int count);  // Emphasizes array usage <==> void process(int* arr, int count);   // Emphasizes pointer usage

reference style
void process(const int (&arr)[5]);  // enforcing size

> = C++ 20  best of both
void process(std::span<const int> arr) // size-aware, non-owning view of contiguous elements, but it doesn't own their storage.

*** Neither pointer nor reference syntax automatically guarantees bounds safety

*/

//void printArrayA(const int numbers[], int count) {
//	for (int i = 0; i < count; i++) {
//		std::cout << numbers[i] << "\n";
//	}
//}
//
//void printArrayB(const int(&numbers)[5]) {
//	for (int value : numbers) {
//		std::cout << value << "\n";
//	}
//}
//
//void printArrayC(std::span<const int> arr) {
//	for (int value : arr) {
//		std::cout << value << "\n";
//	}
//	//std::cout << arr.size() << "\n";  // you get to use .size()
//}
//
//int main(){
//	std::cout << "Welcome to E3.12.1 \n\n";
//
//	int numbers[5] = {12,24,36,48,60};
//
//	int sumNumbers = 0;
//	for (int i = 0; i < std::size(numbers); i++) {
//		std::cout << "numbers element "<< (i + 1) << " is " << numbers[i] << ".\n";
//		sumNumbers += numbers[i];
//	}
//
//	std::cout << "\nsum of numbers is: " << sumNumbers << ".\n";
//	std::cout << "numbers mean: " << sumNumbers / std::size(numbers) << ".\n\n";
//
//	numbers[2] = 100;
//
//	for (int i = 0; i < std::size(numbers); i++) {
//		std::cout << "modified numbers element " << (i + 1) << " is " << numbers[i] << ".\n";
//	}
//
//	std::cout << "\nnumbers has " << std::size(numbers) << " elements.\n\n";
//
//	//std::cout << "\nOOB access to numbers generates values like this --> " << numbers[10] << " but still exited with code 0.\n\n";
//
//	//std::cout << "\nThe IDE is kind enough to warn me at least. \n ";
//
//	printArrayA(numbers, std::size(numbers));
//	printArrayB(numbers);
//	printArrayC(numbers);
//}
//################# END E3.12.1 #################


//################# E3.12.2 C++ Vectors #################
/*
A std::vector stores elements of the same type in contiguous memory, like an array, but can grow and shrink dynamically.
#include <vector>

std::vector<int> numbers = {10, 20, 30};
numbers.push_back(40);  // Append 40
numbers.pop_back();     // Remove last element
numbers.size();         // Number of elements
numbers.at(0);          // Bounds-checked access
numbers[0];             // Unchecked access

Array vs. Vector
Property					Raw array			std::vector
Size						Fixed				Dynamic
Contiguous storage			Yes					Yes
.size()						No					Yes
Bounds-checked access		No built-in .at()	.at()
Append/remove elements		No					Yes
Manages dynamic storage		No					Yes

std::vector — Common Function Quick Reference
Function		Purpose
.front()		Access first element	// require a nonempty vector.  return references to existing elements, so you can read or modify them when the vector isn't const
.back()			Access last element    // require a nonempty vector.   return references to existing elements, so you can read or modify them when the vector isn't const
.push_back(x)	Append element
.pop_back()		Remove last element; returns void
.size()			Number of elements    // counts actual elements
.empty()		Check whether vector has no elements
.at(i)			Bounds-checked element access
.clear()		Remove all elements
.insert(pos, x)	Insert element at specified position
.erase(pos)		Remove element at specified position
.resize(n)		Change number of elements
.capacity()		Current allocated element capacity // measures available storage before another allocation is needed.
.reserve(n)		Request capacity for at least n elements

*/
//void printVector(const std::vector<int> vec) {
//	int i = 1;
//	for (int number : vec) { std::cout << "numbers element " << (i++) << " is " << number << ".\n"; } //for thing in iterable collection, do stuff
//}
//
//int main() {
//	std::vector<int> numbers = {10, 20, 30, 40, 50};
//
//	printVector(numbers);
//
//	std::cout << "The new std::vector Numbers has " << numbers.size() << " elements.\n\n"; 
//	
//	numbers.push_back(60);
//	numbers.push_back(70);
//	printVector(numbers);
//	std::cout << "\n";
//
//	//int last_elem = numbers.pop_back(); // E0144: a value of type void cannot be used to initialize an int.
//	numbers.pop_back(); 
//	printVector(numbers);
//	std::cout << "\n";
//
//	numbers[1] = 99;
//	printVector(numbers);
//	std::cout << "\n";
//
//	int sumNumbers = 0;
//	for (int number : numbers) {
//		sumNumbers += number;
//	}
//
//	std::cout << "\nsum of numbers is: " << sumNumbers << ".\n";
//	std::cout << "numbers mean: " << static_cast<double>(sumNumbers) / numbers.size() << ".\n\n";
//
//	printVector(numbers);
//	std::cout << "\n";
//
//	//numbers[100];
//	//numbers.at(100);
//
//}
//################# END E3.12.2 #################

//################# E3.12.3 C++ Vector Memory: Size vs. Capacity #################
/*
A vector has two important properties:
- Size: Number of elements currently stored.
- Capacity: Number of elements it can hold before needing additional storage.

Parameter						Modifies original?
std::vector<int> vec			❌ Copy
const std::vector<int>& vec		❌ Read-only reference
std::vector<int>& vec			✅ Mutable reference

*/
//void printVector(const std::vector<int> vec) {
//	int i = 1;
//	for (int number : vec) { std::cout << "numbers element " << (i++) << " is " << number << ".\n"; } //for thing in iterable collection, do stuff
//}
//
//void appendVector(std::vector<int>& vec, int value) {
//
//	std::cout  << value << " added to the vector. \n";
//	vec.push_back(value);
//	std::cout << "Vector size is " << vec.size() << ".\n";
//	std::cout << "Vector capacity is " << vec.capacity() << ".\n";
//}
//
//int main() {
//
//	std::cout << "Welcome to E3.12.3 \n\n";
//	std::vector<int> numbers = { 10, 20, 30};
//
//	printVector(numbers);
//
//	std::cout << "The new std::vector Numbers has " << numbers.size() << " elements.\n\n";
//
//	std::cout << "Vector size is " << numbers.size() << ".\n";
//	std::cout << "Vector capacity is " << numbers.capacity() << ".\n";
//
//
//	for (int i = 1; i < 21; i++) { appendVector(numbers, i); }
//	printVector(numbers);
//
//	numbers.clear();
//
//	std::cout << "Vector size is " << numbers.size() << ".\n";
//	std::cout << "Vector capacity is " << numbers.capacity() << ".\n";
//
//	numbers.reserve(50);
//
//	std::cout << "Vector size is " << numbers.size() << ".\n";
//	std::cout << "Vector capacity is " << numbers.capacity() << ".\n";
//
//	std::vector<int> five_ints = { 8, 13, 21, 34, 55 };
//
//	for (int integer : five_ints) { appendVector(numbers, integer);}
//	printVector(numbers);
//
//	std::cout << "Vector size is " << numbers.size() << ".\n";
//	std::cout << "Vector capacity is " << numbers.capacity() << ".\n";
//}
//################# END E3.12.3 #################

//################# E3.12.4 C++ Vector Insertion & Erasure #################
/*
vec.insert(vec.begin() + 1, 15);  // vec elem 0 + target (zero-indexed) elem
vec.erase(vec.begin() + 2);

insertion shifts elements right; erasure shifts remaining elements left.

*/
void printVector(const std::vector<int> vec) {
	int i = 1;
	for (int number : vec) { std::cout << "numbers element " << (i++) << " is " << number << ".\n"; } //for thing in iterable collection, do stuff
}

void vectorInsert(std::vector<int>& vec, int offset, int value) {
	vec.insert(vec.begin() + offset, value);
}

int main() {

	std::cout << "Welcome to E3.12.4 \n\n";
	std::vector<int> numbers = { 10, 20, 30, 40, 50 };
	std::cout << "New Vector: \n";
	printVector(numbers);

	vectorInsert(numbers, 1, 15);
	vectorInsert(numbers, 0, 5);
	vectorInsert(numbers, (numbers.size()), 60);
	//vectorInsert(numbers, (numbers.size() - 1), 60);

	int target = 30;
	auto idx = std::find(numbers.begin(), numbers.end(), target);
	//auto iter = std::find(numbers.begin(), numbers.end(), target);

	if (idx != numbers.end()) {
		numbers.erase(idx);
	}

	//if (iter != numbers.end()) {
	//	int idx = std::distance(numbers.begin(), iter);
	//	numbers.erase(numbers.begin() + idx);
	//}

	numbers.erase(numbers.begin() + 0);

	std::cout << "\nUpdated vector: \n";
	printVector(numbers);
	std::cout << "Final Vector size is " << numbers.size() << ".\n";

}
//################# END E3.12.4 #################



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
#include <type_traits>
#include <cctype>

//################# E3.14.1 C++ Pointers & References: Address, Value, Dereference #################
/*
int number = 42;

int* ptr = &number;
int& ref = number;

Expression	Meaning
number		Original variable's value
&number		Memory address of number
ptr			Pointer holding that address
*ptr		Value at the stored address
ref			Another name for number
&ref		Address of the original variable
*/

//
//
//int main() {
//	std::cout << "Welcome to E3.14.1 \n\n";
//	int number = 42;
//	int* ptr = &number;
//	int& ref = number;
//
//
//	std::cout << "number is " << number << ".\n";
//	std::cout << "ptr is " << ptr << ".\n";
//	std::cout << "*ptr is " << *ptr << ".\n";
//	std::cout << "ref is " << ref << ".\n";
//	std::cout << "address of number is " << &number << ".\n";
//	std::cout << "address of ref is " << &ref << ".\n";
//
//	*ptr = 100;
//	std::cout << "number is " << number << ".\n";
//	std::cout << "*ptr is " << *ptr << ".\n";
//	std::cout << "ref is " << ref << ".\n";
//
//	ref = 200;
//	std::cout << "number is " << number << ".\n";
//	std::cout << "*ptr is " << *ptr << ".\n";
//	std::cout << "ref is " << ref << ".\n";
//
//	int other = 500;
//
//	ptr = &other;
//	std::cout << "number is " << number << ".\n";
//	std::cout << "*ptr is " << *ptr << ".\n";
//	std::cout << "ref is " << ref << ".\n";
//
//	*ptr = 600;
//	std::cout << "number is " << number << ".\n";
//	std::cout << "*ptr is " << *ptr << ".\n";
//	std::cout << "ref is " << ref << ".\n";
//	std::cout << "other is " << other << ".\n";
//
//
//	// Bonus 
//	//int* null_pointer = nullptr;
//	//std::cout << *null_pointer;
//	int ref_redir = 55;
//	ref = ref_redir;
//	//std::cout << "number is " << number << ".\n";
//	//std::cout << "*ptr is " << *ptr << ".\n";
//	//std::cout << "ref is " << ref << ".\n";
//	//std::cout << "other is " << other << ".\n";
//
//}
//################# END E3.14.1 #################


//################# E3.14.2 C++ Pointers & References in Functions #################
/*
void modifyByPointer(int* ptr) {
	*ptr = 100;
}

void modifyByReference(int& ref) {
	ref = 200;
}

int number = 42;

modifyByPointer(&number);
modifyByReference(number);

*/

//void addTen(int* ptr) {
//	*ptr += 10;
//}
//
//void doubleValue(int& ref) {
//	ref = ref * 2;
//}
//
//void swapValues(int* a, int* b) {
//	// dereference and stash
//	int temp_1 = *a; 
//	int temp_2 = *b;
//
//	//the actual swap step
//	*a = temp_2;
//	*b = temp_1;
//}
//
//
//
//int main() {
//	std::cout << "Welcome to E3.14.2 \n\n";
//	int alpha = 10;
//	int bravo = 20;
//
//	std::cout << "alpha was initialized to " << alpha << ".\n";
//	std::cout << "bravo was initialized to " << bravo << ".\n";
//
//	addTen(&alpha);
//	std::cout << "\nalpha is now " << alpha << ".\n";  // pass in the address of the target so it can be acted upon
//
//	doubleValue(bravo);
//	std::cout << "bravo is now " << bravo << ".\n"; // pass in the target so its address can be acted upon.
//
//	swapValues(&alpha, &bravo);
//	std::cout << "\nalpha is now " << alpha << ".\n";
//	std::cout << "bravo is now " << bravo << ".\n";
//
//
//	// Bonus 
//	int* null_pointer = nullptr;
//	//addTen(null_pointer);  // The function ultimately says "rejected"
//	//doubleValue(null_pointer);  /// Immediate no
//
//
//	/* Bonus ans.
//	Why does a pointer parameter require &alpha at the call site, while a reference parameter accepts bravo directly?
//	I do not know.  Best guess: reference parameters are already aligned with the variables address.
//
//	Can a pointer parameter receive nullptr?
//	It seems yes, but it will fail to something like --> code -1073741819 
//
//	Can a reference parameter normally be null?
//	Looks like NOPE, insta-fail
//
//	Does swapping the pointer variables themselves necessarily swap the caller's integer values?
//	Oh no, because as soon as the first swap is complete, one of those values will be lost forever, I believe the stash + individual reassigment is the way bro.
//	*/
//}
//################# END E3.14.2 #################


//################# E3.14.3 C++ Pointer Arithmetic & Arrays #################
/*
int numbers[5] = {10, 20, 30, 40, 50};

int* ptr = numbers;

std::cout << *ptr;       // 10
std::cout << *(ptr + 1); // 20
std::cout << *(ptr + 2); // 30

Important: ptr + 1 advances address by one element type i.e int a 4 bytes, char 1 byte, double 8 bytes,
*/

//void pointerPrint(int* ptr, int size) {
//
//	for (int i = 0; i < size; i++) {
//		std::cout << "Array element " << (i + 1) << " is " << *(ptr + i) << ".\n";
//	}
//	std::cout << "\n";
//}
//
//
//int main() {
//	std::cout << "Welcome to E3.14.3 \n\n";
//	int numbers[5] = { 10, 20, 30, 40, 50 };
//	int* ptr = numbers;
//
//	std::cout << "\naddress of ptr is " << ptr << ".\n";  
//	//std::cout << "\naddress of elem 0 of numbers is " << &numbers[0] << ".\n";  
//
//	std::cout << "\naddress of ptr + 1 is " << (ptr + 1) << ".\n";
//	std::cout << "\naddress of ptr + 2 is " << (ptr + 2)  << ".\n";
//	std::cout << "\nsize of int is " << sizeof(int) << ".\n\n";
//
//	pointerPrint(ptr, std::size(numbers));
//
//	*(ptr + 2) = 99;
//
//	pointerPrint(ptr, std::size(numbers));
//
//	ptr += 2;
//	std::cout << "The pointer no longer points to the first element of the array, it now points to the third element which is " << *ptr << ".\n";
//
//	ptr -= 2;
//	std::cout << "This shining example of negative pointer movement now points to the first element again and the proof is right here --> " << *ptr << ".\n";
//
//	// Bonus 
//	//std::cout << numbers[2] << ".\n";
//	//std::cout << *(numbers + 2) << ".\n"; 
//
//
//	/* Bonus ans.
//	Why does ptr + 1 advance by sizeof(int) bytes?  ---> because the + 1 adds 1 * (4 bytes) to the address of ptr.
//
//	Are numbers[2] and *(numbers + 2) equivalent? ---> Yes, element 2 vs the dereferenced array start + 2 positions right aka element 2
//
//	Can pointer arithmetic safely move outside an array's boundaries? ---> Yes but only forward and only 1 position to be used as a stop, no dereferencing, beyond that not feasible (undefined)  oh hey, the Safety Rule!
//
//	Why might pointer arithmetic be useful in embedded systems?  ---> It provides the engineer precise control over movement around the memory space.
//	*/
//}
//################# END E3.14.3 #################

//################# E3.14.4 C++ Pointer Safety & const #################
/*
int alpha = 10;
int bravo = 20;

const int* ptr = &alpha;  // Read-only access through ptr
int* const fixed = &alpha; // Cannot redirect fixed

Declaration	   			Modify value through pointer?		Redirect pointer?
=============================================================================
int* ptr				Yes									Yes
const int* ptr			No									Yes
int* const ptr			Yes									No
const int* const ptr	No									No
*/


int main() {
	std::cout << "Welcome to E3.14.4 \n\n";
	int alpha = 10;
	int bravo = 20;
	int* ptr = &alpha;

	int* nptr = nullptr;

	std::cout << "\nalpha is " << alpha << ".\n";
	std::cout << "\nptr is " << ptr << ".\n";
	std::cout << "\nThe value at ptr is " << *ptr << ".\n";

	std::cout << "Do we have a null pointer? " << (ptr == nullptr) << ".\n";
	std::cout << "Do we have a null pointer now? " << (nptr == nullptr) << ".\n";

	ptr = &bravo;
	std::cout << "\nbravo is " << bravo << ".\n";
	std::cout << "\nptr is " << ptr << ".\n";
	std::cout << "\nThe value at ptr is " << *ptr << ".\n";

	*ptr = 99;
	std::cout << "\nbravo is " << bravo << ".\n";
	std::cout << "\nptr is " << ptr << ".\n";
	std::cout << "\nThe value at ptr is " << *ptr << ".\n";

	const int* ci_ptr = &alpha;
	std::cout << "\nalpha is " << alpha << ".\n";
	std::cout << "\nci_ptr is " << ci_ptr << ".\n";
	std::cout << "\nThe value at ci_ptr is " << *ci_ptr << ".\n";

	ci_ptr = &bravo;
	std::cout << "\nbravo is " << bravo << ".\n";
	std::cout << "\nci_ptr is " << ptr << ".\n";
	std::cout << "\nThe value at ci_ptr is " << *ptr << ".\n";

	int* const ic_ptr = &alpha;
	std::cout << "\nalpha is " << alpha << ".\n";
	std::cout << "\nci_ptr is " << ic_ptr << ".\n";
	std::cout << "\nThe value at ci_ptr is " << *ic_ptr << ".\n";

	*ic_ptr = 77;
	std::cout << "\nalpha is " << alpha << ".\n";
	std::cout << "\nci_ptr is " << ic_ptr << ".\n";
	std::cout << "\nThe value at ci_ptr is " << *ic_ptr << ".\n";

	std::cout << "\nFinal alpha is " << alpha << ".\n";
	std::cout << "\nFinal bravo is " << bravo << ".\n";

	int* const test_ptr = nullptr;

	/* Bonus ans.
	* What's the difference between a null pointer and a dangling pointer?  null - A declared pointer that doesnt point to anything (I think equivalent to int 0, str "", array [],
	the nullptr is just dying to be assigned something (not dangerous if not used) vs dangling - a pointer whose pointee has been destroyed (dangerous)

	Does const int* ptr prevent modification of the original variable through other means? --> Yes, by locking the ptr to the var with const ptr.

	Why might int* const ptr be useful?  --> Because it still allow modification of the original variable.

	Can you initialize an int* const without assigning it an address?   --> Yes, nullptr, just like any other pointer.  Assignment does make it different, modify/redir rules make it different.
	*/
}
//################# END E3.14.4 #################






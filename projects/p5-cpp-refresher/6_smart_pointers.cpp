
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

//################# E3.15.1 C++ Dynamic Memory: new and delete #################
/*
int* ptr = new int(42);

std::cout << *ptr;  // 42

delete ptr;
ptr = nullptr;

Operation		Purpose
==================================================
new int(42)		Allocate and initialize an integer
delete ptr		Release the allocated integer
nullptr			Represent no pointed-to object
new int[5]		Allocate an array of five integers
delete[] ptr	Release a dynamically allocated array

Swerios answer to a great pointer joke: How do you prevent a leak?  With a finger!
or the serious answer:
HARD RULE: EVERY new MUST be undone by a delete.
delete ptr;       // Release memory
ptr = nullptr;    // Prevent accidental reuse
#include <memory>

auto ptr = std::make_unique<int>(42);
// No manual delete needed!
nullptr prevents accidental reuse; delete prevents the leak. Smart pointers help automate cleanup.
*/

//void pointerPrint(int* ptr, int size) {
//
//	for (int i = 0; i < size; i++) {
//		std::cout << "Array element " << (i + 1) << " is " << *(ptr + i) << ".\n";
//	}
//	std::cout << "\n";
//}
//
//int pointerAdd(int* ptr, int size) {
//	int sum = 0;
//	for (int i = 0; i < size; i++) {
//		sum += *(ptr + i);
//	}
//	return sum;
//}
//
//void pointerAssign(int* ptr, int size) {
//	for (int i = 0; i < size; i++) {
//		*(ptr + i) = (i + 1) * 10;
//	}
//	pointerPrint(ptr, 5);
//}
//
//int main() {
//	//Part A
//
//	std::cout << "Welcome to E3.15.1 \n\n";
//
//	int* ptr = new int(25);
//	std::cout << "ptr is at memory location: " << ptr << ".\n";
//	std::cout << "The value at ptr is: " << *ptr << ".\n";
//
//	*ptr = 75;
//	std::cout << "ptr is at memory location: " << ptr << ".\n";
//	std::cout << "The updated value at ptr is: " << *ptr << ".\n";
//
//	delete ptr;
//	ptr = nullptr;
//
//	std::cout << "Do we have a null pointer? " << (ptr == nullptr) << ".\n\n";
//
//	//Part B
//	int* a_ptr = new int[5];
//
//	pointerAssign(a_ptr, 5);
//	std::cout << "The integer array elements sum to: " << pointerAdd(a_ptr, 5) << ".\n";
//
//	delete[] a_ptr;
//
//	a_ptr = nullptr;
//	std::cout << "Do we have another null pointer? " << (a_ptr == nullptr) << ".\n\n";
//
//	//This block...is for learning
//	int* test_ptr = new int(66);
//	test_ptr = nullptr;
//	std::cout << "Do we have null test pointer? " << (test_ptr == nullptr) << ".\n\n";
//
//	/*
//	What's the difference between stack and heap memory?  ---> The stack is storage for function operations, the heap is storage for dynamic memory allocation.
//
//	Why must new[] be paired with delete[]?  --> Because anything declared with new requires manual management and if it is allocated, it must ultimately be released when no longer needed.
//	the matching forms matter because arrays may contain multiple objects requiring destruction.
//
//	What is a memory leak?  allocated memory with no pointer assigned to it, so wasted space? Allocated memory that becomes unreachable without being released.
//
//	Why should we avoid dereferencing a pointer after delete?  --> be cause there is nothing to dereference. No target.
//
//	Does assigning nullptr automatically release allocated memory?  According to me test_ptr, No.  Does the language or the IDE enforce this? 	Also, multiple pointers can point to the same resource so that would be bad anayway.
//	
//	*/
//}
//################# END E3.15.1 #################


//################# E3.15.2 C++ Smart Pointers: std::unique_ptr #################
/*
#include <memory>

auto ptr = std::make_unique<int>(42);
std::unique_ptr<int> e_ptr = nullptr; /// null init

std::cout << *ptr;  // 42

Operation					Purpose
=================================================================================
std::make_unique<int>(42)	Create an owned integer
*ptr						Access the integer
ptr.get()					Obtain its raw address without transferring ownership
ptr.reset()					Release the owned object
std::move(ptr)				Transfer ownership to another smart pointer
ptr == nullptr				Check whether ownership is empty

Important: std::unique_ptr cannot be copied. Ownership is exclusive.
Safety rule: Never manually delete an object owned by a unique_ptr.
*/

//int main() {
//	//Part A
//
//	std::cout << "Welcome to E3.15.2 \n\n";
//
//	auto ptr = std::make_unique<int>(25);
//	std::cout << "smart ptr is at memory location: " << ptr << ".\n";
//	std::cout << "The value at smart ptr is: " << *ptr << ".\n";
//
//	*ptr = 75;
//	std::cout << "smart ptr is at memory location: " << ptr << ".\n";
//	std::cout << "The updated value at smart ptr is: " << *ptr << ".\n";
//
//	ptr.reset();
//	std::cout << "Do we have a null pointer? " << (ptr == nullptr) << ".\n\n";
//
//	////Part B
//	auto u_ptr = std::make_unique<int>(75);
//	std::cout << "u_ptr is at memory location: " << u_ptr << ".\n";
//	std::cout << "The value at u_ptr is: " << *u_ptr << ".\n";
//
//	std::unique_ptr<int> e_ptr = nullptr;
//	std::cout << "Do we have a null e_ptr? " << (e_ptr == nullptr) << ".\n\n";
//
//	e_ptr = std::move(u_ptr);
//	std::cout << "e_ptr is at memory location: " << e_ptr << ".\n";
//	std::cout << "The value at e_ptr is: " << *e_ptr << ".\n";
//
//	std::cout << "Do we have a null u_ptr? " << (u_ptr == nullptr) << ".\n\n";
//
//	*e_ptr = 200;
//	std::cout << "The value at e_ptr is now: " << *e_ptr << ".\n";
//
//	/*  BONUS ??
//	Why can't two unique_ptr objects own the same allocation?  --> Because of the bitter: it is forbidden, but there is a sill a sweet side: allocation ownership can be "transferred".
//
//	Does std::move() physically move the integer to another memory address?  --> no, it's transfers ownership to another smart pointer.
//
//	What happens when a unique_ptr goes out of scope?  --> "automatically releases the target object when the smart pointer is destroyed (out of scope)"
//
//	How does reset() differ from assigning nullptr to a raw pointer?  Reset prepares a smart pointer for transfer, buy releasing it from it's bond  and setting the smart pointer to null. 
//
//	unique_ptr::reset() releases ownership and destroys the currently owned object.
//	Assigning nullptr to a raw pointer only changes the pointer, potentially leaking its allocation.
//	*/
//}
//################# END E3.15.2 #################

//################# E3.15.3 C++ Smart Pointers: std::unique_ptr #################
/*
#include <memory>

auto alpha = std::make_shared<int>(42);
auto bravo = alpha;

std::cout << *alpha;           // 42
std::cout << *bravo;           // 42
std::cout << alpha.use_count(); // 2

Unlike unique_ptr, a shared_ptr permits multiple owners.

Reference counting: The managed object is destroyed when its final owning shared_ptr releases ownership.

Safety rule: Never construct separate owning shared_ptr objects independently from the same raw pointer.

Operation					Purpose
===========================================================
std::make_shared<int>(42)	Create a shared integer
auto bravo = alpha			Share ownership
.use_count()				Report current owner count
.reset()					Release one pointer's ownership
*ptr						Access the shared object
ptr == nullptr				Check whether pointer is empty

*/
//
//int main() {
//	//Part A
//	std::cout << "Welcome to E3.15.3 \n\n";
//
//	auto alpha = std::make_shared<int>(100);
//	std::cout << "alpha's target is at memory location: " << alpha << ".\n";
//	std::cout << "The value at alpha is: " << *alpha << ".\n";
//
//	auto bravo = alpha;
//	std::cout << "bravo's target is at memory location: " << bravo << ".\n";
//	std::cout << "The value at bravo is: " << *bravo << ".\n";
//
//	std::cout << "alpha's use_count is: " << alpha.use_count() << ".\n";
//	std::cout << "bravo's use_count is: " << bravo.use_count() << ".\n";
//
//	*bravo = 200;
//	std::cout << "The value at alpha is: " << *alpha << ".\n";
//	std::cout << "The value at bravo is: " << *bravo << ".\n";
//
//	//Part B
//	alpha.reset();
//	std::cout << "Is alpha a null pointer? " << (alpha == nullptr) << ".\n\n";
//	std::cout << "bravo's use_count is: " << bravo.use_count() << ".\n";
//	std::cout << "The value at bravo is: " << *bravo << ".\n";
//
//	bravo.reset();
//	std::cout << "Is bravo a null pointer too? " << (bravo == nullptr) << ".\n\n";
//
//	/*  BONUS ??
//	Why does resetting alpha not destroy the integer while bravo still owns it?  ---> Because reset only releases the calling owner?
//
//	What's the primary ownership difference between unique_ptr and shared_ptr?  owner counts ---> unique == one and only one, shared == one or more 
//
//	Does copying a shared_ptr copy the managed integer? --->  No, just the reference to it.
//
//	What might happen if two objects hold shared_ptr references to each other?  --->  "The managed object is destroyed when its final owning shared_ptr releases ownership."  might a reset() of one cause an inadvertent destruction of the managed resource of the other?
//	Circular ownership: Needs one conceptual correction.
//
//	If object A owns B through a shared_ptr, and B owns A through another shared_ptr, they can keep each other's reference counts above zero indefinitely.
//	Result: a memory leak, even after external owners disappear.
//	That's called a reference cycle.  <--- weak_ptr addresses this situation.
//	*/
//}
//################# END E3.15.3 #################


//################# E3.15.4 C++ Shared & Weak Pointers #################
/*
#include <memory>

auto owner1 = std::make_shared<int>(42);
auto owner2 = owner1;

std::weak_ptr<int> observer = owner1;

Operation					Purpose
===========================================================
std::make_shared<int>(42)	Create a shared allocation
owner1.use_count()			Count shared owners
owner2 = owner1				Share ownership
std::weak_ptr<int>			Observe without owning
observer.lock()				Attempt to obtain a temporary shared owner
observer.expired()			Check whether the object has been destroyed
owner1.reset()				Release one owner's claim

Safety rule: Never dereference an empty smart pointer. Check the result of lock() before accessing its object.

*/

int main() {
	//Part A
	std::cout << "Welcome to E3.15.4 or E3.15.whatever because I lost track of module labeling while running for my life. 😅😆\n\n";

	auto owner1 = std::make_shared<int>(100);
	std::cout << "owner1's target is at memory location: " << owner1 << ".\n";
	std::cout << "The value at owner1 is: " << *owner1 << ".\n";
	std::cout << "owner1's use_count is: " << owner1.use_count() << ".\n";

	auto owner2 = owner1;
	std::cout << "owner1's use_count is: " << owner1.use_count() << ".\n";
	std::cout << "owner2's use_count is: " << owner2.use_count() << ".\n";

	*owner2 = 200;
	std::cout << "The value at owner1 is: " << *owner1 << ".\n";
	owner1.reset();
	std::cout << "Is owner1 a null pointer? " << (owner1 == nullptr) << ".\n\n";
	std::cout << "The value at owner2 is: " << *owner2 << ".\n";


	//Part B
	std::weak_ptr<int> observer = owner2;
	std::cout << "Is observer expired? " << observer.expired() << ".\n\n";
	auto temp = observer.lock();
	std::cout << "The value at temp is: " << *temp << ".\n";

	temp.reset();
	std::cout << "Is temp now a null pointer? " << (temp == nullptr) << ".\n\n";
	owner2.reset();
	std::cout << "Is owner2 now a null pointer? " << (owner2 == nullptr) << ".\n\n";

	auto another_temp = observer.lock();
	std::cout << "Is another_temp now a null pointer? " << (another_temp == nullptr) << ".\n\n";

	/*  BONUS ??
	* Why doesn't copying a shared_ptr duplicate the underlying integer?  ---> becaue we copying reference "to" the item, not the item itself.  3rd grade I know, best I can do before you bring your sharpening stone.
	*
	Why doesn't a weak_ptr increase the ownership count?  ---> Because (by design) it does NOT contribute to the reference count.  It's a non-owning observer only.

	What happens if two objects own each other through shared_ptr members?  ---> a reference circle.  Weak pointers dont contribute to reference counts and therefore ensure auto release happens
	One clarification: two objects owning each other through shared_ptr can remain allocated indefinitely because their ownership counts never reach zero

	How can weak_ptr help solve that problem?  ---> By releasing the resource when it is out of scope
	A weak_ptr doesn't itself release the resource; it allows the final shared owner to release it.

	When would you prefer unique_ptr over shared_ptr?  ---> When you want to ensure only a single owner can change a target value.  Great way to avoid race conditions I'd say. The problem of too many hands applies heer too.
	unique_ptr guarantees one owner, not that only one part of a program can modify the object. It also doesn't automatically guarantee thread safety.
	*/
}
//################# END E3.15.4 #################






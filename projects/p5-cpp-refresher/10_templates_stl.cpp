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
#include <type_traits>
#include <cctype>
#include <numeric>

//################# E3.19.1 C++ Templates & STL #################
/* Notes
Templates let you write one function that works with multiple data types, without duplicating code.

The non-templated approach
====================================
int maximum(int a, int b) {
    return (a > b) ? a : b;
}

double maximum(double a, double b) {
    return (a > b) ? a : b;
}

The templated approach
=====================================
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

maximum(10, 20);       // int
maximum(3.5, 7.2);     // double
maximum('A', 'Z');     // char

<-- The operations inside the template must be valid for the type supplied. Our maximum() requires the > comparison to work.
Concept						Purpose
==============================================================================
template					Declares a template
typename T					Introduces a type parameter
T							Placeholder for a type
Template instantiation		Compiler generates a type-specific implementation
Type deduction				Compiler infers T from arguments

Templates = Generic programming. Write code once, reuse it with different data types.
Type safety = Big payoff. Templates preserve type checking at compile time.
STL containers = Storage. vector, array, list, map, etc.
Iterators = Navigation. Provide a common way to traverse containers.
Algorithms = Operations. sort(), find(), count(), etc.

The STL provides the machinery for all three to work together:
Container (stores) → Iterator (accesses) → Algorithm (processes)
*/
//Part A
//template<typename T>
//T findMax(T a, T b) {
//    return (a > b) ? a : b;
//}
//
////Part B
//template<typename T> // each template has to have it's own identifier declaration and it can be any non-keyword string or valid single character.
//
////By reference version
//void swapValues(T& a, T& b) {
//    T temp = a;
//    a = b;
//    b = temp;
//}//end of template
//
////By value version
//// void swapValues(T* a, T* b) {
////    T temp = *a;
////    *a = *b;
////    *b = temp;
////}//end of template
//
////Helper Templates - the return does NOT have to match the input type
//template<typename T>
//void printPartAResults(T a) {
//    std::cout << findMax(a[0], a[1]) << " is the larger value.\n";
//}//end of template
//
//template<typename T>
//void printPartBResults(T a) {
//    std::cout << "We see " << a[0] << a[1] << "\n";
//    //std::cout << "Element 1 is: " << a[0] << "   Element 2 is: " << a[1] << ".\n";
//}//end of template
//
////I felt a need to exercise structs to see how useful they can be
//struct Testing {
//    std::vector<int> i_values = { 33, 88 };
//    std::vector<double> d_values = { 86.7531, 67.5 };
//    std::vector<char> c_values = { 'M', 'c' };
//    std::vector<std::string> s_values = { " world!", "hello"};
//};//end of struct
//
//
//int main() {
//	std::cout << "Welcome to E3.19.1 \n\n";
//
//    Testing testValues;
//    printPartAResults(testValues.i_values);
//    printPartAResults(testValues.d_values);
//    printPartAResults(testValues.c_values);
//
//    std::cout << "\nBefore the swap:\n";
//    printPartBResults(testValues.i_values);
//    printPartBResults(testValues.s_values);
//
//    //By reference version
//    swapValues(testValues.i_values[0], testValues.i_values[1]);
//    swapValues(testValues.s_values[0], testValues.s_values[1]);
//    
//    //By value version
//    //swapValues(&testValues.i_values[0], &testValues.i_values[1]);
//    //swapValues(&testValues.s_values[0], &testValues.s_values[1]);
//
//    std::cout << "\nAfter the swap:\n";
//    printPartBResults(testValues.i_values);
//    printPartBResults(testValues.s_values);
//}//end of main

/*  Bonus Q
*
Does a function template generate every possible type implementation immediately?
--> I dont think so, I believe it just infers from the inputs and the should probably match if they share the same identifier (T or U or X,Y, or Z)

Why does findMax(10, 3.5) present a type-deduction problem?
--> Because the T corresponds to a single type (even if that type is arbitrary).

Can a template work with user-defined classes or structs?
--> I believe I just unknowingly exercise this exact question.  Given the mixed bag of test value types, I used the struct to 1: get some practice with it and 2: make my code neater.
--> Seems like inside of a function, templated or regular, anything goes, external interplay, however, needs to follow some basic typing rules.

What's the primary advantage of templates compared with writing many overloaded functions?
--> Flexibility bro.  No contest.  The template can ease (non-Pythonic) C++ pain substantially in certain situations.

Is T a special C++ keyword, or can you choose another name?
--> I thought so until I started the WH machine next door and Wow dude, pretty much limitless.  Any valid non-keyword string or single character.
*/
//################# END E3.19.1 #################

//################# E3.19.2 C++ Class Templates: Generic Objects #################
/* Notes
* Class templates work with entire classes, allowing one class definition to handle different data types
*
* template <typename T>
class Storage {
private:
    T value;

public:
    Storage(T v) : value(v) {}

    T getValue() const {
        return value;
    }

    void setValue(T v) {
        value = v;
    }
};

Storage<int> integerBox(42);
Storage<std::string> stringBox("Radar");

std::cout << integerBox.getValue(); // 42
std::cout << stringBox.getValue();  // Radar

Concept					Meaning
==============================================================
template <typename T>	Introduces a type parameter
Storage<T>				Generic class definition
Storage<int>			Class specialization using int
Storage<std::string>	Class specialization using std::string
T value					Member whose type depends on T
*/

////Part A
//template <typename T>
//class RadarStorage {
//private:
//    T value;
//
//public:
//    RadarStorage(T v): value(v) {}//end of constructor
//
//    //Getter and Setter
//    T getValue() const { return value; }
//
//    void setValue(T v) { value = v;  }
//
//    //Helper
//    void printValue(std::string v_type) {
//        std::cout << "The " << v_type  << " value is: " << value << ".\n";
//    }
//};//end of template class RadarStorage
//
//
////The beauty of resuable code!
//template <typename T, typename U>
//class RadarPair {
//private:
//    T first;
//    U second;
//
//public:
//    RadarPair(T f, U s): first(f), second(s) {}//end of constructor
//
//    //Getters and Setters
//    T getFirst() const { return first; }
//    T getSecond() const { return second; }
//
//    void setFirst(T f) { first = f; }
//    void setSecond(U s) { second = s; }
//
//    //Helper
//    void printValues(std::string t_type, std::string u_type) {
//        std::cout << "The first value is " << t_type << ": " << first << ".\n";
//        std::cout << "The second value is " << u_type << ": " << second << ".\n";
//    }
//};//end of template class RadarPair
//
//
//int main() {
//    std::cout << "Welcome to E3.19.2 \n\n";
//
//    //Part B
//    RadarStorage<int> integerBox(100);
//    RadarStorage<double> doubleBox(250.5);
//    RadarStorage<std::string> stringBox("Radar");
//
//    std::cout << "Initial Values: \n";
//    integerBox.printValue("integer");
//    doubleBox.printValue("double");
//    stringBox.printValue("string");
//
//    integerBox.setValue(200);
//    doubleBox.setValue(600.5);
//    stringBox.setValue("Sonar");
//
//    std::cout << "\nUpdated Values: \n";
//    integerBox.printValue("integer");
//    doubleBox.printValue("double");
//    stringBox.printValue("string");
//
//    //Part C
//    RadarPair<int, std::string> pairBox(101, "Aircraft");
//    std::cout << "\nInitial Paired Values: \n";
//    pairBox.printValues("integer", "string");
//
//
//    //Part D?
//    std::cout << "\nUpdated Paired Values: \n";
//    pairBox.setFirst(202);
//    pairBox.setSecond("Ship");
//    pairBox.printValues("integer", "string");
//
//    std::cout << "\nFor fun: \n";
//    RadarPair<std::string, std::string> funPair("Hello", "World!");
//    funPair.printValues("string", "string");
//
//}//end of main

/*  Bonus Q
*
Does RadarStorage<int> share its stored value with RadarStorage<double>?
-->  I don't think so.  Should still be 1 memloc / value

Can two objects of RadarStorage<int> hold different values?
--> Yes, different objects implies different identifiers.

Why might a class template be preferable to maintaining separate classes for integers, doubles, and strings?
--> Reducing the bloat bro.  66% less function declaration space required for a templated function in this case.
--> Less to maintain, less to debug
--> It's like another form of abstraction; internal abstraction.

Can a class template contain ordinary non-template member functions?
--> Yes, I believe my helpers printerValue(s) demonstrates that.

Does RadarPair<T, U> require T and U to represent different types?
--> Not at all, demonstrated with my Hello World test.

*/
//################# END E3.19.2 #################

//################# E3.19.3 C++ STL Algorithms & Iterators #################
/* Notes
* STL - standard C++ algorithms that replace the need to manually implement common operations.
*
* Component	Responsibility
==========================
Containers	Store data
Iterators	Navigate data
Algorithms	Process data

#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> numbers = {30, 10, 50, 20, 40};

std::sort(numbers.begin(), numbers.end());

Algorithm			Purpose
=================================================
std::sort()			Sort elements --> call with (numbers.begin(), numbers.end()); add std::greater<int>() for descending order
std::reverse()		Reverse element order
std::find()			Locate first matching element
std::count()		Count matching elements
std::min_element()	Locate minimum element
std::max_element()	Locate maximum element
std::accumulate()	Accumulate values
std::find_if()		Find using a condition
std::count_if()		Count using a condition

LAMBDA LAMBDA LAMBDA! - a small function supplied directly to an algorithm.

Lambda component	Purpose
==================================
[]					Capture list
(int n)				Parameter list
{ ... }				Function body

auto isEven = [](int n) { return n % 2 == 0; };
std::count_if(numbers.begin(), numbers.end(), isEven);

Function behavior			Parameter convention
===================================================
Read-only, large object		const T&
Modify original				T&
Small value (int, double)	T
Read-only iterator			Pass iterator by value

*/

//helpers
template<typename T>
void printIterable(const std::vector<T>& container) {
    int i = 1;

    for (const T& element : container) {
        std::cout << "Element " << i << " is: " << element << "\n";  //IDE complains but unjustified!
        i++;
    }
    std::cout << "\n";
}//end of printIterable()

template<typename V>
void printElement(V iter) {
    std::cout << "The target element is " << *iter << "\n";
}//end of printElement()

template<typename T, typename V>
void findElementIndex(T& container, const V iter) {
    std::cout << "The first occurence of the element is at index " << std::distance(container.begin(), iter) << "\n";
}//end of printElement()

template<typename T, typename V>
void getElementCount(const T& container, V target) {
    std::cout << "There are " << std::count(container.begin(), container.end(), target) << " occurences of " << target << " in the container\n";
}//end of printElement()

template<typename T>
void getMinOrMax(const T& container, const std::string label) {
    if (container.empty()) { std::cout << "Empty Container.\n";return; }

    if (label == "min") {
        auto iter = std::min_element(container.begin(), container.end());
        std::cout << "The minimum value in this container is " << *iter << "\n";
    }

    if (label == "max") {
        auto iter = std::max_element(container.begin(), container.end());
        std::cout << "The maximum value in this container is " << *iter << "\n";
    }
}//end of getMinOrMax()

template<typename T>
T sumIt(const std::vector<T>& container) {
    return std::accumulate(container.begin(), container.end(), 0);
}//end of sumIt()



int main() {
    std::cout << "Welcome to E3.19.3 \n\n";

    //Part A
    std::vector<int> numbers = { 50, 20, 80, 20, 10, 90, 40 };
    printIterable(numbers);
    std::sort(numbers.begin(), numbers.end());
    printIterable(numbers);
    std::reverse(numbers.begin(), numbers.end());
    printIterable(numbers);
    auto iter = std::find(numbers.begin(), numbers.end(), 20);
    if (iter != numbers.end()) {
        printElement(iter);
        findElementIndex(numbers, iter);
    }
    getElementCount(numbers, 20);

    //Part B
    getMinOrMax(numbers, "min");
    getMinOrMax(numbers, "max");

    std::cout << "The vector elements sum to " << sumIt(numbers) << "\n";
    std::cout << "The mean of the vector elements is " << static_cast<float>(sumIt(numbers)) / numbers.size() << "\n";

    //Part C
    auto greaterThan = [](int n) { return n > 40; };
    std::cout << "There are " << std::count_if(numbers.begin(), numbers.end(), greaterThan) << " occurences of values > 40 in the container\n";

    auto l_iter = std::find_if(numbers.begin(), numbers.end(), greaterThan);
    if (l_iter != numbers.end()) {
        std::cout << "The first qualifying element > 40 is " << *l_iter << " and it is at index " << std::distance(numbers.begin(), l_iter) << "\n";
    }

}//end of main

/*  Bonus Q
*
Why do STL algorithms generally accept iterators instead of entire containers?
--> Yes, um both actually.  I learned something along the way: const containter input requires something special but non-const container paired with const or nonconst iter is okay.

Why must you check the result of std::find() against .end() before dereferencing?
--> probably to ensure the element needle isnt at last elem + 1. Avoiding the boundary marker. I suppose it is an .empty() alternative.

Does std::sort() modify the original container?
--> I have no idea how THIS sort works under the hood, but the bro next door says sort in place so that's nice.  Probably has atleast 1 temp I imagine.

What advantage does a lambda provide when using std::count_if()?
--> straight in bro.  I love that.  lambda provides direct responses to questions the algorithm may ask (that the lambda can answer).

Why might using standard algorithms be preferable to writing your own loops?
--> Bro!  Saves time.  Why would I want to hand jam a sorting algorithm when I can just use the library.  Still had to do it in undergrad though, for instructional purposes of course.
*/
//################# END E3.19.3 #################
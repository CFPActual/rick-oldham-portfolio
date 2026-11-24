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

//################# E3.1 C++ Control Flow #################
//std::string classify_temp(int temp) {
//	if (temp < 32) { return "Freezing";}
//	if (temp >= 32 && temp <= 59) { return "Cold";}
//	if (temp >= 60 && temp <= 79) { return "Comfortable";}
//	if (temp >= 80) { return "Hot";}
//}
//
//int main(){
//	std::cout << "Welcome to E3.1 \n";
//
//	int temperature = 75;
//	std::cout << "Current temperature is " << temperature << " degrees.\n";
//
//	int sample_temps[6] = {31, 32, 59, 60, 79, 80};
//
//	for (int i = 0; i < std::size(sample_temps); i++) {
//		std::cout << sample_temps[i] << " degrees Fahrenheit is considered " << classify_temp(sample_temps[i]) << ".\n";
//	}
//}
//################# END E3.1 #################

//################# E3.2 C++ Switch Statement #################
//void switch_it(int temp) {
//	switch (temp) {
//	case 1: std::cout << "System Start\n"; break;
//	case 2: std::cout << "System Status\n"; break;
//	case 3: std::cout << "System Shutdown\n"; break;
//	default: std::cout << "Nothing to see here.\n"; 	
//	}
//}
//
//void switch_it_mod_1(int temp) {
//	switch (temp) {
//	case 1: std::cout << "System Start\n"; break;
//	case 2: std::cout << "System Status\n"; break;
//	case 3: std::cout << "System Shutdown\n"; break;
//	default: std::cout << "Nothing to see here.\n";
//	}
//}
//
//int main() {
//	std::cout << "Welcome to E3.2 \n";
//	switch_it(1);
//	switch_it(2);
//	switch_it(3);
//	switch_it(99);
//
//	std::cout << "\nPart 2 \n\n";
//
//	switch_it_mod_1(1);
//	switch_it_mod_1(2);
//	switch_it_mod_1(3);
//	switch_it_mod_1(99);
//}
//################# END E3.2 #################

//################# E3.3 C++ for loops #################
/*
//################ E3.3 C++ Range-Based for Loops ################
/*
Introduced: C++11
Purpose: Visit every element without manual indexing.

SYNTAX:
for (element : iterable) { ... }

EXAMPLES:
int arr[3] = {10, 20, 30};

for (int value : arr)        // Copy element
for (int& value : arr)       // Modify original
for (const int& value : arr) // Read-only reference
for (auto value : arr)       // Deduce element type

ELIGIBLE:
Raw arrays, std::array, std::vector, std::string,
std::list, std::set, std::map, iterable custom types.

NOT DIRECTLY ELIGIBLE:
int* pointer;  // No range length information

BUSINESS RULES:
1. Prefer range-based for when visiting all elements.
2. Use indexed for when element positions matter.  or --> C++23 std::views::enumerate
3. By-value copies; by-reference accesses originals.
4. const reference prevents modification through it.
5. Iterable must support begin/end traversal.
6. Range-based for does not expose an index automatically.

*/
//################ END E3.3 ################
*/
//################# END E3.3 #################

//################# E3.4 C++ while and do-while #################

//int main() {
//	std::cout << "Welcome to E3.4 \n";
//
//	int counter = 5;
//
//	std::cout << "The while loop says: \n";
//
//	while (counter < 5) {
//		std::cout << "" << counter << ".\n";
//		counter++;
//	}
//
//	std::cout << "\nThe do-while loop says: \n";
//
//	do {
//		std::cout << "" << counter << ".\n";
//		counter++;
//	} while (counter < 5); // <-- while must end with a semi!!
//
//	std::cout << "" << counter << ".\n";
//}
//################# END E3.4 #################


//################# E3.5 C++ break and continue #################
//int main() {
//	std::cout << "Welcome to E3.5 \n";
//
//	int numbers[8] = {3, 7, 12, 5, 18, 9, 24, 6 };
//
//	std::cout << "\nLOOP A \n\n";
//	for (int i = 0; i < std::size(numbers); i++) {
//		int mod = numbers[i] % 2;
//		switch (mod) {
//		case 0: continue;
//		case 1: std::cout << numbers[i] << " is rather odd dont you think?\n"; break;
//		default: std::cout << "Something is horribly wrong.";
//		}
//	}
//
//	std::cout << "\nLOOP B \n\n";
//	for (int i = 0; i < std::size(numbers); i++) {
//		if (numbers[i] <= 15) {std::cout << numbers[i] << " is less than 15.\n";
//		}
//		else {break;}
//	}
//}
//################# END E3.5 #################

//################# E3.6 C++ nested loops #################

//int main() {
//	std::cout << "Welcome to E3.6 \n";
//
//	std::cout << "  col 1      col 2      col 3\n";
//	std::cout << "_________________________________\n";
//
//	for (int i = 1; i < 5; i++) {
//		std::cout << "\n";
//		for (int j = 1; j < 4; j++) {
//			std::cout << i << " * " << j << " = " << i * j << "   ";
//		}
//	}
//	std::cout << "\n\n";
//}
//################# END E3.6 #################

//################# E3.7 C++range-based for loops #################
//
//int main() {
//	std::cout << "Welcome to E3.7 \n";
//
//	int numbers[6] = { 4, 8, 12, 16, 20, 24 };
//
//	std::cout << "\nPart 1 \n\n";
//	for (int value : numbers) {
//		std::cout << value << '\n';
//	}
//
//	std::cout << "\nPart 2 \n\n";
//	int total = 0;
//	for (int value : numbers) {
//		total += value;
//	}
//	std::cout << "The sum of numbers is " << total  <<".\n";
//
//
//	std::cout << "\nPart 3 \n\n";
//	int count_greater_than_10 = 0;
//	for (int value : numbers) {
//		if (value > 10) { count_greater_than_10++; }
//	}
//	std::cout << "The count of values greater than 10 is " << count_greater_than_10 << ".\n";
//}//END main()
//################# END E3.7 #################

//################# E3.8 C++ Intro to Functions pass by value and by reference #################
//
//int add_value(int x) { return x += 10;}
//
//int add_reference(int& x) { return x += 10;}
//
////int add_const(const int& x) { return x += 10; }
//
//int main() {
//	std::cout << "Welcome to E3.8 \n";
//
//	int a = 20;
//
//	std::cout << "a is " << a << ".\n";
//	int a_val = add_value(a);
//	std::cout << "a_val is " << a_val << ".\n";
//	std::cout << "a is " << a << ".\n\n";
//
//	a = 20;
//	std::cout << "a is " << a << ".\n";
//	int a_ref = add_reference(a);
//	std::cout << "a_ref is " << a_ref << ".\n";
//	std::cout << "a is " << a << ".\n\n";

	//a = 20;
	//std::cout << "a is " << a << ".\n";
	//int a_const = add_const(a);
	//std::cout << "a_const is " << a_const << ".\n";
	//std::cout << "a is " << a << ".\n\n";	
//}//END main()
//################# END E3.8 #################


//################# E3.9 C++ Function Overloading #################
//
//int calculate(int a, int b, double e) { return e * (a + b); }
//
//int calculate(double f, int y, int z) { return (y + z) * f; }
//
//
////double calculate(int a, int b) { return static_cast<double>(a * b); }
//double calculate(double a, double b) { return a * b; }
//int calculate(int a, int b, int c) { return a + b + c; }
//
//
//int main() {
//	std::cout << "Welcome to E3.9 \n";
//
//	int a = 5;
//	int b = 10;
//	int c = 20;
//
//	double d = 1.33;
//	double e = 5.7;
//
//	std::cout << "a is " << a << ".\n";
//	std::cout << "b is " << b << ".\n";
//	std::cout << "c is " << c << ".\n";
//	std::cout << "d is " << d << ".\n";
//	std::cout << "e is " << e << ".\n\n";
//
//	//std::cout << "ans for calculate() version 1 is " << calculate(a, b) << ".\n";
//	//std::cout << "ans for calculate() version 2 is " << calculate(d, e) << ".\n";
//
//	std::cout << "ans for calculate() version 4 is " << calculate(e, b, c) << ".\n\n";
//	std::cout << "ans for calculate() version 5 is " << calculate(b, c, e) << ".\n\n";
//
//}//END main()
//################# END E3.9 #################

//################# E3.10 C++ Default Function Parameters #################
//
//int calculate(int param1, int param2 = 10, int param3 = 5) { return (param1 + param2 + param3); }
//
//int main() {
//	std::cout << "Welcome to E3.10 \n";
//
//	int a = 5;
//	int b = 30;
//	int c = 40;
//
//	std::cout << "a is " << a << ".\n";
//	std::cout << "b is " << b << ".\n";
//	std::cout << "c is " << c << ".\n";
//
//
//	std::cout << "ans for calculate() version 1 is " << calculate(a) << ".\n";
//	std::cout << "ans for calculate() version 2 is " << calculate(a, b) << ".\n";
//	std::cout << "ans for calculate() version 3 is " << calculate(a, b, c) << ".\n";
//	std::cout << "ans for calculate() version 4 is " << calculate(a, c) << ".\n";
//	
//	std::cout << "\nBonus: What happens if you try to provide a and c, but omit b?\n\n"; 
//	std::cout << "Passed-in parameters are distributed across the function signature sequentially so...\n";
//	std::cout << "...a goes to param1 (manadatory), c goes to param2 (the next receiver), \n";
//	std::cout << "and param3 uses the default value since there is no third parameter in the call.\n";
//
//}//END main()
//################# END E3.10 #################


//################# E3.11 C++ Recursion #################
//int factorial(int n) { 
//	if (n <= 1) { return 1;}  
//
//	return n * factorial(n - 1);
//}
//
//int main() {
//	std::cout << "Welcome to E3.11 \n";
//
//	int a = 3;
//	int b = 5;
//	int c = 7;
//
//	std::cout << "a is " << a << ".\n";
//	std::cout << "b is " << b << ".\n";
//	std::cout << "c is " << c << ".\n\n";
//
//	std::cout << a << "! =  " << factorial(a) << ".\n";
//	std::cout << b << "! =  " << factorial(b) << ".\n";
//	std::cout << c << "! =  " << factorial(c) << ".\n";
//
//}//END main()
//################# END E3.11 #################

//################# E3.11.3 C++ Recursion #################
//int sum(int n) {
//	if (n <= 1) { return 1; }
//
//	return n + sum(n - 1);
//}
//
//int main() {
//	std::cout << "Welcome to E3.11.3 \n";
//
//	int a = 4;
//	int b = 6;
//	int c = 8;
//
//	std::cout << "a is " << a << ".\n";
//	std::cout << "b is " << b << ".\n";
//	std::cout << "c is " << c << ".\n\n";
//
//	int test_val = a;
//	std::cout << "sum(" << test_val << ") =  " << sum(test_val) << ".\n";
//}//END main()
//################# END E3.11.3 #################

//################# E3.11.4 C++ Recursion #################
//int power(int base, int expo) {
//	if (expo == 0) { return 1; }
//	//if (expo == 1) { return base; }
//
//	return base * power(base, expo - 1);
//}
//
//int main() {
//	std::cout << "Welcome to E3.11.4 \n";
//
//	int a[2] = {3,3};
//	std::cout << a[0] << "^" << a[1] << " = " << power(a[0], a[1]) << ".\n";
//
//	int b[2] = {3,4};
//	std::cout << b[0] << "^" << b[1] << " = " << power(b[0], b[1]) << ".\n";
//
//	int c[2] = {5,0};
//	std::cout << c[0] << "^" << c[1] << " = " << power(c[0], c[1]) << ".\n";
//
//	int d[2] = {7,2};
//	std::cout << d[0] << "^" << d[1] << " = " << power(d[0], d[1]) << ".\n";
//
//}//END main()

//################# END E3.11.4 #################

//################# E3.11.5 C++ Recursion #################
//int digitSum(int n) {
//	if (n == 0) { return 0; }
//
//	return  (n % 10) + digitSum((n - (n % 10)) / 10) ;
//}

//int digitSum(int n) {
//	if (n == 0) { return 0; }
//
//	return  (n % 10) + digitSum(n / 10);
//}
//
//int main() {
//	std::cout << "Welcome to E3.11.5 \n\n";
//	int test_cases[1] = {123};
//	//int test_cases[5] = {123, 507, 9999, 8, 0};
//	
//	for (int i = 0; i < std::size(test_cases); i++) {
//		std::cout << "digitSum(" << test_cases[i] << ") =  " << digitSum(test_cases[i]) << ".\n";	
//	}
//
//}//END main()
//################# END E3.11.5 #################

//################# E3.11.6 C++ Recursion #################
//std::string reverseString(const std::string& text) {
//	if (text.size() == 0) { return text; }
//
//	std::cout << "text = " << text << "\n";
//	std::cout << "text.size() = " << text.size() << "\n";
//
//	return reverseString(text.substr(1)) + text[0];
//}
//
//
//
//int main() {
//	std::cout << "Welcome to E3.11.6 \n\n";
//	const std::string test = "abc";
//
//	//const std::string test_cases[7] = {"hello", "recurssion", "L3Harris", "a", "", "racecar", "emordnilap"};
//	//
//	//for (int i = 0; i < std::size(test_cases); i++) {
//	//	std::cout << "reverseString(" << test_cases[i] << ") =  " << reverseString(test_cases[i]) << "\n\n";	
//	//}
//
//
//	std::cout << "abc another look \n\n";
//	const std::string foo = reverseString(test);
//	std::cout << "reverseString(" << test << ") =  " << foo << "\n\n";
//
//
//}//END main()
//################# END E3.11.6 #################

////################# E3.11.7 C++ Branch Recursion #################
//
//int fibonacci(int n) {
//	if (n == 0) { return 0; }
//	if (n == 1) { return 1; }
//	return fibonacci(n - 1) + fibonacci(n - 2);
//}
//
//int main() {
//	std::cout << "Welcome to E3.11.7 \n";
//
//	int test_values[1] = {20};
//	//int test_values[7] = { 0,1,2,3,5,7,10 };
//
//	for (int i = 0; i < std::size(test_values); i++) {
//			std::cout << "fibonacci(" << test_values[i] << ") =  " << fibonacci(test_values[i]) << ".\n";
//		}
//}//END main()
//################# END E3.11.7 #################

//################# E3.11.8 C++ Branch Recursion Loop Comparator #################
//int fibonacciIterative(int n) {
//	if (n == 0) { return 0; }
//	if (n == 1) { return 1; }
//
//	int seed_1 = 0;
//	int seed_2 = 1;
//
//	int two_back = seed_1;
//	int one_back = seed_2;
//	int fib_carrier = 0;
//
//	for (int i = (n - 1); i > 0; i--) {
//		fib_carrier = two_back + one_back;
//		two_back = one_back;
//		one_back = fib_carrier;
//	}
//	return fib_carrier;
//
//}
//
//int main() {
//	std::cout << "Welcome to E3.11.8 \n";
//
//	int test_values[7] = {0,1,2,5,10,15,20};
//
//	for (int i = 0; i < std::size(test_values); i++) {
//		std::cout << "fibonacci(" << test_values[i] << ") =  " << fibonacciIterative(test_values[i]) << ".\n";
//	}
//}//END main()
//################# END E3.11.8 #################




//################# E3.11.9 C++ Recursion Safety #################
/*
SO - Stack Overflow Risk | TS - Terminates Safely | IR - Incorrect Result
A	if (n == 0) return 0; then return f(n - 1);	n = 5 // SO --> TS
B	if (n == 0) return 0; then return f(n + 1);	n = 5 // TS --> SO
C	if (n >= 10) return 1; then return f(n + 3);	n = 5 // TS
D	if (n == 10) return 1; then return f(n + 3);	n = 5  // SO
E	if (n <= 1) return 1; then return n * f(n - 1);	n = 0 // IR -->
*/
int recursionSafety(int n) {
	//if (n == 0) {return 0;}  //Case A, CaseB
	//if (n >= 10) {return 1;} // Case C
	//if (n == 10) {return 1;} // Case D
	if (n <= 1) { return 1; } // Case E

	//return recursionSafety(n - 1);  //Case A
	//return recursionSafety(n + 1);  // Case B
	//return recursionSafety(n + 3); //Case C, Case D
	return n * recursionSafety(n - 1); // Case E
}

int main() {
	std::cout << "Welcome to E3.11.9 \n";

	int test_values[1] = { 0 };

	for (int i = 0; i < std::size(test_values); i++) {
		std::cout << "Testing recurssion safety with:--> (" << test_values[i] << ") =  " << recursionSafety(test_values[i]) << ".\n";
	}
}//END main()
//################# END E3.11.9 #################
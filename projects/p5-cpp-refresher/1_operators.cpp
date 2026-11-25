	
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
//################# P1 HELLO WORLD ############
//int main()
//{
//    std::cout << "Hello World!\n";
//    return 66;
//}
//################# END P1 #################

//################# P2 CIN #################
//int main() {
//	int a, b;
//
//	std::cout << "Enter two integers: ";
//	std::cin >> a >> b;
//
//	int sum = a + b;
//
//	std::cout << "Sum: " << sum << "\n";
//
//	return 67;
//}
//################# END P2 #################

////################# P3 BRANCHING ############
//int main() {
//
//	int a = 30;
//
//	if(a > 10) {
//		std::cout << "Greater Than";
//	}
//
//	else if (a == 10) {
//		std::cout << "Equal To";
//	
//	}
//
//	else {
//		std::cout << "Less Than";
//	}
//
//}
////################# END P3 #################

//################# P4 BRANCHING WITH CIN############
//int main() {
//
//	int a;
//	std::cout << "Enter a single integer -->  ";
//	std::cin >> a;
//
//	if (a > 10) {
//		std::cout << "Greater Than";
//	}
//
//	else if (a == 10) {
//		std::cout << "Equal To";
//
//	}
//
//	else {
//		std::cout << "Less Than";
//	}
//
//}
//################# END P4 #################

//################# P5 LOOPS ############
//int main(){
//	for (int i = 0; i < 5; i++) {
//		std::cout << i << "\n";
//	}
//
//	int j = 0;
//	while (j < 5) {
//		std::cout << j++ << "\n";
//	}
//
//	int k = 0;
//	do {
//		std::cout << k++ << "\n";
//	} while (k < 5);
//}
//################# END P5 #################

//############# P6 WHILE PRINT #############
//int main() {
//	int a = 1;
//	while (a < 11) {
//		std::cout << a++ << "\n";
//	}
//}
//################# END P6 #################

////############# P7 FUNCTIONS #############
//int multiply(int a, int b) {
//	return a * b;
//}
//
//
//int main() {
//	int a = 1;
//	int b = 10;
//	while (a < 11) {
//		std::cout << multiply(a++, b) << "\n";
//	}
//}
////################# END P7 #################

////############# P8 POINTERS RAW #############
//int main() {
//	auto x = 42; // I took a quick 4-min side trip to explore static vs dynamic types and learned about auto (Im sure it isnt ideal for every situation or maybe every primitive type) 
//	int* p = &x;  //pointer p == address of x.
//
//	std::cout << x << "\n";
//	std::cout << *p << "\n";
//	std::cout << p << "\n";
//	std::cout << &x << "\n";
//
//	*p = 99;
//	std::cout << x << "\n";
//	std::cout << *p << "\n";
//
//	//delete (p);
//	//p = nullptr;
//}
////################# END P8 #################

//############# P9 POINTERS DYNAMIC #############
//int main() {
//	int* p = new int(42);  //pointer p == address of x.
//
//	std::cout << *p << "\n";
//	std::cout << p << "\n";
//
//
//	delete p;
//	p = nullptr;
//
//	std::cout << p << "\n";
//}
//################# END P9 #################

//############# P10 POINTERS UNIQUE #############
//int multiply(int a, int b) {
//	return a * b;
//}
//
//int main() {
//	auto p = std::make_unique<int>(42);
//
//	std::cout << *p << "\n";
//	std::cout << p << "\n";
//
//	*p = 99;
//
//	std::cout << *p << "\n";
//	std::cout << p << "\n";
//
//	std::cout << multiply(3,*p) << "\n";
//	std::cout << (p == nullptr) << "\n";
//}
//################# END P10 #################

//############# P11 POINTERS SHARED/WEAK #############
//int multiply(int a, int b) {
//	return a * b;
//}
//
//int main() {
//	auto p1 = std::make_shared<int>(42);
//	std::cout << p1.use_count() << "...because p1 was added...\n";
//	auto p2 = p1;
//	std::cout << p1.use_count() << "...because p2 was added...\n";
//	auto p3 = p2;
//	std::cout << p1.use_count() << "...because p3 was added...\n";
//	p3.reset();
//	std::cout << p1.use_count() << "...because p3 was removed...\n";
//	p2.reset();
//	std::cout << p1.use_count() << "...because p2 was removed...\n";
//	p1.reset();
//	std::cout << p1.use_count() << "...because p1 is empty...\n";
//	//WEAK EXAMPLE
//	auto p4 = std::make_shared<int>(42);
//	std::cout << p4.use_count() << "...because p4 was added...\n";
//	std::weak_ptr observer = p4;
//	std::cout << p4.use_count() << "...still only 1 ref...\n";
//	std::cout << observer.expired() << "...no no no...\n";
//	p4.reset();
//	std::cout << observer.expired() << "...yes...\n";
//
//
//}
//################# END P11 #################

//############# E1 PRIMITIVES #############
//int main() {
//	bool bool_var_1 = true;
//	bool bool_var_2 = 0;
//	char one_char = 'R';
//	int whole_num = 52;
//	float dec_num = 3.13f;
//	double high_prec_dec_num = 3.1378753;
//	double long_double = 3.13787535767893324567L;
//
//	std::cout << "\n\nA boolean true evaluates to " << (bool_var_1 == 1) << ".\n";
//	std::cout << "A boolean 0 evaluates to " << (bool_var_2 != false) << ".\n";
//	std::cout << "This exercise is brought to you by the letter " << "===> " << one_char << " <===\n";
//	std::cout << "There are " << whole_num << " weeks in a year.\n";
//	std::cout << "It weighs " << dec_num << " pounds.\n";
//	std::cout << std::setprecision(15) << high_prec_dec_num << '\n';
//	std::cout << high_prec_dec_num << " pounds if we use the higher precision setting.\n";
//	std::cout << long_double << " long double.\n";
//	std::cout << std::setprecision(6) << high_prec_dec_num << '\n';
//	std::cout << high_prec_dec_num << " pounds if we use the higher precision setting.\n";
//	std::cout << long_double << " long double.\n";
//	std::cout << "Can get other representations from some of these?  Yes! " << "R is ASCII Decimal " << int(one_char) << ".\n\n";
//}
//################# END E1 #################

//############# E1E1 NUMERIC PRIMITIVE CHARACTERISTICS #############
//int main() { 
//	bool b_1 = true;
//	bool b_2 = 0;
//	char c_1 = 'R';
//	short i_1 = 31000;
//	int i_2 = 52;
//	long i_3 = 77237928372893;
//	long long i_4 = 12789779;
//	float f_1 = 3.13f;
//	double d_1 = 3.1378753;
//	long double d_2 = 3.13787535767893324567L;
//
//	std::cout << "Memory allocated per value\n";
//	std::cout << sizeof(b_1) << "\n";
//	std::cout << sizeof(b_2) << "\n";
//	std::cout << sizeof(c_1) << "\n";
//	std::cout << sizeof(i_1) << "\n";
//	std::cout << sizeof(i_2) << "\n";
//	std::cout << sizeof(i_3) << "\n";
//	std::cout << sizeof(i_4) << "\n";
//	std::cout << sizeof(f_1) << "\n";
//	std::cout << sizeof(d_1) << "\n";
//	std::cout << sizeof(d_2) << "\n";
//
//	std::cout << "\n\nNumeric limits: min/max values\n";
//	std::cout << std::numeric_limits<short>::min() << " to " << std::numeric_limits<short>::max() << "\n";           
//	std::cout << std::numeric_limits<int>::min() << " to " << std::numeric_limits<int>::max() << "\n";           
//	std::cout << std::numeric_limits<long>::min() << " to " << std::numeric_limits<long>::max() << "\n";           
//	std::cout << std::numeric_limits<long long>::min() << " to " << std::numeric_limits<long long>::max() << "\n";
//	std::cout << "float min() --> " << std::numeric_limits<float>::min() << " to " << std::numeric_limits<float>::max() << "\n";
//	std::cout << "float min() hack --> " << std::numeric_limits<float>::min() * -1 << " to " << std::numeric_limits<float>::max() << "\n";
//	std::cout << "float lowest() --> " << std::numeric_limits<float>::lowest() << " to " << std::numeric_limits<float>::max() << "\n";
//	std::cout << "float denorm --> " << std::numeric_limits<float>::denorm_min() << " to " << std::numeric_limits<float>::max() << "\n";
//	std::cout << std::numeric_limits<double>::lowest() << " to " << std::numeric_limits<double>::max() << "\n";           
//	std::cout << std::numeric_limits<long double>::lowest() << " to " << std::numeric_limits<long double>::max() << "\n";           
//
//	std::cout << "\n\nNumeric limits: max precision per value aka longest mantissa in scientific notation?\n";
//	std::cout << std::numeric_limits<short>::digits10 << "\n";    
//	std::cout << std::numeric_limits<int>::digits10 << "\n";    
//	std::cout << std::numeric_limits<long>::digits10 << "\n";    
//	std::cout << std::numeric_limits<long long>::digits10 << "\n";    
//	std::cout << std::numeric_limits<float>::digits10 << "\n";    
//	std::cout << std::numeric_limits<double>::digits10 << "\n";    
//	std::cout << std::numeric_limits<long double>::digits10 << "\n";    
//}
//################# END E1E1 #################

//################# E2 C++ Arithmetic Operators #################
//int main() { 
//	std::cout << "Welcome to E2 \n";
//
//	int a = 17;
//	int	b = 5;
//
//	int add_op = a + b;
//	int sub_op = a - b;
//	int mul_op = add_op * sub_op;
//	int div_op = a / b;
//	int mod_op = a % b;
//	int una_op = mod_op + -mod_op;
//
//	std::cout << "a + b = " << add_op << "\n";
//	std::cout << "a - b = " << sub_op << "\n";
//	std::cout << "add_op * sub_op = " << mul_op << "\n";
//	std::cout << "a / b = " << div_op << "\n";
//	std::cout << "a % b = " << mod_op << "\n";
//	std::cout << "mod_op + -mod_op = " << una_op << "\n";
//
//	std::cout << "a / b = " << a / b << "\n";
//	std::cout << "a.0 / b = " << float(a) / b << "\n";
//
//	std::cout << "Rounding occurs when two integers are divided. Precision is lost.\n";
//	std::cout << "Not only is rounding NOT PERFORMED, but we get a \"precise\" value.\n";
//
//}
//################# END E2 #################

//################# E2 C++ Assignment Operators #################
/*
########################
=	Assign
+=	Add and assign
-=	Subtract and assign
*=	Multiply and assign
/=	Divide and assign
%=	Remainder and assign
########################
*/

//void print_a(int a) {
//	std::cout << "The value of a is -->  " << a << "\n\n";
//}
//
//int main() {
//	std::cout << "Welcome to E2.2 \n";
//
//	int a = 20;
//	int	b = 3;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n\n";
//
//	std::cout << "add_assign = a += b =  " << (a += b) << ".\n";
//	print_a(a);
//	std::cout << "sub_assign = a -= b =  " << (a -= b) << ".\n";
//	print_a(a);
//	std::cout << "mul_assign = a *= b =  " << (a *= b) << ".\n";
//	print_a(a);
//	std::cout << "div_assign = a /= b =  " << (a /= b) << ".\n";
//	print_a(a);
//	std::cout << "mod_assign = a %= b =  " << (a %= b) << ".\n";
//	print_a(a);
//
//	std::cout << "\n\nWhat happens to a after a /= b?\n";
//	std::cout << "a is restored to its original value.\n";
//
//}
//################# END E2.2 #################

//################# E2.3 Increment/Decrement Operators #################
/*
########################
++a	     Prefix increment
a++	     Postfix increment

--a	     Prefix decrement
a--	     Postfix decrement

Note: The distinction: Prefix modifies the variable before its value is used in an expression. Postfix uses the original value before modifying it.
########################
*/

//void print_var(int var, std::string tag) {
//	std::cout << "The value of " <<tag << " is-->  " << var << "\n\n";
//}
//
//int main() {
//	std::cout << "Welcome to E2.3 \n";
//
//	int a = 10;
//	int	b = 20;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n\n";
//
//	std::cout << "Prefix Set \n";
//	print_var(++a, "++a");
//	print_var(a, "a");
//	print_var(++b, "++b");
//	print_var(b, "b");
//
//	a = 10;  b = 20;  //RESET
//	std::cout << "Reset: \n";
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n\n";
//
//	print_var(--a, "a");
//	print_var(a, "a");
//	print_var(--b, "b");
//	print_var(b, "b");
//
//	std::cout << "Postfix Set \n";
//	print_var(a++,"a++");
//	print_var(a,"a");
//	print_var(b++, "b++");
//	print_var(b, "b");
//
//	a = 10;  b = 20;  //RESET
//	std::cout << "Reset: \n";
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n\n";
//
//	print_var(a--, "a--");
//	print_var(a, "a");
//	print_var(b--, "b--");
//	print_var(b, "b");
//
//	a = 1;  b = 2;  //RESET
//	for (int i = 0; i < 10; i++) { std::cout << "Pre: " << ++a << "  Post: " << a++ << "\n"; }
//	std::cout << "\n\n";
//	a = 1;  b = 2;  //RESET
//	for (int i = 0; i < 10; i++) { std::cout << "Post: " << a++ << "  Pre: " << ++a << "\n"; }
//	a = 1;  b = 2;  //RESET
//	for (int i = 0; i < 10; i++) { std::cout << a << "\n"; print_var(++a, "++a"); }
//	a = 1;  b = 2;  //RESET
//	for (int i = 0; i < 10; i++) { std::cout << a << "\n"; print_var(a++, "a++"); }
//}
//################# END E2.3 #################

//################# E2.4 C++ Comparison Operators #################
/*
########################
==	Equal to
!=	Not equal to
>	Greater than
<	Less than
>=	Greater than or equal to
<=	Less than or equal to
########################
*/
//
//bool compare_it(int a, int b, std::string oper) {
//	if (oper == "==") {return (a==b);}
//	if (oper == "!=") {return (a!=b);}
//	else if (oper == ">") { return (a > b); }
//	else if (oper == "<") { return (a < b); }
//	else if (oper == ">=") { return (a >= b); }
//	else if (oper == "<=") { return (a <= b); }
//	else {std::cout << "operator not found\n\n";
//	}
//}
//
//void print_outcome(int a, int b, std::string op, bool ans) {
//	std::cout << "The result of " << a << " " << op << " " << b << " is -->  " << ans << "\n\n";
//
//}
//
//int main() {
//	std::cout << "Welcome to E2.4 \n";
//
//	int a = 10;
//	int	b = a;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n\n";
//
//	std::string comp_operators[6] = { "==", "!=", ">", "<", ">=", "<?"};
//
//	for (int i = 0; i < size(comp_operators); i++) {
//		print_outcome(a, b, comp_operators[i], compare_it(a, b, comp_operators[i])); 	
//	}
//
//	std::cout << "What the heck is going on with the first two prints? \n\n";
//
//	a = 20; b = a;
//	for (int i = 0; i < size(comp_operators); i++) {
//		print_outcome(a, b, comp_operators[i], compare_it(a, b, comp_operators[i]));
//	}
//}
//################# END E2.4 #################

//################# E2.5 C++ Logical Operators #################
/*
########################
&&	Logical AND	--> Both conditions are true
\|\|	Logical OR	--> At least one condition is true
!	Logical NOT	--> The condition is false
########################
*/

//bool compare_it(int a, int b, std::string oper) {
//	if (oper == "==") { return (a == b); }
//	if (oper == "!=") { return (a != b); }
//	else if (oper == ">") { return (a > b); }
//	else if (oper == "<") { return (a < b); }
//	else if (oper == ">=") { return (a >= b); }
//	else if (oper == "<=") { return (a <= b); }
//	else {
//		std::cout << "operator not found\n\n";
//	}
//}
//
//bool test_it(bool a, bool b = false, std::string oper = "!") {
//	if (oper == "&&") { return (a && b); }
//	else if (oper == "||") { return (a || b); }
//	else if (oper == "!") { return !a; }
//	else {
//		std::cout << "operator not found\n\n";
//	}
//}
//
//
//int main() {
//	std::cout << "Welcome to E2.5 \n";
//
//	int a = 10;
//	int	b = 20;
//	int	c = 30;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n";
//	std::cout << "c =  " << c << ".\n\n";
//
//	std::string comp_operators[6] = { "==", "!=", ">", "<", ">=", "<?" };
//	std::string logi_operators[3] = { "&&", "||", "!"};
//
//
//	std::cout << "a < b && b < c = " << test_it(compare_it(a, b, "<"), compare_it(b, c, "<"), "&&") << ".\n";
//	std::cout << "a < b || b < c = " << test_it(compare_it(a, b, ">"), compare_it(b, c, "<"), "||") << ".\n";
//	std::cout << "!(a == b) = " << test_it(compare_it(a, b, "=="), "!") << ".\n\n";
//
//
//	int x = 0;
//
//	bool function_result = compare_it(a, b, ">");
//	bool statement_result = (a > b) && (x++ > 0);
//
//	std::cout << "x =  " << x << ".\n\n";
//
//	std::cout << "(a > b) && (++x < 0) = " << test_it(function_result, statement_result, "&&") << ".\n\n";
//
//}
//################# END E2.5 #################

//################# E2.6.8 C++ Bitwise Operators #################
/*
########################
&	Bitwise AND	--> Both bits are 1
|	Bitwise OR	--> One  bit is 1
^	Bitwise XOR	--> Both bits match
~	Bitwise NOT	--> Flip all bits
<<	Bits ->  left	--> shift bits << n --> mult times 2^n
>>	Bits -> right	--> shift bits >> n --> div by 2^n, the bit cliff accepts all that fall off (== the remainder if int div)
########################
//*/
//bool compare_it(int a, int b, std::string oper) {
//	if (oper == "==") { return (a == b); }
//	else if (oper == "!=") { return (a != b); }
//	else if (oper == ">") { return (a > b); }
//	else if (oper == "<") { return (a < b); }
//	else if (oper == ">=") { return (a >= b); }
//	else if (oper == "<=") { return (a <= b); }
//	else {
//		std::cout << "operator not found\n\n";
//	}
//}
//
//bool test_it(bool a, bool b = false, std::string oper = "!") {
//	if (oper == "&&") { return (a && b); }
//	else if (oper == "||") { return (a || b); }
//	else if (oper == "!") { return !a; }
//	else {
//		std::cout << "operator not found\n\n";
//	}
//}
//
//bool check_oper(std::vector<std::string> arr, std::string oper = "") {
//	auto it = std::find(arr.begin(), arr.end(), oper);
//	return it != arr.end();
//}
//
//
//int main() {
//	std::cout << "Welcome to E2.6.8 \n";
//
//	unsigned int a = 53;
//	unsigned int b = 26;
//
//	std::cout << "a =  " << a << " = " << std::bitset<8>(a) << ".\n";
//	std::cout << "b =  " << b << " = " << std::bitset<8>(b) << ".\n\n";
//
//	std::vector<std::string> comp_operators = { "==", "!=", ">", "<", ">=", "<=" };
//	std::vector<std::string> logi_operators = { "&&", "||", "!" };
//	std::vector<std::string> bitw_operators = { "&", "|", "^", "~", "<<", ">>" };
//
//	if (check_oper(bitw_operators, "&")) { std::cout << "a & b = " << std::bitset<8>(a & b) << "\n"; }
//	if (check_oper(bitw_operators, "|")) { std::cout << "a | b = " << std::bitset<8>(a | b) << "\n"; }
//	if (check_oper(bitw_operators, "^")) { std::cout << "a ^ b = " << std::bitset<8>(a ^ b) << "\n"; }
//	if (check_oper(bitw_operators, "<<")) { std::cout << "a << 2 = " << std::bitset<8>(a << 2) << "\n"; }
//	if (check_oper(bitw_operators, ">>")) { std::cout << "a >> 1 = " << std::bitset<8>(a >> 1) << "\n\n"; }
//
//
//	if (check_oper(bitw_operators, "&")) { std::cout << "a & b = " << (a & b) << "\n"; }
//	if (check_oper(bitw_operators, "|")) { std::cout << "a | b = " << (a | b) << "\n"; }
//	if (check_oper(bitw_operators, "^")) { std::cout << "a ^ b = " << (a ^ b) << "\n"; }
//	if (check_oper(bitw_operators, "<<")) { std::cout << "a << 2 = " << (a << 2) << "\n"; }
//	if (check_oper(bitw_operators, ">>")) { std::cout << "a >> 1 = " << (a >> 1) << "\n"; }
//
//}
//################# END E2.6.8 #################

//################# E2.6.9 C++ Compound Bitwise Operators #################
/*
###### result to left term ########
&=	Bitwise AND	--> Both bits are 1
|=	Bitwise OR	--> One  bit is 1
^=	Bitwise XOR	--> Both bits differ
~=	Bitwise NOT	--> Flip all bits
<<=	Bits ->  left	--> shift bits << n --> mult times 2^n
>>=	Bits -> right	--> shift bits >> n --> div by 2^n, the bit cliff accepts all that fall off (== the remainder if int div)
########################
*/
//void display_result(int ans, std::string oper, int shift=1) {
//	if ((oper == "<<= ") || (oper == ">>= ")) { 
//		std::cout << "a " << oper << shift << " == " << "binary:" << std::bitset<8>(ans) << " and decimal:" << ans << "\n";
//	}
//
//	else { 
//		std::cout << "a " << oper << " b == " << "binary:" << std::bitset<8>(ans) << " and decimal:" << ans << "\n";
//	}
//
//}
//
//int main() {
//	std::cout << "Welcome to E2.6.9 \n";
//
//	unsigned int a = 53;
//	unsigned int b = 26;
//
//
//	std::cout << "a =  " << a << " = " << std::bitset<8>(a) << ".\n";
//	std::cout << "b =  " << b << " = " << std::bitset<8>(b) << ".\n\n";
//
//	a &= b; display_result(a, "&=");
//	a |= b; display_result(a, "|="); 
//	a ^= b; display_result(a, "^="); 
//	a <<= 2; display_result(a, "<<= ", 2); 
//	a >>= 1; display_result(a, ">>= ", 1);
//}
//################# END E2.6.9 #################

//################# E2.7 C++ Ternary Operator: The Compact if/else #################
/*
condition ? value_if_true : value_if_false;
  (a > b) ?       a        :      b;
example: int largest = (a > b) ? a : b;
########################
*/
//int main() {
//	std::cout << "Welcome to E2.7 \n";
//
//	unsigned int a = 35;
//	unsigned int b = 17;
//	unsigned int c = 17;
//
//	int smaller = (a < b) ? a : b;
//	std::cout << "smaller: " << smaller << ".\n";
//
//	int larger = (a > b) ? a : b;
//	std::cout << "larger: " << larger << ".\n";
//
//	int odd = (a % 2 == 0) ? 0:1;
//	if (odd) { std::cout << a << " is an odd number." << ".\n"; }
//	else { std::cout << a << " is an even number." << ".\n"; }
//
//
//	std::cout << "\nRound 2 \n\n";
//
//	a = 20;
//	b = 17;
//
//	smaller = (a < b) ? a : b;
//	std::cout << "smaller: " << smaller << ".\n";
//
//	odd = (a % 2 == 0) ? 0 : 1;
//	if (odd) { std::cout << a << " is an odd number." << ".\n"; }
//	else { std::cout << a << " is an even number." << ".\n"; }
//
//
//	smaller = (c < b) ? c : b;
//	std::cout << "smaller: " << smaller << ".\n";
//	std::cout << "If both numbers are equal return the value. \n";
//}
//################# END E2.7 #################

//################# E2.8 C++ sizeof() and type casting #################
//
///*
//static_cast<T>(value) explicitly converts a value to type T
//*/
//
//int main() {
//	std::cout << "Welcome to E2.8 \n";
//
//	int a = 17;
//	int b = 5;
//	double c = 3.9;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n";
//	std::cout << "c =  " << c << ".\n\n";
//
//	std::cout << "size of a : " << sizeof(a) << ".\n";
//	std::cout << "size of c : " << sizeof(c) << ".\n";
//	std::cout << "a / b : " << a / b << ".\n";
//	std::cout << "static_cast<double>(a) / b : " << static_cast<double>(a) / b << ".\n";
//	std::cout << "size of a : " << sizeof(a) << " <--- No...still an int.\n";
//	std::cout << "static_cast<int>(c) : " << static_cast<int>(c) << ".\n";
//	std::cout << "size of c : " << sizeof(c) << " <--- No...still a double.\n";
//
//
//}
//################# END E2.8 #################

//################# E2.9 C++ operator precedence #################

/*
My Sandwich Choice : Bacon Lettuce and Tomatoe, Alright?
(!, ~, ++, --) --> Maths(PEMDAS) --> Shifts --> Comparisons(GLT first) --> Bitwise(AXO) --> Logical(AO) --> Ternary, Assignment
*/
//void display_result(bool exp = 1) {
//	std::cout << "expression result = " << exp << ".\n";
//	}
//int main() {
//	std::cout << "Welcome to E2.9 \n";
//
//	int a = 10;
//	int b = 5;
//	int c = 2;
//
//	std::cout << "a =  " << a << ".\n";
//	std::cout << "b =  " << b << ".\n";
//	std::cout << "c =  " << c << ".\n\n";
//
//	std::cout << "chaperoned expression = " << (a > b && b > c) << ".\n";
//
//	display_result(a > b && b > c);  // Valid
//
//	//std::cout << "(a + b) * c = " << (a + b) * c << ".\n";
//	//std::cout << "((a > b) && (b > c)) = " << ((a > b) && (b > c)) << ".\n\n";
//
//	//std::cout << "Trying different parenthetic variations: \n";
//	//std::cout << "((a + b) > (c * 5)) = " << ((a + b) > (c * 5)) << ".\n";
//	//std::cout << "(a + b > c * 5) = " << (a + b > c * 5) << ".\n";
//	//std::cout << "(a + b > (c * 5)) = " << (a + b > (c * 5)) << ".\n";
//	//std::cout << "((a + b) > c * 5) = " << ((a + b) > c * 5) << ".\n\n";
//
//	//std::cout << "(a + b == b + c)  = " << (a + b == b + c) << ".\n";
//	//std::cout << "No parents is not an option. \n";
//}
//################# END E2.9 #################

//################# E2.10 C++ operator associativity #################

/*
My Sandwich Choice : Bacon Lettuce and Tomatoe, Alright?
UNARY(!, ~, ++, --) --> Maths(PEMDAS) --> Shifts --> Comparisons(GLT first) --> Bitwise(AXO) --> Logical(AO) --> Ternary, Assignment
Operator Associativity --> Left to Right MSCBL + postfix, Right to Left TAU + prefix
*/

int main() {
	std::cout << "Welcome to E2.10 \n";

	int a = 20;
	int b = 5;
	int c = 2;

	int ans_1 = a - b - c;
	int ans_2 = a / b / c;
	int ans_3 = a = b = c;

	std::cout << "a - b - c =  " << ans_1 << ".\n";
	std::cout << "a / b / c =  " << ans_2 << ".\n";
	std::cout << "a = b = c =  " << ans_3 << ".\n\n";

	a = 20;
	b = 5;
	c = 2;

	std::cout << "a - b - c =  " << (a - b - c) << ".\n";
	std::cout << "a / b / c =  " << (a / b / c) << ".\n";
	std::cout << "a = b = c =  " << (a = b = c) << ".\n\n";

	a = 20;
	b = 5;
	c = 2;

	std::cout << "a - b - c =  " << a - b - c << ".\n";
	std::cout << "a / b / c =  " << a / b / c << ".\n";
	std::cout << "a = b = c =  " << (a = b = c) << ".\n\n";
}
//################# END E2.10 #################

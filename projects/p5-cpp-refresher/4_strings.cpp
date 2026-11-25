
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

//################# E3.13.1 C++ Strings & Characters! 🚀🧀 #################
/*
char — a single character, using single quotes.
std::string — a sequence of characters, using double quotes
char letter = 'A';  // isalpha(), isdigit(), isalnum(), isspace(), isupper(), islower(), toupper(), tolower()
std::string word = "Hello";   // .size(), .append(), .find(), and .substr()

Java and C++ share the same rule

Java String → Immutable.
C++ std::string → Mutable.
Python str → Immutable.

<cstring> functions that use null termination to stop iterating:
std::strlen()	Count characters until '\0'
std::strcpy()	Copy a C-style string
std::strcat()	Append a C-style string
std::strcmp()	Compare two C-style strings
std::strchr()	Find a character
std::strstr()	Find a substring
*/
//
//int main() {
//
//	std::cout << "Welcome to E3.13.1 \n\n";
//	char single_letter = 'R';
//	std::string stan_str = "Radar";
//
//	std::cout << "This episode of Sesame Street has been brought to you by the letter " << single_letter << ".\n";
//	std::cout << "The " << stan_str.size() << " character string du jour is " << stan_str << ".\n";
//
//	std::cout << "The first character is " << stan_str[0] << " and the last character is " << stan_str[stan_str.size() - 1] << ".\n";
//	stan_str = "L" + stan_str.substr(1);
//	std::cout << "The reassigned (immutable) string is now " <<  stan_str << ".\n";
//	stan_str.append("Systems");
//	std::cout << "The " << stan_str.size() << " character modified string is now " << stan_str << ".\n";
//
//}
//################# END E3.13.1 #################

//################# E3.13.2 C++ Strings Operations #################
/*
std::string text = "Radar Systems";

text.find("Systems");       // Starting index: 6
text.substr(0, 5);          // "Radar"
text.replace(0, 5, "Laser"); // "Laser Systems"
*/

//int main() {
//
//	std::cout << "Welcome to E3.13.2 \n\n";
//	std::string message = "Radar Systems Online";
//
//	std::cout << "The " << message.size() << " character string for E3.13.2 is " << message << ".\n";
//	std::cout << "substring \"Systems\" begins at index " << message.find("Systems") << " of " << message << ".\n";
//	std::cout << message.substr(0,5) << ".\n";
//	std::cout << message.replace(0, 5, "Laser") << ".\n";
//	std::cout << message.append("!") << "\n";
//	std::cout << "substring \"s\" begins at index " << message.find('s') << " of " << message << ".\n";
//	std::cout << message << "\n";
//
//	// Bonus
//	//std::cout << "substring \"v\" begins at index " << message.find('v') << " of " << message << ".\n";
//	std::cout << message.replace(0, 5, "Giant Planet Killing Death laser") << ".\n";
//	/*
//	B1
//	substring "z" begins at index 18446744073709551615 of Laser Systems Online!. ?? std::string::npos is the special unsigned value representing not found. That enormous integer you observed is its numerical representation
//	substring "x" begins at index 18446744073709551615 of Laser Systems Online!.
//	substring "v" begins at index 18446744073709551615 of Laser Systems Online!.
//
//	B2
//	No, it is designed to read at or from to, not replace
//
//	B3
//	It obliges
//	Giant Planet Killing Death laser Systems Online!.
//	
//	*/
//
//}
//################# END E3.13.2 #################

//################# E3.13.3 C++ String Iteration & Character Manipulation #################
/*
* char letter = 'A';  // isalpha(), isdigit(), isalnum(), isspace(), isupper(), islower(), toupper(), tolower()
#include <cctype>
#include <string>

std::string text = "Radar";

for (char& c : text) {
	c = static_cast<char>(std::toupper(c));
}

// Bonus
Why does char& allow modification while char doesn't? ---> because you have to access the memory location to change it.  read only vs &-fuled access
Does std::toupper() modify its argument directly? ---> excercised it!  Absolutley not.  reassigmnet required.
What happens to punctuation during uppercase conversion ---> it seems to return the unaltered punctuation as if to say ---> It's already upper case!
Subsequent tests of integers and whitespace have the same result --> input returned...that's nice...I think
*/

//void stringOps(std::string& patient, std::string operation) {
//
//	// Counting
//	int counter = 0;
//	if (operation == "alpha") {for (char letter : patient) {if (isalpha(letter)) {counter++;}}	
//		std::cout << operation <<" count is: " << counter << ".\n";
//	}//End alpha
//
//	if (operation == "digit") {for (char letter : patient) {if (isdigit(letter)) {counter++;}}
//		std::cout << operation <<" count is: " << counter << ".\n";
//	}//End digit
//
//	if (operation == "space") {for (char letter : patient) {if (isspace(letter)) {counter++;}}
//		std::cout << operation << " count is: " << counter << ".\n";
//	}//End space
//
//	if (operation == "upper") {for (char& letter : patient) {if (isalpha(letter)) {letter = toupper(letter);}}
//		std::cout << operation << " produces: " << patient << ".\n";
//	}//End upper
//		
//		
//}//END StringOps()
//		
//
//int main() {
//	std::cout << "Welcome to E3.13.3 \n\n";
//	std::string message = "Radar Systems 2026";
//	std::cout << "The message for E3.13.3 is " << message << ".\n";
//	std::vector<std::string> opSet = { "alpha", "digit", "space", "upper" };
//
//	for (std::string op:opSet) {
//		stringOps(message, op);
//	}
//	std::cout << "The message for E3.13.3 is now " << message << ".\n";
//	//Bonus
//	char punc = '@';
//	char upper_punc = toupper(punc);
//	std::cout << "When toupper() is applied to punctuation like " << punc << " you get " << upper_punc << ".\n";
//}
//################# END E3.13.3 #################

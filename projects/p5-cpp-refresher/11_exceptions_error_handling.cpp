
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
#include <stdexcept>

//################# E3.20.1 C++ Exceptions: Throwing, Catching & Validation #################
/* Notes
* Exception type			Typical purpose
=================================================================
std::invalid_argument	Invalid input argument
std::out_of_range		Access outside valid boundaries
std::runtime_error		Failure encountered during execution
std::exception			Common base class for standard exceptions

try {
    throw std::invalid_argument("Invalid input");
}
catch (const std::invalid_argument& e) {
    std::cout << e.what() << '\n';
}

*/
//Part A
//double safeDivide(double numer, double denom) {
//    if (denom == 0) { throw std::invalid_argument("Invalid Argumant: IEEE 754 says dividing doubles by 0 produces +inf, -inf, or Nan, so dont do it again please.\n"); }
//    return numer / denom;
//}//end of safeDivide()
//
////Part B
//int safeAccess(const std::vector<int>& vec, int index) {
//    if ((index < 0) || (index >= (vec.size()))) { throw std::out_of_range("Index " + std::to_string(index) + " is out of range for a zero-indexed vector of size: " + std::to_string(vec.size()) + ".\n");}
//    return vec[index];
//}//end of safeAccess()
//
////Part C
//void radarScan(bool hardwareReady) {
//    if (!hardwareReady) { throw std::runtime_error("Radar hardware unavailable");}
//    else { std::cout << "Radar scan successful"; }
//}//end of radarScan()
//
////Helper
//template<typename T>
//void printResult(const T& result) {
//    std::cout << "Test successful. Result: " << result << "\n";
//}//end of printResult()
//
//
////Part D
//int main() {
//	std::cout << "Welcome to E3.20.1 \n\n";
//    //std::vector<int> vec = {};
//    std::vector<int> vec = {10, 20, 30};
//
//    //Test 1
//    try {
//        printResult(safeDivide(20, 4));
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 2
//    try {
//        printResult(safeDivide(20, 0));
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 3
//    try {
//        printResult(safeAccess(vec, 1));
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 4
//    try {
//        printResult(safeAccess(vec, -1));
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 5
//    try {
//        printResult(safeAccess(vec, 5));
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 6
//    try {
//        radarScan(true);
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//
//    //Test 7
//    try {
//        radarScan(false);
//    }
//    catch (const std::exception& e) {
//        std::cout << e.what() << '\n';
//    }
//    std::cout << "\nAll tests completed\n";
//}//end of main

/*  Bonus Q
*
Does execution continue within a function after it throws an exception?
--> No

Why catch exceptions by const reference rather than by value?
--> ref ensures the input is original, const ref ensures that same + no modify

Can a single try block have multiple catch blocks?
-->  From memory Yes.  The catch is just things to do, I believe you can even have more than one try, but first failure gets the exception.

Could catch (const std::exception& e) handle all three exception types used in this exercise?
--> Um Yes, we just did it.

Why might throwing an exception be preferable to returning a sentinel value such as -1?
--> Because a sentinel tells you 1 is negative.  A well messaged exception will guide the engineer to the fix.  It can be like post error recovery coaching.

*/
//################# END E3.20.1 #################

//################# E3.20.2 C++ Exception Handling: Multiple Handlers & Custom Exceptions #################
/* Notes
try {
    // Operation that may fail
}
catch (const std::invalid_argument& e) {
    std::cout << e.what();
}
catch (const std::runtime_error& e) {
    std::cout << e.what();
}
catch (const std::exception& e) {
    std::cout << e.what();
}

Important: Catch specific exception types before general ones. Only the first matching handler executes.
<-- Matching means the catch handler's exception type is compatible with the thrown exception.

Custom Exceptions
class SensorError : public std::runtime_error {
public:
    SensorError(const std::string& msg)
        : std::runtime_error(msg) {}
};

throw SensorError("Sensor unavailable");

Custom exception classes can publicly inherit std::runtime_error.
A custom exception class constructor can forward its const ref string message to the base class' constructor.
*/
//Part A
class RadarError : public std::runtime_error {
public:
    RadarError(const std::string& msg)
        : std::runtime_error(msg) {}
};//end of constructor

//Part B
void processRadar(int targetCount, bool hardwareReady) {
    if (targetCount < 0) { throw std::invalid_argument("Target count must be >= 0 \n"); }
    if (targetCount > 100) { throw std::out_of_range("Target count must be between 0 and 100\n "); }
    if (!hardwareReady) { throw RadarError("Radar hardware unavailable\n"); }
    std::cout << "Radar processing successful." << "Target Count is " << targetCount << "\n";
}//end of processradar()

//Part C
void runTest(int targetCount, bool hardwareReady) {
    try {
        processRadar(targetCount, hardwareReady);
    }
    catch (const std::invalid_argument& e) { //catches errors relto: targetCount; negative values
        std::cout << "|Negative Value Exception Handler|\n";
        std::cout << "Target count must be >= 0\n\n";
        std::cout << e.what();
    }
    catch (const std::out_of_range& e) { //catches errors relto: targetCount; over the target count limit
        std::cout << "|Max Value Exception Handler|\n";
        std::cout << "Target count must be <= 100\n\n";
        std::cout << e.what();
    }
    catch (const RadarError& e) { //catches errors relto: hardwareReady
        std::cout << "|Hardware Readiness Exception Handler|\n";
        std::cout << "Radar unavialable for targeting\n\n";
        std::cout << e.what();
    }
    catch (const std::exception& e) { //catches errors relto: the general catch all (that isnt caught by the first 3)
        std::cout << "|General Purpose Exception Handler|\n\n";
        std::cout << e.what();
    }
}//end of runTest()

//Part D
int main() {
    std::cout << "Welcome to E3.20.2 \n\n";

    //A better pattern using stand vector pair
    std::vector<std::pair<int, bool>> targets = {
    { 25, true },
    { -5, true },
    { 150, true },
    { 50, false },
    { 100, true },
    { 0, true }
    };

    //No size compare or struct needed
    int test_count = 0;
    for (const auto& item : targets) {
        runTest(item.first, item.second);
        test_count++;
    }

    //works fine but the pattern above kills!
    //struct TestData {
    //    std::vector<int> targets = { 25, -5, 150, 50, 100, 0 };
    //    std::vector<bool> hardware = { true, true, true, false, true, true };
    //};// end of testData
    //TestData radarData;

    //int test_count = 0;
    //if (radarData.targets.size() == radarData.hardware.size()) {
    //    int i = 0;
    //    for (int target:radarData.targets) {
    //        runTest(target, radarData.hardware[i]);
    //        i++;
    //        test_count++;
    //    }//end of outter for loop: targets
    //}//end of size comparison

    std::cout << "\nAll " << test_count << " tests completed\n";
}//end of main

/*  Bonus Q
*
Why should the general std::exception handler come last?
--> Because custom or specific handlers provide an opportunity for more focused feedback, plus, Ive heard the general handler doesnt always find a match.

Why can RadarError use what() without implementing it?
-->I assume all functions inherit the what().super class  by default  hey look at that comment --> Your custom exception inherits what() from its base class.

Can multiple catch blocks execute for a single thrown exception?
--> No.  First match wins

Could a std::runtime_error handler catch a RadarError?
-->  I assume no, that's why me made a custom handler

Why might custom exceptions be useful in a large software system?
--> When there could be error situations not covered by the standard stuff. Like if (weird condition 1 + odd condition 2 + unique situation 3) occur {please tell me how to fix it precisely
so I dont have to navigate this giant software system (burning up precious man hours)trying to find the problem}
*/
//################# END E3.20.2 #################





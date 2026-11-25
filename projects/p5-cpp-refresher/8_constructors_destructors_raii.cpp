
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

//################# E3.17.1 C++ Object Lifetime & Destructors #################
/* Notes
* A destructor is a special member function that runs when an object is destroyed.
class RadarTarget {
private:
    int id;

public:
    RadarTarget(int i) : id(i) {
        std::cout << "Constructed: " << id << '\n';
    }

    ~RadarTarget() {
        std::cout << "Destroyed: " << id << '\n';
    }
};

Constructor						Destructor
==============================================================
Runs during object creation		Runs during object destruction
Same name as class				~ followed by class name
Can accept parameters			Cannot accept parameters
Can be overloaded				Cannot be overloaded
No return type					No return type
*/

//Part A
//class RadarTarget {
//private:
//    int id;
//
//public:
//    RadarTarget(int i):
//    id(i)
//    {
//        std::cout << "Constructed: " <<"<" << id << ">" << ".\n";
//    } //end of constructor
//
//    ~RadarTarget() { 
//        std::cout << "Destroyed: " << "<" << id << ">" << ".\n"; 
//    } //end of destructor
//
//    //Getters
//    int getID() const { return id; }
//}; //end of class radarTarget
//
////Part B
//int main() {
//	std::cout << "Welcome to E3.17.1 \n\n";
//    RadarTarget target1(101);
//    {
//        RadarTarget target2(202);
//        RadarTarget target3(303);
//        std::cout << "End of nested scope. \n\n";
//    }  //enter a nested scope --> Practical uses: Resource management, temporary objects, and preventing variable-name collisions.
//    std::cout << "back in main() scope. \n\n";
//    std::cout << "Target 1 ID is: " << target1.getID() << "\n\n";
//    std::cout << "I believe we are done in main(). Time to return 0. \n\n";
//}//end of main
/*
Why are target3 and target2 destroyed in reverse construction order?
--> destructors are still functions and functions use the stack to support execution.
<-- Refinement: automatic local objects are destroyed in reverse construction order as their scope exits; this isn't because destructors themselves use the call stack.

Does a destructor require an explicit call like delete for an ordinary local object?
--> No, we just exposed it to override it with a print statement.  Stuff has been being destroyed the whole time we've been training, just under the hood, with out my intervention.

What happens to an object's lifetime if it's created with new?
--> I believe it's lifetime is "cemented" until the "unwind" I assum the new/delete pairing is a requrement everywhere.
<-- new/delete is not a requirement everywhere. Modern C++ favors automatic storage, containers, and RAII ownership such as unique_ptr

Why might automatic destruction be useful when managing files, locks, or dynamically allocated memory?
--> less engineer management, less code, can't mess it up if it is done for you.
*/
//################# END E3.17.1 #################

//################# E3.17.2 C++ RAII (Resource Acquisition Is Initialization): Automatic Resource Management #################
/* Notes
C++ technique: acquire resources during initialization and release them automatically when the owning object's lifetime ends.
Key: Scope exit triggers cleanup. 🧀    <-- Deterministic resource cleanup
RAII connects resource ownership to object lifetime.

#include <memory>

void radarScan() {
    auto data = std::make_unique<int>(42);

    std::cout << *data << '\n';
} // data is destroyed; its owned memory is released;  no explicit delete required

Concept			Purpose
==================================================================
Acquisition		Obtain a resource
Ownership		Establish responsibility for that resource
Destructor		Release the owned resource
Scope exit		Trigger automatic destruction of local objects
RAII			Connect acquisition and cleanup to object lifetime

In this exercise the destructor is only reporting cleanup. The unique_ptr member performs the actual memory release automatically when it is destroyed.

*/
//Part A
//class RadarBuffer {
//private:
//    std::unique_ptr<int[]> data;
//    int size;
//
//public:
//    RadarBuffer(int buffer_size) {
//        size = buffer_size;
//        data = std::make_unique<int[]>(size);
//        std::cout << "Buffer aquired.\n";
//    }//end of constructor
//
//    ~RadarBuffer() {
//        std::cout << "Buffer released.\n";
//    }//end of destructor
//
//    //Getter and Setter
//    int getValue(int index) { 
//        if (index < 0 || index > (size - 1)) { return -1; }
//        return data[index]; 
//    }
//
//    int setValue(int index, int value) { 
//        if (index < 0 || index >(size - 1)) { return -1; }
//        data[index] = value; 
//    }
//};//end of class RadarBuffer
//
//
//void processRadarData(bool abort) {
//    //Part C
//    std::vector<int> part_c = { 77, 25, 36 };
//    RadarBuffer buffer2(part_c.size());
//    int i = 0;
//    for (int value : part_c) {
//        buffer2.setValue(i, value);
//        std::cout << "buffer2 value " << (i + 1) << " is " << buffer2.getValue(i) << ".\n";
//        i++;
//    }
//    if (abort) { std::cout << "Scan aborted.\n"; return; }
//    else std::cout << "Scan completed.\n";
//}//end of processRadarData()
//
////Part B
//int main() {
//    std::cout << "Welcome to E3.17.2 \n\n";
//    int buffer_size = 5;
//    {
//        RadarBuffer buffer1(buffer_size);
//        for (int i = 0; i < buffer_size; i++) {
//            int value = (i + 1) * 10;
//            buffer1.setValue(i, value);
//            std::cout << "buffer1 value " << (i + 1) << " is " << buffer1.getValue(i) << ".\n";
//        }
//    }//end of nested scope
//    std::cout << "Returned to main scope.\n";
//
//    ////Part C
//    //std::vector<int> part_c = { 77, 25, 36 };
//    //RadarBuffer buffer2(part_c.size());
//    //int i = 0;
//    //for (int value:part_c) {
//    //    buffer2.setValue(i, value);
//    //    std::cout << "buffer2 value " << (i + 1) << " is " << buffer2.getValue(i) << ".\n";
//    //    i++;
//    //}
//    processRadarData(false);
//    processRadarData(true);
//}//end of main

/* Bonus Q
Why does RadarBuffer not need to manually call delete[]?
--> The unique_ptr member performs the actual memory release automatically when it is destroyed (it's reference counter ==0)
<-- unique_ptr doesn't use shared-ownership reference counting. Its destructor releases its owned allocation.
<-- The destructor's print statement doesn't release memory; the unique_ptr member's destructor does that afterward.

Does an early return prevent local object destruction?
--> No, isnt that the whole point ? Lifetime?  and lifetime is tied to usage.

What happens if RadarBuffer contains multiple RAII-managed resources?
--> Not 100% sure bro. I imagine this process scaled up. Management still happens in the order they were initiated.
<-- Multiple RAII-managed members are automatically destroyed in reverse member declaration order.

Why is RAII particularly useful when exceptions occur?
--> It might make it easier to find the problem.  Fewer suspects so less to consider I suppose.

What's the difference between the RadarBuffer destructor printing a message and the actual memory being released?
--> The print is one final overload-induced exec before actual obj destruction. The print just delays the action.
*/
//################# END E3.17.2 #################

//################# E3.17.3 C++ RAII Under Pressure: Exception Safety #################
/* Notes
try {
    throw std::runtime_error("Radar failure");
}
catch (const std::exception& e) {
    std::cout << e.what() << '\n';
}

Keyword				Purpose
========================================================================
try					Enclose code that may throw
throw				Signal an exceptional condition
catch				Handle a matching exception
e.what()			Retrieve the exception's message
Stack unwinding		Destroy local objects while propagating an exception

*/
class RadarBuffer {
private:
    std::unique_ptr<int[]> data;
    int size;

public:
    RadarBuffer(int buffer_size) {
        size = buffer_size;
        data = std::make_unique<int[]>(size);
        std::cout << "Buffer aquired.\n";
    }//end of constructor

    ~RadarBuffer() {
        std::cout << "Buffer released.\n";
    }//end of destructor

    //Getter and Setter
    int getValue(int index) {
        if (index < 0 || index >(size - 1)) { return -1; }
        return data[index];
    }

    int setValue(int index, int value) {
        if (index < 0 || index >(size - 1)) { return -1; }
        data[index] = value;
        return 0;
    }
};//end of class RadarBuffer


//Part A
void processRadarScan(bool simulateFailure) {
    std::vector<int> buffer_values = { 10, 20, 30 };
    RadarBuffer buffer(static_cast<int>(buffer_values.size()));
    int i = 0;
    for (int value : buffer_values) {
        buffer.setValue(i, value);
        std::cout << "buffer value " << (i + 1) << " is " << buffer.getValue(i) << ".\n";
        i++;
    }//end buffer population
    std::cout << "Radar Scan started.\n";

    if (simulateFailure) { throw std::runtime_error("Radar hardware failure"); }
}//end of processRadarData()

//Part B
int main() {
    std::cout << "Welcome to E3.17.3 \n\n";
    try {
        processRadarScan(false);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

    try {
        processRadarScan(true);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << '\n';
    }

}//end of main

/* Bonus Q
Why does the destructor execute even though the function never reaches its normal exit?
--> Because, regardless of resource use or non-use, release must happen.  The alternative I imagine is an enormous pile of unfinished business and a lot of wastes memory.

What does stack unwinding mean?
--> Isnt that the "pop" phase?  The sequence of circling back to collect the plates from the buffet plate dispenser?

Does catch automatically repair the condition that caused the exception?
The venerable try/catch <--- I rememeber that.
--> I say emphatic "No", catch is the graceful failure.  Try it!  and if it breaks, print a nice message, but the engineer still has to debug and fix.  The catch just narrows the search for the root cause.

What happens if an exception is thrown but no matching handler is found?
--> Doesn't the language provide a default if no custom handler has been created?

Why is RAII preferable to manually placing delete statements along every possible exit path?
--> "manually placing delete statements along every possible exit path" just seems like a lot of juice for that squeeze.
Automation can be good in certain situations, likle when you need to be safe, but don't want to pay the "manual" price.

Leaner feedback:
This is great. Bro, I wish GPT was around during my undergrad days. You can't beat instant raw-intuition validation, or detailed correction.
I feel like concepts are bubbling back up or sticking better because the search space has been eliminated.  I haven't visited StackOverflow in years bro.
*/
//################# END E3.17.3 #################


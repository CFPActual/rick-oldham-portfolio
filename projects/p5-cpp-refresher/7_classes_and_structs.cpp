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

//################# E3.16.1 C++ Struct and Class #################
/* Notes
* struct RadarTarget {
	int id;
	double distance;
	bool detected;
};

RadarTarget target1{101, 250.5, true};

std::cout << target1.id;
std::cout << target1.distance;

class RadarSystem {
public:
	int targetCount = 0;

	void detectTarget() {
		++targetCount;
	}
};

Feature						struct		class
===============================================
Default member access		public		private
Default inheritance access	public		private

public means code outside the class can access those members.

*/

//struct RadarTarget {
//    int id;
//    double distance;
//    bool detection;
//};
//
//
//class RadarSystem {
//public:
//    int targetCount = 0;
//
//    void detectTarget() {
//        targetCount++;
//    }
//};
//
//
//int main() {
//	std::cout << "Welcome to E3.16.1 \n\n";
//
//    // Part A
//    RadarTarget target1{1, 42, true};
//    RadarTarget target2{2, 600, false};
//
//    std::cout << "Target 1 data: " << "TID: " << target1.id << " Distance: " <<target1.distance << " Detection: " << target1.detection << "\n";
//    std::cout << "Target 2 data: " << "TID: " << target2.id << " Distance: " <<target2.distance << " Detection: " << target2.detection << "\n";
//    target2.distance = 630;
//    std::cout << "Target 2 distance has been updated to: "  << target2.distance << "\n";
//
//    // Part B
//
//    RadarSystem myRadar;
//
//    for (int i = 0; i < 3; i++) { myRadar.detectTarget(); }
//
//    std::cout << "My radar target count: " << myRadar.targetCount << "\n";
//
//	/* Bonus ??
//    * What fundamental capability do struct and class share?  --> The ability to create a user defined type with custom instance variables
//      --> both struct and class can contain data and member functions, not just instance variables.
//
//    What does public control?  --> access to the class (functions, instance variables)
//
//    Why might grouping target data into a struct be preferable to maintaining separate arrays?  --> Because a struct isnt restricted to just one primitive type.  Arrays can only contain one type
//
//    Does creating two objects from the same class mean they share their ordinary data members?  -->  No, each instance has it's own
//	*/
//}
//################# END E3.16.1 #################


//################# E3.16.2 C++ Encapsulation: private, public & Getters/Setters #################
/* Notes
class RadarTarget {
private:
	double distance = 0.0;

public:
	void setDistance(double d) {
		if (d >= 0.0) {
			distance = d;
		}
	}

	double getDistance() const {
		return distance;
	}
};

Concept							Purpose
====================================================================================
private							Restrict direct access from outside the class
public							Expose the class's interface
Setter							Modify internal data through controlled logic
Getter							Retrieve internal data - should be set to const unless modifying in function
const after a member function	Promise not to modify the object's non-mutable state

RadarTarget target;

target.setDistance(250.5);
std::cout << target.getDistance();

*/
//Part A
//class RadarTarget {
//private:
//	int id = 0;
//	double distance = 0.0;
//	bool detected = 0;
//
//public:
//	int getID() const { return id; }
//
//	double getDistance() const { return distance; }
//
//	bool getDetection() const { return detected; }
//
////Part B
//	void setID(int id) {
//
//		if (id < 0) { std::cout << "ID must be a positive integer.\n"; return; }
//		this->id = id; 
//	}
//
//	void setDistance(double distance) { 
//		if (distance < 0) { std::cout << "Distance must be a positive.\n"; return; }
//		this->distance = distance; 
//	}
//
//	void setDetection(bool d) { 
//		if ((d == false) || (d == true)) { detected = d; }
//		else { std::cout << "Detected must be a boolean.\n"; return; }
//		
//	}
//
//};
//
////Part C
//
//int main() {
//	std::cout << "Welcome to E3.16.2 \n\n";
//
//	RadarTarget target1;
//	RadarTarget target2;
//
//	target1.setID(101);
//	target1.setDistance(200);
//	target1.setDetection(false);
//
//	target2.setID(102);
//	target2.setDistance(175);
//	target2.setDetection(true);
//
//	// Just to see the response "...blah blah blah is inaccessible
//	//std::cout << "Target A data: " << "TID: " << target1.id << " Distance: " << target1.distance << " Detection: " << target1.detected << "\n";
//	//std::cout << "Target B data: " << "TID: " << target2.id << " Distance: " <<target2.distance << " Detection: " << target2.detected << "\n";
//
//	std::cout << "Target A data: " << "TID: " << target1.getID() << " Distance: " << target1.getDistance() << " Detection: " << target1.getDetection() << "\n";
//	std::cout << "Target A data: " << "TID: " << target2.getID() << " Distance: " << target2.getDistance() << " Detection: " << target2.getDetection() << "\n";
//
//	target1.setDistance(-4);
//	target2.setID(-103);
//
//	std::cout << "Target A data: " << "TID: " << target1.getID() << " Distance: " << target1.getDistance() << " Detection: " << target1.getDetection() << "\n";
//	std::cout << "Target A data: " << "TID: " << target2.getID() << " Distance: " << target2.getDistance() << " Detection: " << target2.getDetection() << "\n";
//
//	/*Bonus
//	WARNING: "guessing" really means testing my intuition.  I have experienced OOP in Java, C++ and Python so there may be some "memory mixing" across languages, but then that's why we are here!  This is great!!
//	Why is private useful if getters and setters still provide access? -->  private restricts access by "external" entities, while still allowing internal access.
//
//	What's the difference between a const member function and a const object? --> A const object cannot be changed a const member function (guessing) enforces the no change policy for setter returns;
//
//	Can a private member function be called by another member function of the same class? -->  Yes, I belive so
//
//	Does encapsulation automatically make a class thread-safe? --> I dont think so, otherwise we would not need mutual exclusion or semaphores.  
//	
//	*/
//}
//################# END E3.16.2 #################

//################# E3.16.3 C++ Constructors & Object Initialization #################
/* Notes
what is a constructor - a special class member function that runs when an object is created.

class RadarTarget {
private:
	int id;
	double distance;

public:
	RadarTarget(int i, double d) {
		id = i;
		distance = d;
	}

	int getID() const { return id; }
	double getDistance() const { return distance; }
};

RadarTarget target1(101, 250.5);

Constructor rules:
Rule				Meaning
=========================================================
Name				Must match class name
Return type			None, not even void
Invocation			Automatic during object creation
Parameters			Allowed
Overloading			Multiple constructors allowed
Default constructor	Can create an object without argument
*/

////Part A
//class RadarTarget {
//private:
//	int id;
//	double distance;
//	bool detected;
//
//public:
//	RadarTarget(int i, double dist, bool d) {
//		id = i;
//		distance = dist;
//		detected = d;
//	} //end of constructor 1
//
////Part B
//	RadarTarget() {  // <-- the default constructor: call it with object label only n --> ()
//		id = 0;
//		distance = 0.0;
//		detected = false;
//	} //end of constructor 2
//
//	//Getters
//	int getID() const { return id; }
//	double getDistance() const { return distance; }
//	bool getDetection() const { return detected; }
//};//end of class
//
////Part C
//int main() {
//	std::cout << "Welcome to E3.16.3 \n\n";
//
//	RadarTarget target1(101, 250.5, true);
//	RadarTarget target2;
//
//	std::cout << "Target 1 data: " << "TID: " << target1.getID() << " Distance: " << target1.getDistance() << " Detection: " << target1.getDetection() << "\n";
//	std::cout << "Target 2 data: " << "TID: " << target2.getID() << " Distance: " << target2.getDistance() << " Detection: " << target2.getDetection() << "\n";
//
//	RadarTarget target3(202, 600.0, false);
//	std::cout << "Target 3 data: " << "TID: " << target3.getID() << " Distance: " << target3.getDistance() << " Detection: " << target3.getDetection() << "\n";
//
//	//Bonus test
//
//
//	/*Bonus Q
//	Why doesn't a constructor declare a return type?  
//	-->  It doesnt need to, the return type is the object itself.  by-design automatic return of the thing being instantiated? plus none is required😁 "not even void".
//
//	Can constructors be overloaded like ordinary functions?  
//	-->  Yes,  params can vary from 0 to enough to cover all instance variables, the function body can vary as well.  parameterized vs default is a good example.
//
//	What's the difference between initialization and assignment?  
//	-->  Initialization reserves the memory space for the declared variable, assigment applies a value.  If that's true, statements like int one = 1; are two-fers.
//	--> Initialization establishes an object's initial value; assignment changes an already-initialized object
//
//	What happens if you define only a parameterized constructor and attempt to create an object without arguments?  
//	-->  If the object has instance variables (default characterics for an object) it will use the defaults.  Otherwise I believe the IDE will be angry.
//	As soon as I commented out the default constructor target2 got the squiggly --> "RadarTarget': no appropriate default constructor available"
//	*/
//} //End of Main()
//################# END E3.16.3 #################

//################# E3.16.4 C++ Constructor Initializer Lists #################
/* Notes Hoarding🤣
Traditional Obj Init
====================
class RadarTarget {
private:
	int id;
	double distance;
	int foo;
	bool blah;


public:
	RadarTarget(int i, double d) {
		id = i;
		distance = d;
	}
};

Obj Init with Initializer Lists
===============================
class RadarTarget {
private:
	int id;
	double distance;

public:
	RadarTarget(int i, double d)
		: id(i), distance(d) { --> Important: Members initialize in their "class" declaration order, regardless of their order in the initializer list. auto enforced
	}
};

Approach					Behavior
====================================================================
Constructor body assignment	Members initialized first, then assigned
Member initializer list		Members initialized directly
const data member			Must be initialized
Reference data member		Must be bound during initialization

const means an object cannot be modified through that const-qualified access. It doesn't necessarily mean the underlying value can never change.
*/

//Part B
class RadarConfig {
private:
	const int maxTargets;
	int& activeTargets;

public:
	RadarConfig(const int m, int& a) :
		maxTargets(m), activeTargets(a) {
	} // end of parameterized initializer list constructor


   //Getters
	const int getMaxTargets() const { return maxTargets; }
	int& getActiveTargets() const { return activeTargets; }
}; // end of class RadarConfig

//Part A
class RadarTarget {
private:
	int id;
	double distance;
	bool detected;

public:
	//Extra Crispy!
	RadarTarget(int i, double di, bool de) :
		id(i), distance(di), detected(de) {
	}//end of initializer list paramerterized constructor

	RadarTarget() :
		id(0), distance(0.0), detected(false) {
	}//end of initializer list default constructor

   //Traditional
   //RadarTarget(int id, double distance, bool detected) {
   //	this->id = id;
   //	this->distance = distance;
   //	this->detected = detected;
   //}// end of traditional parameterized constructor

   //RadarTarget() {
   //	id = 0;
   //	distance = 0.0;
   //	detected = false;
   //} //end of traditional default constructor 

   //Getters
	int getID() const { return id; }
	double getDistance() const { return distance; }
	bool getDetection() const { return detected; }
}; // end of class RadarTarget

int main() {
	std::cout << "Welcome to E3.16.4 \n\n";

	RadarTarget target1;
	RadarTarget target2(101, 250.5, true);

	std::cout << "Target 1 data: " << "TID: " << target1.getID() << " Distance: " << target1.getDistance() << " Detection: " << target1.getDetection() << "\n";
	std::cout << "Target 2 data: " << "TID: " << target2.getID() << " Distance: " << target2.getDistance() << " Detection: " << target2.getDetection() << "\n";

	//Part B - cont
	int active = 5;
	RadarConfig config1(100, active);

	std::cout << "Config 1 data: " << "Max Targets: " << config1.getMaxTargets() << " Distance: " << config1.getActiveTargets() << "\n";
	active = 10;
	std::cout << "Config 1 data: " << "Max Targets: " << config1.getMaxTargets() << " Distance: " << config1.getActiveTargets() << "\n";


	//Bonus test

	/*Bonus Q
	Why must const and reference members use initialization rather than later assignment?
	--> I assume because the "constant" values have to be established up front; const and reference both imply a value is already assigned.

	Does an initializer list execute before or after the constructor body?
	--> I assume (related to Q1) the values have to be in memory "somewhere" before they can be applied to the instance vars.

	If initializer-list order differs from member declaration order, which determines actual initialization order?
	--> I learned from QQ that "C++ automatically enforces class declaration order during member initialization"

	Why might direct member initialization be more efficient than assignment inside the constructor?
	--> Fewer instructions: direct == do it now (the two-fer?) vs instantiate then assign?
	*/
} //End of Main()
//################# END E3.16.4 #################

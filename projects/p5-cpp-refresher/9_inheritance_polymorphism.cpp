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

//################# E3.18.1 C++ Inheritance: Base & Derived Classes #################
/* Notes
class RadarTarget {
protected:
    int id;

public:
    RadarTarget(int i) : id(i) {}

    int getID() const {
        return id;
    }
};

class Aircraft : public RadarTarget {
private:
    double altitude;

public:
    Aircraft(int i, double a)
        : RadarTarget(i), altitude(a) {}

    double getAltitude() const {
        return altitude;
    }
};

Aircraft target1(101, 35000);

std::cout << target1.getID();       // 101
std::cout << target1.getAltitude(); // 35000

<-- class Aircraft inherits class RadarTarget's accessible interface (anything public) and adds aircraft-specific functionality.
Aircraft cannot directly access RadarTarget's private members unless public getters and setters are engaged.  ()

protected in RadarTarget controls access to its members.
public inheritance lets Aircraft inherit those accessible members without changing their access level.
public: inside Aircraft makes its own declared members accessible from outside.

Access					private	 protected
==========================================
Same class				✅		 ✅
Derived (child) class	❌		 ✅
Outside code			❌		 ❌

Access modifier		Same class	Derived class						Outside code
================================================================================
public				Yes			Yes									Yes
protected			Yes			Yes									No
private				Yes			No direct access(super public G/S)	No
<-- Derived classes can indirectly access private data through accessible superclass functions (e.g., public/protected getters and setters).
<-- Access rules apply to both member variables and member functions.
*/
//Part A
//class RadarTarget {
//protected:
//    int id;
//    double distance;
//
//
//public:
//    RadarTarget(int i, double d) :
//        id(i), distance(d)
//    {
//        std::cout << "constructing RadarTarget object\n\n";
//    }//end of class RadarTarget constructor
//
//    //Getters and Setters
//    int getID() const { return id; }
//    double getDistance() const { return distance; }
//
//    void setID(int i) { id = i; }
//    void setDistance(double d) { distance = d; }
//
//    //Helpers
//    void dispalyInfo() {
//        std::cout << "Target ID is " << id << ".\n";
//        std::cout << "Target distance is " << distance << ".\n";
//    }//end of dispalyInfo()
//
//};//end of calass RadarTarget
//
//
////Part B
//class Aircraft : public RadarTarget {
//private:
//    double altitude;
//
//public:
//    Aircraft(int i, double d, double a) :
//        RadarTarget(i, d), altitude(a) 
//    {
//        std::cout << "constructing Aircraft object\n\n";
//    }//class Aircraft constructor
//
//
//   //Getters and Setters
//    double getAltitude() const { return altitude; }
//
//    //Helpers
//    void dispalyAircraftInfo() {
//        std::cout << "Target ID is " << id << ".\n";
//        std::cout << "Target distance is " << distance << ".\n";
//        std::cout << "Aircraft altitude is " << altitude << ".\n";
//    }//end of dispalyAircraftInfo()
//
//};//end of class Aircraft
//
////Part C
//int main() {
//	std::cout << "Welcome to E3.18.1 \n\n";
//
//    RadarTarget target1(101, 250.5);
//    Aircraft aircraft1(202, 600.0, 35000);
//
//    target1.dispalyInfo();
//    aircraft1.dispalyAircraftInfo();
//    aircraft1.dispalyInfo();
//
//    std::cout << "\nAircraft altitude is still " << aircraft1.getAltitude() << ".\n";
//}//end of main

/*  Bonus Q
*
Why can Aircraft access protected members but ordinary outside code cannot?
--> because RadarTarget was declared protected not private, which allows direct access without the need for getters/setters.
--> if Radartarget memmbers were private, then getters/setters would nbe required.

Does an Aircraft object contain a RadarTarget base-class portion?
--> Yes, target ID and distance: either through a RadarTarget instantiation, or an Aircraft instantiation

Which constructor executes first: base or derived?
--> Base
Can Aircraft use inherited public methods without redefining them?
--> Yes
What's the difference between inheritance and composition (an object containing another object as a member)?
--> Seems like inheritance is automatic, but composition has to be "built".  Oh yeah Q bro just reminded me of "IS-A/HAS-A"
*/
//################# END E3.18.1 #################

//################# E3.18.2 C++ Virtual Functions & Runtime Polymorphism #################
/* Notes
class RadarTarget {
public:
    virtual void identify() const {
        std::cout << "Generic radar target\n";
    }

    virtual ~RadarTarget() = default;
};

class Aircraft : public RadarTarget {
public:
    void identify() const override {
        std::cout << "Aircraft detected\n";
    }
};

Keyword				Purpose
====================================================================================
virtual				Enable runtime dispatch through a base-class pointer/reference
override			Verify that a derived function overrides a virtual base function
<-- override is optional but recommended whenever a derived function overrides a virtual base function. It enables compiler verification without changing runtime behavior.
<-- Pure virtual: Implementation required for a concrete derived class; override keyword still optional.
= default			Request a compiler-generated implementation
virtual destructor	Enable safe deletion through a base-class pointer

Polymorphism at work (under the hood)
================================================
RadarTarget target;
Aircraft aircraft;

RadarTarget* ptr = &target;
ptr->identify();       // Generic radar target

ptr = &aircraft;
ptr->identify();       // Aircraft detected
<-- One base-class pointer can refer to different derived objects. Virtual dispatch selects the appropriate implementation.
*/

//Part A 
//class RadarTarget {
//protected:
//    int id;
//
//public:
//    RadarTarget(int i): 
//        id(i)
//    {}//end of constructor
//
//    virtual ~RadarTarget() {} //end of virtual destructor <-- Ensures the derived destructor also runs when deleting through a base-class pointer; enables proper cleanup through polymorphism.
//
//    //Helpers
//    virtual void identify() const { std::cout << "Generic Target ID is: " << id << "\n"; }  
//   //void identity() const { std::cout << "Generic Target ID is: " << id << "\n"; } // C++  is like "dispatch is gone bro, use the base function".
//
//}; //end of class RadarTarget
//
//
////Part B
//class Aircraft : public RadarTarget {
//public:
//    Aircraft(int i) :
//        RadarTarget(i) 
//    {}//end of class Aircraft constructor
//
//    //Helpers
//    virtual void identify() const override { std::cout << "Aircraft detetcted: " << "<" << id  <<">" << "\n"; }
//}; //end of class Aircraft
//
//class Ship : public RadarTarget {
//public:
//    Ship(int i) :
//        RadarTarget(i)
//    {} //end of class Ship constructor
//
//    //Helpers
//    virtual void identify() const override { std::cout << "Ship detetcted: " << "<" << id << ">" << "\n"; }
//
//};  //end of class Ship
//
//
////Part C
//int main() {
//    std::cout << "Welcome to E3.18.2 \n\n";
//
//    RadarTarget target1(100);
//    Aircraft aircraft1(200);
//    Ship ship1(300);
//
//    RadarTarget* ptr;
//
//    ptr = &target1;
//    ptr->identify();
//
//    ptr = &aircraft1;
//    ptr->identify();
//
//    ptr = &ship1;
//    ptr->identify();
//
//    std::vector<RadarTarget*> targetGroup = { &target1, &aircraft1, &ship1 };
//
//    for (RadarTarget* target:targetGroup) {
//         target->identify();
//    }
//}//end of main

/*  Bonus Q
*
Why does a base-class pointer successfully call a derived-class implementation?
--> I assume the virtual dispatch handles that.

What changes if virtual is removed from the base-class function?
--> The runtime dispatch capability is lost, so the base function will be used?

Why should a polymorphic base class generally have a virtual destructor?
--> I gathered "generally Yes, from Q bro.  Derived object deletion seems to "require" a virtual destructor for dispatching.
<-- Virtual destructors aren't required for dispatch. They're needed for safe deletion through a base pointer.

Does override introduce polymorphism, or verify that overriding is correct?
--> verifies that overriding is correct . Polymorphism may create the necessity for a function overiding.

Can a base-class reference demonstrate runtime polymorphism just like a pointer?
--> I don't know bro.
<-- YES — Base-class references support runtime polymorphism too.
*/
//################# END E3.18.2 #################

//################# E3.18.3 C++ Abstract Classes & Pure Virtual Functions #################
/* Notes
class RadarTarget {
public:
    virtual void identify() const = 0;

    virtual ~RadarTarget() = default;
};

The = 0 makes identify() a pure virtual function.

Concept				Meaning
==================================================================
virtual				Enables runtime dispatch
= 0					Declares a pure virtual function
Abstract class		Cannot be instantiated directly
Concrete class		Can be instantiated
override			Compiler verifies correct overriding
<-- A class containing at least one pure virtual function is abstract.
*/

//Part A
class RadarTarget {
protected:
    int id;

public:
    RadarTarget(int i) :
        id(i) {
    } //end of constructor

    virtual void identify() const = 0;  // pure virtual function

    virtual ~RadarTarget() = default; /// virtual destructor

    int getID() const { return id; }

}; //end of class RadarTarget

//Part B

class Aircraft : public RadarTarget {
public:
    Aircraft(int i) :
        RadarTarget(i) {
    }//end of constructor

    virtual void identify() const override { std::cout << "Aircraft detetcted: " << "<" << id << ">" << "\n"; }
};//end of class Aircraft


class Ship : public RadarTarget {
public:
    Ship(int i) :
        RadarTarget(i) {
    }//end of constructor

    virtual void identify() const override { std::cout << "Ship detetcted: " << "<" << id << ">" << "\n"; }
};//end of class ship



//Part C
int main() {
    std::cout << "Welcome to E3.18.3 \n\n";

    Aircraft aircraft1(101);
    Ship ship1(202);

    std::vector<RadarTarget*> targetGroup = { &aircraft1, &ship1 };

    for (RadarTarget* target : targetGroup) {
        target->identify();
    }
    //RadarTarget target1(303);

}//end of main

/*  Bonus Q
*
Why can't an abstract class be instantiated directly?
--> becasuse it's abstract, it has no definition no {do stuff}

Must every derived class override every inherited pure virtual function to become concrete?
--> I think I just learned the answer is Yes plus this response to my QC solidifies it.
--> "Mandatory to make the derived class concrete."

Can an abstract class contain ordinary implemented functions?
Of course, doesnt a getter count as an ordinary function.

Can an abstract class have a constructor?
--> Yes, RadarTarget in 3.18.3 does.

How is an abstract class different from an ordinary base class with virtual functions?
--> The abstract class has atleast one "pure" virtual funtion.  3.18.2 had virtuals but none were "pure" virtual.
--> abstract has no definition.  I guess it's main purpose is to enforce the signature.
*/
//################# END E3.18.3 #################


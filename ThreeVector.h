// @author: Christian Weber for Phys 678 Homework 9 Problem 1
// Created on Wed Apr 20 16:55:20 2016

/*

ThreeVector.h

Contains the delerations of the ThreeVector class

ThreeVector - A class that implements (real valued) three component vectors in C++

*/
#ifndef ThreeVector_h
#define ThreeVector_h
#include <iostream> // for cin, cout
#include <cmath> 
// class decleration
template <typename aType>
class ThreeVector{
private:
	// these are the three private variables that hold the three elements of the vector
	aType mx, my, mz;

public:
	////constructors
	ThreeVector();	//default constructor
	ThreeVector(aType x, aType y, aType z); 	// set constructor
	ThreeVector(const ThreeVector &copyMeVector); //copy constructor

	//Destructor
	//~ThreeVector();

	//// access members
	//return each element of the vector individually
	//since none of these methods are changing anything, we make it explicit by declaring them as const. This will also allow us to use them on a ThreeVector instance that has been declared as constant 
	
	aType x()const; //return x component of 3 vector
	aType y()const; //return y component of 3 vector
	aType z()const; //return z component of 3 vector

	aType mag()const; //return the magnitude of the vector
	aType phi()const; //return the azimuthal angle of the vector in the xy plane
	aType theta()const; //return the polar angle of the vector
	aType perp()const; //return the transverse (to z) component of the vector
	
	//output operator
	template<typename bType>
	friend std::ostream& operator<<(std::ostream& os, const ThreeVector<bType>& vOut);
	//http://stackoverflow.com/questions/4660123/overloading-friend-operator-for-template-class

	//// set members
	//set each element of the vector individually
	void setX(aType val); //set x component of 3 vector
	void setY(aType val); //set y component of 3 vector
	void setZ(aType val); //set z component of 3 vector

	//Assignment Operator
	ThreeVector operator=(const ThreeVector& assignMeVector);


};


#endif

////constructors

template<typename aType>  		//default constructor
ThreeVector<aType>::ThreeVector(){mx=0; my=0; mz=0;}
template<typename aType> 		// set constructor
ThreeVector<aType>::ThreeVector(aType x, aType y, aType z){mx=x; my=y; mz=z;} 
template<typename aType> 		//copy constructor
ThreeVector<aType>::ThreeVector(const ThreeVector &copyMeVector){ mx=copyMeVector.x(); my=copyMeVector.y(); mz=copyMeVector.z();}
//unless the methods .x, .y, .z are also declared as constant, we will get an error here.

////Destructor
//ThreeVector::~ThreeVector(){}


//// access methods
//return each element of the vector individually

template <typename aType>
aType ThreeVector<aType>::x()const{return mx;} //return x component of 3 vector
template <typename aType>
aType ThreeVector<aType>::y()const{return my;} //return y component of 3 vector
template <typename aType>
aType ThreeVector<aType>::z()const{return mz;} //return z component of 3 vector


template <typename aType>
aType ThreeVector<aType>::mag()const{return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));} //return the magnitude of the vector
template <typename aType> 
aType ThreeVector<aType>::phi()const{return atan2(y(),x());} //return the azimuthal angle of the vector in the xy plane
template <typename aType> 
aType ThreeVector<aType>::theta()const{ return acos(z()/mag());} //return the polar angle of the vector
template <typename aType> 
aType ThreeVector<aType>::perp()const{return sqrt(pow(x(),2)+pow(y(),2));} //return the transverse (to z) component of the vector

template <typename aType> 
std::ostream& operator<<(std::ostream& os, const ThreeVector<aType>& vOut){
	os << vOut.x() <<"\t"<< vOut.y() <<"\t"<< vOut.z();
	return os;}


//// set set methods
//set each element of the vector individually
template <typename aType>
void ThreeVector<aType>::setX(aType val){mx = val;} //set y component of 3 vector
template <typename aType>
void ThreeVector<aType>::setY(aType val){my = val;} //set y component of 3 vector
template <typename aType>
void ThreeVector<aType>::setZ(aType val){mz = val;} //set z component of 3 vector

//Assignment Operator
template <typename aType>
ThreeVector<aType> ThreeVector<aType>::operator=(const ThreeVector& assignMeVector){ mx=assignMeVector.x(); my=assignMeVector.y(); mz=assignMeVector.z();
return *this;}//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.
//NOTE, assigments are right now only between ThreeVector<aType> of the same <aType> supported

////in case the method implementations are in a seperate .cxx file (i.e. seperate from the .h file)
// instantiate the ThreeVector class for the types that I expect to use -- I don't wanna write everything into the .h file, despite that being the other recommended solution to the otherwise extant linking problem
// see here for an explanation and example solutions to the problem -- https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//template class ThreeVector<double>;
//template class ThreeVector<int>;

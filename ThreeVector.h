// @author: Christian Weber for Phys 678 Homework 9 Problem 1
// Created on Wed Apr 20 16:55:20 2016

/*

ThreeVector.h

Contains the delerations of the ThreeVector class

ThreeVector - A class that implements (real valued) three component vectors in C++

*/
#ifndef ThreeVector_h
#define ThreeVector_h

// class delceration
class ThreeVector{
private:
	// these are the three private variables that hold the three elements of the vector
	double mx, my, mz;

public:
	////constructors
	//default constructor
	ThreeVector();
	// set constructor
	ThreeVector(double x, double y, double z);
	//copy constructor
	ThreeVector(const ThreeVector &copyMeVector);

	//Destructor
	~ThreeVector();

	//// access members
	//return each element of the vector individually
	//since none of these methods are changing anything, we make it explicit by declaring them as const. This will also allow us to use them on a ThreeVector instance that has been declared as constant 
	double x()const; //return x component of 3 vector
	double y()const; //return y component of 3 vector
	double z()const; //return z component of 3 vector

	double mag()const; //return the magnitude of the vector
	double phi()const; //return the azimuthal angle of the vector in the xy plane
	double theta()const; //return the polar angle of the vector
	double perp()const; //return the transverse (to z) component of the vector


	//// set members
	//set each element of the vector individually
	void setX(double val); //set x component of 3 vector
	void setY(double val); //set y component of 3 vector
	void setZ(double val); //set z component of 3 vector

	//Assignment Operator
	ThreeVector operator=(const ThreeVector& assignMeVector);

};

#endif

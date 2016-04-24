// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations
// Created on Wed Apr 20 16:51:34 2016

/*
ThreeVector.cxx

ThreeVector - A class that implements (real valued) three component vectors in C++

*/

//load our own files that we need
#include "ThreeVector.h"

//load the packages that we need
#include <iostream> // for cin, cout
#include <cmath> 
//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;

////constructors
//default constructor
ThreeVector::ThreeVector(){	setX(0); setY(0); setZ(0);}
// set constructor
ThreeVector::ThreeVector(double x, double y, double z){setX(x); setY(y); setZ(z);}
//copy constructor
ThreeVector::ThreeVector(const ThreeVector &copyMeVector){ setX(copyMeVector.x()); setY(copyMeVector.y()); setZ(copyMeVector.z());}
//unless the methods .x, .y, .z are also declared as constant, we will get an error here.

////Destructor
ThreeVector::~ThreeVector(){}


//// access methods
//return each element of the vector individually
double ThreeVector::x()const{return mx;} //return x component of 3 vector
double ThreeVector::y()const{return my;} //return y component of 3 vector
double ThreeVector::z()const{return mz;} //return z component of 3 vector

double ThreeVector::mag()const{return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));} //return the magnitude of the vector
double ThreeVector::phi()const{return atan2(y(),x());} //return the azimuthal angle of the vector in the xy plane
double ThreeVector::theta()const{ return acos(z()/mag());} //return the polar angle of the vector
double ThreeVector::perp()const{return sqrt(pow(x(),2)+pow(y(),2));} //return the transverse (to z) component of the vector

std::ostream& operator<<(std::ostream& os, const ThreeVector& vOut){
	os << vOut.x() <<"\t"<< vOut.y() <<"\t"<< vOut.z();
	return os;
}


//// set set methods
//set each element of the vector individually
void ThreeVector::setX(double val){mx = val;} //set y component of 3 vector
void ThreeVector::setY(double val){my = val;} //set y component of 3 vector
void ThreeVector::setZ(double val){mz = val;} //set z component of 3 vector

//Assignment Operator
ThreeVector ThreeVector::operator=(const ThreeVector& assignMeVector){ setX(assignMeVector.x()); setY(assignMeVector.y()); setZ(assignMeVector.z());
return *this;}//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.

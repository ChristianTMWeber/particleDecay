// @author: Christian Weber for Phys 678 Final Project
//Created on Wed May 04 10:44:30 2016

/*

VectorTestFunctions.h

Functions that help me to assert the correct working of he ThreeVector and LorentzVector classes.

Made for ThreeVectorTest.cxx and LorentzVectorTest.cxx

*/

//load our own files that we need

//load the packages that we need
#include <iostream> // for cin, cout
#include <fstream>
#include <cmath> 
#include <string> 
#include <sstream> 


//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;

#ifndef VectorTestFunctions_h
#define VectorTestFunctions_h
////functions that makes it easier to compare vectors

// things to print for passed/failed tets
void testPassed(int const &n);
void testFailed(int const &n);





//declaration for ThreeVector of type double
void allElementsEqual(  const int &n,const ThreeVector &vA, const ThreeVector &vB);
void allElementsUnequal(const int &n,const ThreeVector &vA, const ThreeVector &vB);

void vectorsEqualWithinAccucary(const int &n,const ThreeVector &vA, const ThreeVector &vB);




//declaration for scalar of type int
void allElementsEqual(  const int &n,const  int &sA, const int &sB);

//declaration for scalar of type bool
void allElementsEqual(  const int &n,const  bool &sA, const bool &sB);

//declaration for scalar of type double
void allElementsEqual(  const int &n,const  double &sA, const double &sB);
void vectorsEqualWithinAccucary(const int &n,const double sA, const double sB);

#endif

////functions that makes it easier to compare vectors

// things to print for passed/failed tets
void testPassed(int const &n){cout << "Test\t"<<n<<"\tpassed!"<< endl;}
void testFailed(int const &n){cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}


/*
void vectorsEqualWithinAccucary(const int &n,const LorentzVector &vA, const LorentzVector &vB){
	double precision = 5E-16;
	if( abs(vA-vB)/abs(vA)<precision ) 
		{testPassed(n);}
	else{testFailed(n);}	}
*/

//definition for ThreeVector of type <double>
void allElementsEqual(const int &n,const ThreeVector &vA, const ThreeVector &vB){
	if((vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z())) 
		{testPassed(n);}
	else{testFailed(n);}	}

void allElementsUnequal(const int &n,const ThreeVector &vA, const ThreeVector &vB){
	if((vA.x()!=vB.x())&&(vA.y()!=vB.y())&&(vA.z()!=vB.z())) 
		{testPassed(n);}
	else{testFailed(n);}	}

void vectorsEqualWithinAccucary(const int &n,const ThreeVector &vA, const ThreeVector &vB){
	double precision = 5E-16;
	if( abs(vA-vB)/abs(vA)<precision ) 
		{testPassed(n);}
	else{testFailed(n);}	}


//declaration for scalar of type int
void allElementsEqual(  const int &n,const  int &sA, const int &sB){
	if(sA==sB)
		{testPassed(n);}
	else{testFailed(n);}	}

//declaration for scalar of type bool
void allElementsEqual(  const int &n,const  bool &sA, const bool &sB){
	if(sA==sB) 
		{testPassed(n);}
	else{testFailed(n);}	}

//declaration for scalar of type double
void allElementsEqual(  const int &n,const  double &sA, const double &sB){
	if(sA==sB) 
		{testPassed(n);}
	else{testFailed(n);}	}

void vectorsEqualWithinAccucary(const int &n,const double sA, const double sB){
	double precision = 5E-16;
	if( abs(sA-sB)/abs(sA)<precision ) 
		{testPassed(n);}
	else{testFailed(n);}	}

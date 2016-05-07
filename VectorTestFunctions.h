// @author: Christian Weber for Phys 678 Final Project
//Created on Wed May 04 10:44:30 2016

/*

VectorTestFunctions.h

Functions that help me to assert the correct working of he ThreeVector and LorentzVector classes.

Made for ThreeVectorTest.cxx and LorentzVectorTest.cxx

*/

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


//declaration for LorentzVector of type double
void allElementsEqual(  const int &n,const LorentzVector &vA, const LorentzVector &vB);
void allElementsUnequal(const int &n,const LorentzVector &vA, const LorentzVector &vB);


//declaration for ThreeVector of type double
void allElementsEqual(  const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB);
void allElementsUnequal(const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB);

void vectorsEqualWithinAccucary(const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB);


//declaration for ThreeVector of type int
void allElementsEqual(  const int &n,const ThreeVector<int> &vA, const ThreeVector<int> &vB);
void allElementsUnequal(const int &n,const ThreeVector<int> &vA, const ThreeVector<int> &vB);

//declaration for scalar of type int
void allElementsEqual(  const int &n,const  int &sA, const int &sB);

//declaration for scalar of type bool
void allElementsEqual(  const int &n,const  bool &sA, const bool &sB);

//declaration for scalar of type double
void allElementsEqual(  const int &n,const  double &sA, const double &sB);
void vectorsEqualWithinAccucary(const int &n,const double sA, const double sB);

#endif


////functions that makes it easier to compare vectors

//definition for LorentzVector (of type double anyway)
void allElementsEqual(const int &n,const LorentzVector &vA, const LorentzVector &vB){
	if((vA.t()==vB.t())&&(vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

void allElementsUnequal(const int &n,const LorentzVector &vA, const LorentzVector &vB){
	if((vA.t()!=vB.t())&&(vA.x()!=vB.x())&&(vA.y()!=vB.y())&&(vA.z()!=vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}


//definition for ThreeVector of type <double>
void allElementsEqual(const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB){
	if((vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

void allElementsUnequal(const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB){
	if((vA.x()!=vB.x())&&(vA.y()!=vB.y())&&(vA.z()!=vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

void vectorsEqualWithinAccucary(const int &n,const ThreeVector<double> &vA, const ThreeVector<double> &vB){
	double accuracy = 3E-15;
	if( abs(vA-vB)<accuracy ) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}


//definition for ThreeVector of type <int>
void allElementsEqual(const int &n,const ThreeVector<int> &vA, const ThreeVector<int> &vB){
	if((vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

void allElementsUnequal(const int &n,const ThreeVector<int> &vA, const ThreeVector<int> &vB){
	if((vA.x()!=vB.x())&&(vA.y()!=vB.y())&&(vA.z()!=vB.z())) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

//declaration for scalar of type int
void allElementsEqual(  const int &n,const  int &sA, const int &sB){
	if(sA==sB)
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

//declaration for scalar of type bool
void allElementsEqual(  const int &n,const  bool &sA, const bool &sB){
	if(sA==sB) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

//declaration for scalar of type double
void allElementsEqual(  const int &n,const  double &sA, const double &sB){
	if(sA==sB) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}

void vectorsEqualWithinAccucary(const int &n,const double sA, const double sB){
	double accuracy = 3E-15;
	if( abs(sA-sB)<accuracy ) 
		{cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}	}
// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations
// Created on Wed Apr 20 17:01:35 2016

/*
ThreeVectorTest.cxx

Tests the ThreeVector class which implements real three element vectors in C++

*/

//load our own files that we need
#include "ThreeVector.h"

//load the packages that we need
#include <iostream> // for cin, cout
#include <cmath> 
//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;

//declarations for functions that we want to use

void allElementsEqual(  const int &n,const ThreeVector &vA, const ThreeVector &vB);
void allElementsUnequal(const int &n,const ThreeVector &vA, const ThreeVector &vB);

int main(int argc, char *argv[]) {
	const double pi = 3.141592653589793;
	const double lim = 1E-15;
	int n=0;

	cout << "Begin ThreeVectorTest" << endl;

	//create an vector using the default constructor
	ThreeVector v1;
	//check the default constructor
	n=1;
	if((v1.x()==0)&&(v1.y()==0)&&(v1.z()==0)) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//create an vector using the default constructor
	ThreeVector v2(1,2,3);
	//check the set constructor
	n=2;
	if((v2.x()==1)&&(v2.y()==2)&&(v2.z()==3)) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//check the set method
	n=3;
	v1.setX(4);		v1.setY(5);		v1.setZ(6);
	if((v1.x()==4)&&(v1.y()==5)&&(v1.z()==6)) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//check the copy constructor
	n=4;
	ThreeVector v3(v1);
	allElementsEqual(n,v1,v3);
	//check that we actually copied the vector v1, and not only references the elements of v3 to the locations of the elements of v1
	n=5;
	v3.setX(7);		v3.setY(8);		v3.setZ(9);
	allElementsUnequal(n,v1,v3);
	//Check Assignment Operator
	n=6;
	ThreeVector v6;
	v6=v3;
	allElementsEqual(n,v3,v6);
	//check that we actually assign the vector v6, and not only references the elements of v3 to the locations of the elements of v6
	n=7;
	v6.setX(2*v6.x());		v6.setY(2*v6.y());		v6.setZ(2*v6.z());
	allElementsUnequal(n,v3,v6);
	//What happens if we self reference? Nothing should happen. 
	n=8;
	ThreeVector v8;
	v8=v6;		v6=v6;
	allElementsEqual(n,v6,v6);
	//test the magnitude method
	n=9;
	ThreeVector v9a(1,2,2), v9b(4,4,4);
	if((v9a.mag()==3)&&(v9b.mag()==sqrt(3*16))) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//test the phi method
	n=10;
	ThreeVector v10a(1,0,0), v10b(0,1,0), v10c(1,1,0), v10d(0,-1,0), v10e(-23,-6,0);
	if((v10a.phi()==0)&&(v10b.phi()==pi/2)&&(v10c.phi()==pi/4)&&(v10d.phi()==-pi/2)&&(v10e.phi()==atan2(-6,-23))) {cout << "Test "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//test the theta method
	n=11;
	ThreeVector v11a(1,0,0), v11b(0,0,1), v11c(0,1,1), v11d(0,2,2), v11e(0,-6,79);
	if( (    v11a.theta()==pi/2)&&
		(    v11b.theta()==0)&&
		(abs(v11c.theta()-pi/4) < lim) &&
		(abs(v11d.theta()-pi/4) < lim) &&
		(    v11e.theta()==acos(79/sqrt(pow(-6,2)+pow(79,2))))
		){cout << "Test "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
	//test the perp method
	n=12;
	ThreeVector v12(4,3,980708);
	if( v12.perp()==5){cout << "Test "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}

	cout << abs( -1*(v11c.theta()-pi/4)) <<"   " << 1E-5<< endl;
//    &&(v11d.theta()==-pi/2&&(v11e.theta()==atan2(-6,-23))

}

//	cout << v3.x()<< " "<< v3.y()<< " "<< v3.z()<< " "<<endl;
//	cout << v6.x()<< " "<< v6.y()<< " "<< v6.z()<< " "<<endl;


void allElementsEqual(const int &n,const ThreeVector &vA, const ThreeVector &vB){
	if((vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z())) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
}
void allElementsUnequal(const int &n,const ThreeVector &vA, const ThreeVector &vB){
	if((vA.x()!=vB.x())&&(vA.y()!=vB.y())&&(vA.z()!=vB.z())) {cout << "Test  "<<n<<" passed!"<< endl;}
	else{cout << "Test  "<<n<<" FAILED!"<< endl;}
}

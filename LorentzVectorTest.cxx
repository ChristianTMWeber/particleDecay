// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations
// Created on Sun May 01 17:29:31 2016

/*
ThreeVectorTest.cxx

Tests the TreeVector class which implements real three element vectors in C++

*/

//load our own files that we need
#include "ThreeVector.h"
#include "LorentzVector.h"
#include "VectorTestFunctions.h"
//#include "LorentzVector.h"
//load the packages that we need
#include <iostream> // for cin, cout
#include <fstream>
#include <cmath> 
#include <string> 
#include <sstream> 
//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;


//// commence the testing 
int main(int argc, char *argv[]) {
	cout << "Begin LorentzVector Test" << endl;
	
	//create a vector using the default constructor
	int n;
	
	//check the default constructor and the methods to get the t,x,y, and z components
	LorentzVector v1;
		
	n=1;
	if((v1.t()==0)&&(v1.x()==0)&&(v1.y()==0)&&(v1.z()==0)) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//check the set method
	n=2;
	v1.setT(3);		v1.setX(4);		v1.setY(5);		v1.setZ(6);
	if((v1.t()==3)&&(v1.x()==4)&&(v1.y()==5)&&(v1.z()==6)) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}
	
	//check the set constructor (4 scalars)
	n=3;
	LorentzVector v2(3,4,5,6);
	
	allElementsEqual(n,v1,v2);
	
	//check the set constructor (ThreeVector - scalar)
	n=4;
	ThreeVector<double> t4(4,5,6);
	double s4=3;
	LorentzVector v4(t4,s4);
	allElementsEqual(n,v4,v2);
	
	//check the set constructor (scalar - ThreeVector)
	n=5;
	LorentzVector v5(s4,t4);
	allElementsEqual(n,v5,v2);
	
	//check the copy constructor
	n=6;
	LorentzVector v6(v2);
	allElementsEqual(n,v6,v2);
	
	//check the assignment operator
	n=7;
	LorentzVector v7;
	v7 = v2;
	allElementsEqual(n,v7,v2);
	
	//check that my two sets of set methods are doing the same
	n=8;
	LorentzVector v8a,v8b;
	double s8a = 2, s8b=3, s8c=5, s8d=7;
	
	v8a.setE(s8a); v8a.setPx(s8b); v8a.setPy(s8c); v8a.setPz(s8d);
	v8b.setT(s8a); v8b.setX(s8b) ; v8b.setY(s8c) ; v8b.setZ(s8d) ;
	
	allElementsEqual(n,v8a,v8b);
	
	//check that my two sets of get methods are doing the same 
	n=9;

	if((v8a.t()==v8a.E())&&(v8a.x()==v8a.px())&&(v8a.y()==v8a.py())&&(v8a.z()==v8a.pz())) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}
	
	// check that .setVect works
	n=10;
	ThreeVector<double> t10(-9,-7,-5);
	LorentzVector v10a(0,t10), v10b;
	v10b.setVect(t10);
	
	allElementsEqual(n,v10a,v10b);
	
	//checl that .vect works
	n=11;
	ThreeVector<double> t11 = v10a.vect();
	
	allElementsEqual(n,t11,t10);
	
	//check .mag
	n=12;
	LorentzVector  v12(3,2,1,0);
	double s12target = 2, s12;
	s12=v12.mag();
	vectorsEqualWithinAccucary(n,s12target,v12.mag());
	
	//and the .mass
	n=13;
	double s13 = v12.mass();
	vectorsEqualWithinAccucary(n,s12target,v12.mass());
	
	//and abs(LorentzVector)
	n=14;
	double s14 = abs(v12);
	vectorsEqualWithinAccucary(n,s12target,abs(v12));
	
	// check the == operator true state 
	n=15;
	LorentzVector v15(79,31,52,17);
	allElementsEqual(n,v15==v15,true);
	
	// check the == operator false state 
	n=16;
	LorentzVector v16=v15;	v15.setT(-15);
	allElementsEqual(n,v15==v16,false);
	
	// check the != operator true state 
	n=17;
	allElementsEqual(n,v15!=v16,true);
	
	// check the != operator false state 
	n=18;
	allElementsEqual(n,v15!=v15,false);

	//check <<, and >> operator for file streams
	n=19;
	
	ofstream ofs19("LorentzVectorTest19.txt");
	ifstream ifs19("LorentzVectorTest19.txt");
	LorentzVector v19out(60,27,65,69),v19in;

	ofs19 << v19out <<endl;
	ifs19 >> v19in;

	allElementsEqual(n,v19out,v19in);
	
	// double check using stringstream 
	n=20;
	LorentzVector v20(-75,46,9,24),v20in;
	
	stringstream stringStream20;
	
	stringStream20 << v20 << endl;
	stringStream20 >> v20in;

	allElementsEqual(n,v20,v20in);
	
	// test += operator
	n=21;
	LorentzVector v21(0,0,0,0);
	v21+=v20;
	allElementsEqual(n,v20,v21);
	
	// test *= operator
	n=22;
	LorentzVector v22a(0,0,0,0),v22b(0,0,0,0);
	v22a+=v20;	v22a+=v20;
	v22b+=v20;	v22b*=2;

	allElementsEqual(n,v22a,v22b);
	
	//test -= operator
	n=23;
	LorentzVector v23a(0,0,0,0);
	LorentzVector v23b=v23a;
	v23b += v20;
	v23b -= v20;

	allElementsEqual(n,v23a,v23b);
	
	//test /= operator
	n=24;
	LorentzVector v24a(1,2,4,8), v24b(2,4,8,16);
	v24b/=2;
	allElementsEqual(n,v24a,v24b);
	
	//test the + operator
	n=25;
	LorentzVector v25sum, v25summand;
	
	v25summand + v24a;
	cout << v25summand + v24a << endl;
	
	
	
	return 0;
	
}


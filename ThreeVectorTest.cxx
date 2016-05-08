// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations
// Created on Wed Apr 20 17:01:35 2016

/*
ThreeVectorTest.cxx

Tests the ThreeVector class which implements real three element vectors in C++

*/

//load our own files that we need
#include "ThreeVector.h"
#include "LorentzVector.h"
#include "VectorTestFunctions.h" // we are not calling this here, but the compiler needs to know that 'LorentzVector' is a viable type, to understand 'VectorTestFunctions.h', and it know this type from "VectorTestFunctions.h".

//load the packages that we need
#include <iostream> // for cin, cout
#include <fstream>
#include <cmath> 
#include <string> 
#include <sstream> 
//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;



//TEST
//implement the output operator overloading for the ThreeVector class
//ostream& operator<<(ostream& os, const ThreeVector& vOut);

int main(int argc, char *argv[]) {
	int n;

	cout << "Begin ThreeVectorTest" << endl;

	//create an vector using the default constructor
	ThreeVector<double> v1;
	ThreeVector<int> v1_int;
	//check the default constructor and the methods to get the x,y, and z components
	n=1;
	if((v1.x()==0)&&(v1.y()==0)&&(v1.z()==0)) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//check the set method
	n=2;
	v1.setX(4);		v1.setY(5);		v1.setZ(6);
	if((v1.x()==4)&&(v1.y()==5)&&(v1.z()==6)) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//check the set constructor
	n=3;
	ThreeVector<double> v2(1,2,3);
	if((v2.x()==1)&&(v2.y()==2)&&(v2.z()==3)) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//check the copy constructor
	n=4;
	ThreeVector<double> v3(v1);
	allElementsEqual(n,v1,v3);
	//check that we actually copied the vector v1, and not only references the elements of v3 to the locations of the elements of v1
	n=5;
	v3.setX(7);		v3.setY(8);		v3.setZ(9);
	allElementsUnequal(n,v1,v3);
	
	//Check Assignment Operator
	n=6;
	ThreeVector<double> v6;
	v6=v3;
	allElementsEqual(n,v3,v6);

	//check that we actually assign the vector v6, and not only references the elements of v3 to the locations of the elements of v6
	n=7;
	v6.setX(2*v6.x());		v6.setY(2*v6.y());		v6.setZ(2*v6.z());
	allElementsUnequal(n,v3,v6);

	//What happens if we self reference? Nothing should happen. 
	n=8;
	ThreeVector<double> v8;
	v8=v6;		v6=v6;
	allElementsEqual(n,v6,v6);

	//test the magnitude method
	n=9;
	ThreeVector<double> v9a(1,2,2), v9b(4,4,4);
	if((v9a.mag()==3)&&(v9b.mag()==sqrt(3*16))) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//test the phi method
	const double pi = 3.141592653589793;
	n=10;
	ThreeVector<double> v10a(1,0,0), v10b(0,1,0), v10c(1,1,0), v10d(0,-1,0), v10e(-23,-6,0);
	if((v10a.phi()==0)&&(v10b.phi()==pi/2)&&(v10c.phi()==pi/4)&&(v10d.phi()==-pi/2)&&(v10e.phi()==atan2(-6,-23))) 
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//test the theta method

	const double acc = 1E-15; // the numerical accuracy that I demand, if '==' fails while it shouldn'
	n=11;
	ThreeVector<double> v11a(1,0,0), v11b(0,0,1), v11c(0,1,1), v11d(0,2,2), v11e(0,-6,79);
	if( (    v11a.theta()==pi/2)&&
		(    v11b.theta()==0)&&
		(abs(v11c.theta()-pi/4) < acc) &&
		(abs(v11d.theta()-pi/4) < acc) &&
		(    v11e.theta()==acos(79/sqrt(pow(-6,2)+pow(79,2))))
		){cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}
	//test the perp method
	n=12;
	ThreeVector<int> v12(4,3,980708);
	if( v12.perp()==5)
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//test the output operator
	n=13;
	stringstream testStringStream, referenceStringStream;

	testStringStream 		<< v12;
	referenceStringStream	<< v12.x() <<"\t"<< v12.y() <<"\t"<< v12.z();

	if(testStringStream.str() == referenceStringStream.str() )
		{cout << "Test\t"<<n<<"\tpassed!"<< endl;}
	else{cout << "Test\t"<<n<<"\tFAILED!!"<< endl;}

	//test the += operator
	n=14;
	ThreeVector<int> v14(0,0,0);
	v14+=v12;
	allElementsEqual(n,v14,v12);

	//Test + operator
	n=15;
	ThreeVector<int> v15summand(0,0,0),v15sum(0,0,0),v15check(0,0,0);
	v15sum=v15summand+v14;
	allElementsEqual(n,v15sum,v14);

	//Test that v15summand did not change
	n=16;
	allElementsEqual(n,v15summand,v15check);

	//test the *= operator
	n=17;
	ThreeVector<int> v17=v12;
	v17*=2;
	allElementsEqual(n,v17,v12+v12);

	//Test * operator, specifically: vector*scalar
	n=18;
	ThreeVector<int> v18product(0,0,0), v18factor(95,-7,22);
	ThreeVector<int> v18Check = v18factor;
	int scalarFactor = 3;
	v18product = v18factor*scalarFactor;
	allElementsEqual(n,v18product,v18factor+v18factor+v18factor);

	//Test that v18factor did not change
	n=19;
	allElementsEqual(n,v18factor,v18Check);

	//Test * operator, specifically: scalar*vector
	n=20;
	ThreeVector<int> v20product(0,0,0), v20factor(-7,8,22);
	v20product = scalarFactor*v20factor;
	allElementsEqual(n,v20product,v20factor*=scalarFactor);

	//Test * operator, specifically: vector*scalar
	n=21;
	ThreeVector<int> v21product(0,0,0), v21factor(-4,81,2);
	v21product = v21factor*scalarFactor;
	allElementsEqual(n,v21product,v21factor*=scalarFactor);

	//test the -= operator
	n=22;
	ThreeVector<int> v22(0,0,0),v22subtrahend(9,-13,93);
	v22-=v22subtrahend;
	allElementsEqual(n,v22,v22subtrahend*(-1));

	//Test - operator
	n=23;
	ThreeVector<int> v23(0,0,0);
	v23=v22-v22subtrahend;
	allElementsEqual(n,v23,v22subtrahend*(-2));

	//Test /= operator
	n=24;
	ThreeVector<int> v24dividend(2,4,8), v24quotient(1,2,4);
	int divisor = 2;
	v24dividend/=divisor;
	allElementsEqual(n,v24dividend,v24quotient);

	//Test / operator
	n=26;
	ThreeVector<int> v25dividend(2,4,8), v25quotient;
	v25quotient = v25dividend/divisor;
	allElementsEqual(n,v25quotient,v24quotient);

	//Test unary + operator
	n=27;
	allElementsEqual(n,+v25quotient,v24quotient);

	//Test unary + operator
	n=28;
	ThreeVector<int> v28(0,0,0);
	allElementsEqual(n,-v24quotient,v28-v24quotient);

	//Test dot-product
	n=29;
	ThreeVector<int> v29(1,2,3);
	allElementsEqual(n,v29*v29,14);

	//Test abs() function
	n=30;
	ThreeVector<int> v30(1,2,2);
	allElementsEqual(n,abs(v30),3);

	//Test cross() method
	n=31;
	ThreeVector<int> v31c(8,3,6),v31b(-7,1,2),v31a(0,-58,29);
	allElementsEqual(n,v31c.cross(v31b),v31a);


	n=32;
	ThreeVector<int> v32a(1,2,3);
	ThreeVector<int> v32b(v32a[0],v32a[1],v32a[2]);
	allElementsEqual(n,v32a,v32b);

	//Test array subscriting -- value setting
	n=33;
	ThreeVector<int> v33(4,5,6);
	v32a[0]=v33.x(); 	v32a[1]=v33.y();	v32a[2]=v33.z();
	allElementsEqual(n,v32a,v33);

	//Test .rotateX method
	n=34;
	ThreeVector<double> v34(0,0,1), v34rotated,v34target(0,-1,0);
	v34rotated=v34.rotateX(pi/2);
	vectorsEqualWithinAccucary(n,v34rotated,v34target);

	//Test .rotateY method
	n=35;
	ThreeVector<double> v35(1,1,1), v35rotated,v35target(sqrt(2),1,0);
	v35rotated=v35.rotateY(pi/4);
	vectorsEqualWithinAccucary(n,v35rotated,v35target);

	//Test .rotateZ method
	n=36;
	ThreeVector<double> v36(10,-2,4), v36rotated,v36target(1+5*sqrt(3),5-sqrt(3),4);
	v36rotated=v36.rotateZ(pi/6);
	vectorsEqualWithinAccucary(n,v36rotated,v36target);
	
	//Test .unit method
	n=37;
	ThreeVector<int> v37(2,0,0),v37target(1,0,0);
	ThreeVector<int> v37copy=v37;
	allElementsEqual(n,v37.unit(),v37target);

	//check that v37 did not change
	n=38;
	allElementsEqual(n,v37,v37copy);

	//check == operator true state
	n=39;
	ThreeVector<int> v39(9,780,-977);
	allElementsEqual(n,v39==v39,true);
	//check == operator falste state
	n=40;
	allElementsEqual(n,v39==(2*v39),false);

	//check ~= operator true state
	n=41;
	allElementsEqual(n,v39!=(2*v39),true);
	//check ~= operator false state
	n=42;
	allElementsEqual(n,v39!=v39,false);

	//check <<, and >> operator for file streams
	n=43;
	ofstream ofs43("ThreeVectorTest43.txt");
	ifstream ifs43("ThreeVectorTest43.txt");
	ThreeVector<int> v43out(2,3,5),v43in;

	ofs43 << v43out	<< endl;
	ifs43 >> v43in;
	allElementsEqual(n,v43out,v43in);

	// double check using stringstream 
	n=44;
	ThreeVector<int> v44out(7,11,13);
	stringstream stringStream44;

	stringStream44 << v44out << endl;
	stringStream44 >> v43in;

	allElementsEqual(n,v44out,v43in);
	/*
	// check cin function
	ThreeVector<int> v45;
	cin >> v45;
	cout << v45;
	*/
	// Do the recommended check from the instruction set
	n=45;
	ThreeVector<double> v45a(96,66,4),v45b(76,4,32),v45c(75,28,96);
	ThreeVector<double> v45RotateMe = v45b;
	double x45=80, result45Target=68.6518071308040163;

	double result45 = (((v45a+v45b)-v45c)/x45) * (v45RotateMe.rotateX(0.1)+v45c.unit());
	allElementsEqual(n,result45,result45Target);


	return 0;
}

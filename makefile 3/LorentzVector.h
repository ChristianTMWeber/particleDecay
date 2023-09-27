// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations
// Created on Wed Apr 20 16:55:20 2016

/*

LorentzVector.h

Contains the delerations of the LorentzVector class. A class derived from the ThreeVector clas

LorentzVector - A class that implements (real valued) four component  lorentz vectors in C++. We define our vector such that the components are (ct, x,y,z) and our metric such that the contravariant Lorentz vector is (ct,-x,-y,-z)

*/

//#include "ThreeVector.h"
#ifndef LorentzVector_h
#define LorentzVector_h
#include <iostream>
#include <cmath>

// class decleration
class LorentzVector: public ThreeVector<double>{
protected:
	double ct;

	void getBoostMatrix(double boostMatrix[4][4],const LorentzVector momentuFourVector){
		//LorentzVector momentuFourVector(5,4,0,0);

		ThreeVector<double> beta = (double(-1)*(momentuFourVector.vect()/momentuFourVector.E()));

		ThreeVector<double> betaUnit = beta.unit();

		double gamma = 1/sqrt(1-pow(beta.mag(),2));

				//see Jackson p.547;
			//boostMatrix[row][column]
				//row 0
				boostMatrix[0][0]=  gamma;
				boostMatrix[0][1]= -gamma*beta.x();
				boostMatrix[0][2]= -gamma*beta.y();
				boostMatrix[0][3]= -gamma*beta.z();
				//row 1
				boostMatrix[1][0]=   -gamma*beta.x();
				boostMatrix[1][1]= 1+(gamma-1)*betaUnit.x()*betaUnit.x();
				boostMatrix[1][2]=   (gamma-1)*betaUnit.x()*betaUnit.y();
				boostMatrix[1][3]=   (gamma-1)*betaUnit.x()*betaUnit.z();
				//row 2
				boostMatrix[2][0]=   -gamma*beta.y();
				boostMatrix[2][1]=   (gamma-1)*betaUnit.x()*betaUnit.y();
				boostMatrix[2][2]= 1+(gamma-1)*betaUnit.y()*betaUnit.y();
				boostMatrix[2][3]=   (gamma-1)*betaUnit.y()*betaUnit.z();
				//row 3
				boostMatrix[3][0]=   -gamma*beta.z();
				boostMatrix[3][1]=   (gamma-1)*betaUnit.x()*betaUnit.z();
				boostMatrix[3][2]=   (gamma-1)*betaUnit.y()*betaUnit.z();
				boostMatrix[3][3]= 1+(gamma-1)*betaUnit.z()*betaUnit.z();
	};
public:
	////constructors

	//default constructor
	LorentzVector(): ThreeVector<double>() {ct=0;};

	// set constructor - 4 scalars
	LorentzVector(const double T, const double X,const double Y,const double Z): ThreeVector<double>(){
						ct=T; mx=X; my=Y; mz=Z;};
	
	// set constructor - three-vector, scalar
	LorentzVector(const ThreeVector<double>& momentumThreeVector,const double E): ThreeVector<double>(){
						ct=E; 
						mx=momentumThreeVector.x();
						my=momentumThreeVector.y(); 
						mz=momentumThreeVector.z();};
	
	// set constructor - scalar, three-vector
	LorentzVector(const double E, const ThreeVector<double>& momentumThreeVector): ThreeVector<double>(){
						ct=E; 
						mx=momentumThreeVector.x(); 
						my=momentumThreeVector.y(); 
						mz=momentumThreeVector.z();};
 	//copy constructor
	LorentzVector(const LorentzVector &copyMeVector){
		ct=copyMeVector.t(); mx=copyMeVector.x(); my=copyMeVector.y(); mz=copyMeVector.z();};

	//Assignment Operator
	LorentzVector operator=(const LorentzVector& assignFromVector){ 
					ct=assignFromVector.t(); mx=assignFromVector.x(); my=assignFromVector.y(); mz=assignFromVector.z();
					return *this;}//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.

	////get members 
	double t() const{return ct;}; //return t component of 4-vector

	double E() const{return ct;}; //return t component of 4-vector
	double px()const{return mx;}; //return x component of 4-vector
	double py()const{return my;}; //return y component of 4-vector
	double pz()const{return mz;}; //return z component of 4-vector

	// return spacial component of four-vector as ThreeVector
	ThreeVector vect()const{return ThreeVector(mx,my,mz);};

	// return squareroot of four-vector norm
	//note that we folllow the definition of the metric where the contra-variant four-vectors are given as (ct,-x,-y,-z)
	double mag()const{	ThreeVector spaceComponents = vect();
					  	return sqrt(pow(ct,2)-pow(spaceComponents.mag(),2));};

	double mass()const{ return mag();};

	////set members
	void setT( double val){ct = val;}; //set t component of 4 vector

	void setE( double val){ct = val;}; //set t component of 4 vector
	void setPx(double val){mx = val;}; //set x component of 4 vector
	void setPy(double val){my = val;}; //set y component of 4 vector
	void setPz(double val){mz = val;}; //set z component of 4 vector

	//set spacial component of 4-vector using ThreeVector
	void setVect(const ThreeVector& assignFromVector){ 
		mx=assignFromVector.x(); my=assignFromVector.y(); mz=assignFromVector.z();};

	//array subscripting operator
	double& operator[](const unsigned int index){
		switch(index%4){ 	case 0: return ct; break;
								case 1: return mx; break;
								case 2: return my; break;
								case 3: return mz; break;
								default: return ct; break; // there is no way this should be called. But the -wall -pedantic -obnoxious compiler demands a non-local default return. So this is a bad hack. It'll work for now.
					}
	};

	////Arithmetic Operators 

	// +=, plus operator
	LorentzVector& operator+=(const LorentzVector& addMeVector){
				 	ct+=addMeVector.t(); mx+=addMeVector.x(); my+=addMeVector.y(); mz+=addMeVector.z();
					return *this;};

	// *=, multiplication operator
	LorentzVector& operator*=(const double& scalarFactor){
				 ct*=scalarFactor; mx*=scalarFactor; my*=scalarFactor; mz*=scalarFactor;
				 return *this;};

	//since we define the LorentzVector only of type double, we do not need to take special care of the -= and /= cases and can define these as non-members in terms of += and */

	// -=, minus operator
	LorentzVector& operator-=(const LorentzVector& subtractMeVector){
						LorentzVector tempVector(subtractMeVector);
						*this+=(tempVector*=(-1));
					return 	*this;};

	// /=, devision operator
	LorentzVector& operator/=(const double& scalarDivisor){
						*this*=(1/scalarDivisor);
					return 	*this;};

	//// Vector Operatorions

	//Lorentz Boost

	LorentzVector boost(const LorentzVector& labFrameFourMomentum){
					double boostMatrix[4][4] ={};
					getBoostMatrix(boostMatrix,labFrameFourMomentum);
					productVectorMatrix(*this,boostMatrix);
					return *this;}; //boost the vector into the lab-frame


// product between a matrix and a vector
// overload it for LorentzVectors and 4x4 matrices
void productVectorMatrix(LorentzVector& fourVector,const double boostMatrix[4][4]){
	//define a array to store the resulting vectors elements temporary
	double resultingVector[4] ={0,0,0,0};

	//perform the matrix multiplication elementwise
	for(int m=0;m<4;++m){ 
	 	for(int n=0;n<4;++n){ resultingVector[m] += boostMatrix[m][n] * fourVector[n]; }
	}
	//write the results into the aVector
	for(int m=0;m<4;++m){ fourVector[m] = resultingVector[m];}
	};
};


#endif

//// boolean operators

bool operator==(const LorentzVector& vA,const LorentzVector& vB){ return (vA.t()==vB.t()&&vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z()); }
bool operator!=(const LorentzVector& vA,const LorentzVector& vB){ return !(vA==vB); }

// << operator
std::ostream& operator<<(std::ostream& os, const LorentzVector& vOut){
	os << vOut.t()<<"\t"<< vOut.x() <<"\t"<< vOut.y() <<"\t"<< vOut.z();
	return os;}
// >> operator
std::istream& operator>>(std::istream& is, LorentzVector& vIn){
	double tmpT, tmpX, tmpY, tmpZ;
	is >>tmpT>> tmpX>>tmpY>>tmpZ;
	vIn.setT(tmpT);
	vIn.setX(tmpX); 
	vIn.setY(tmpY); 
	vIn.setZ(tmpZ);
	return is;}
	
/* ADDITION */

// + operator
//we make + not a member function, so no 'ThreeVector::'
// we choose to template the + , and the following arithmetric operators as aType operator+(aType leftSummand, const aType& rightSummand), instead of ThreeVector<aType> operator+(ThreeVector<aType> leftSummand, const ThreeVector<aType>& rightSummand). This has the advantage that we do not have to overload the + operator again for the LorentzVectors. The downside here is that we probably overload the + operator for _all_ types, even the fundamental ones. So fingers crossed that nothing breakes. It should be ok, as long as everything is defined in terms of the +=, *=, -=, /= operators.



LorentzVector operator+(const LorentzVector&  leftSummand, const LorentzVector& rightSummand){
	LorentzVector tempVector(leftSummand);
	//LorentzVector newSummand = leftSummand->copy(); //Lena
	tempVector+=rightSummand;
	return tempVector;}


// unary + operator

LorentzVector& operator+(LorentzVector& unaryPlusVector){
	return unaryPlusVector;}

/* SUBTRACTION */

// - operator

LorentzVector operator-(LorentzVector minuend, const LorentzVector& subtrahend){
	minuend-=subtrahend;
	return minuend;}

// unary - operator

LorentzVector& operator-(LorentzVector& unaryMinusVector){
	unaryMinusVector*=(-1);
	return unaryMinusVector;}

/* MULTIPLICATION */

// * operator -- scalar on the right

LorentzVector operator*(LorentzVector leftVectorFactor, const double& rightScalarFactor){
	leftVectorFactor*=rightScalarFactor;
	return leftVectorFactor;}

// * operator -- scalar on the left

LorentzVector operator*(const double& leftScalarFactor,LorentzVector rightVectorFactor){
	rightVectorFactor*=leftScalarFactor;
	return rightVectorFactor;}

/*DIVISION*/

// / operator -- there's only the case with the scalar on the right

LorentzVector operator/(LorentzVector leftVectorDividend, const double& rightScalarDivisor){
	leftVectorDividend/=rightScalarDivisor;
	return leftVectorDividend;}


//// Vector Operatorions


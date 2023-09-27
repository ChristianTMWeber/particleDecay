// @author: Christian Weber for Phys 678 Final Project
// Created on Wed Apr 20 16:55:20 2016

/*

ThreeVector.h

Contains the delerations of the ThreeVector class

ThreeVector - A class that implements (real valued) three component vectors in C++

*/
#ifndef ThreeVector_h
#define ThreeVector_h
#include <iostream>
#include <cmath> 

// class decleration

class ThreeVector{
protected:
	// these are the three private variables that hold the three elements of the vector
	double mx, my, mz;

	// rotation
	// get the 3x3 rotation matrix for x.y.z.(column vector) (in this order) rotations
	//xPhi is the angle in radiation of which we rotate around the x-Axis, yPhi, and zPhi analog. 
	//ATTENTION, rotations in 3d are not commutative. So this rotation matrix is to be understood to first a rotation around z, then around y, and last around x. If we want rotations in different orders, we have to do this by applying this matrix repeatedly with the approprite angles each time 0
	void getRotationMatrix(double rotationMatrix[3][3],const double &xPhi, const double &yPhi,const double &zPhi){
							rotationMatrix[0][0]= cos(yPhi)*cos(zPhi);
							rotationMatrix[0][1]=-cos(yPhi)*sin(zPhi);
							rotationMatrix[0][2]= sin(yPhi);
							rotationMatrix[1][0]= cos(zPhi)*sin(xPhi)*sin(yPhi) + cos(xPhi)*sin(zPhi);
							rotationMatrix[1][1]= cos(xPhi)*cos(zPhi)           - sin(xPhi)*sin(yPhi)*sin(zPhi);
							rotationMatrix[1][2]=-cos(yPhi)*sin(xPhi);
							rotationMatrix[2][0]=-cos(xPhi)*cos(zPhi)*sin(yPhi) + sin(xPhi)*sin(zPhi);
							rotationMatrix[2][1]= cos(zPhi)*sin(xPhi)           + cos(xPhi)*sin(yPhi)*sin(zPhi);
							rotationMatrix[2][2]= cos(xPhi)*cos(yPhi);
							};

// product between a matrix and a vector

void productVectorMatrix(ThreeVector& aVector,const double rotationMatrix[3][3]){
	//define a array to store the resulting vectors elements temporary
	double resultingVector[3] ={0,0,0};

	//perform the matrix multiplication elementwise
	for(int m=0;m<3;++m){ 
	 	for(int n=0;n<3;++n){ resultingVector[m] += rotationMatrix[m][n] * aVector[n]; }
	}
	//write the results into the aVector
	for(int m=0;m<3;++m){ aVector[m] = resultingVector[m];}
};

public:
	////constructors
	ThreeVector(){mx=0; my=0; mz=0;};	//default constructor
	ThreeVector(double x, double y, double z){mx=x; my=y; mz=z;}; 	// set constructor
	ThreeVector(const ThreeVector &copyMeVector){ mx=copyMeVector.x(); my=copyMeVector.y(); mz=copyMeVector.z();}; //copy constructor

	//Destructor
	virtual ~ThreeVector(){};

	//// access members
	//return each element of the vector individually
	//since none of these methods are changing anything, we make it explicit by declaring them as const. This will also allow us to use them on a ThreeVector instance that has been declared as constant 
	
	double x()const{return mx;}; //return x component of 3 vector
	double y()const{return my;}; //return y component of 3 vector
	double z()const{return mz;}; //return z component of 3 vector

	virtual double mag()	 const{return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));}; //return the magnitude of the vector
	double phi()	 const{return atan2(y(),x());}; //return the azimuthal angle of the vector in the xy plane
	double theta()const{return acos(z()/mag());}; //return the polar angle of the vector
	double perp() const{return sqrt(pow(x(),2)+pow(y(),2));}; //return the transverse (to z) component of the vector

	//// set members
	//set each element of the vector individually
	void setX(double val){mx = val;}; //set x component of 3 vector
	void setY(double val){my = val;}; //set y component of 3 vector
	void setZ(double val){mz = val;}; //set z component of 3 vector

	//array subscripting operator
	double& operator[](const unsigned int index){
	switch(index%3){ 	case 0:  return mx; break;
							case 1:  return my; break;
							case 2:  return mz; break;
							default: return mx; break; // there is no way this should be called. But the -wall -pedantic -obnoxious compiler demands a non-local default return. So this is a bad hack. It'll work for now.
						}				};

	//Assignment Operator
	ThreeVector operator=(const ThreeVector& assignFromVector){ 
				mx=assignFromVector.x(); my=assignFromVector.y(); mz=assignFromVector.z();
				return *this;};
	//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.
	//NOTE, assigments are right now only between ThreeVector of the same <double> supported

	// +=, plus operator
	virtual ThreeVector& operator+=(const ThreeVector& addMeVector){
				 mx+=addMeVector.x(); my+=addMeVector.y(); mz+=addMeVector.z();
				return *this;};

	// -=, minus operator
	//we could implement this as a non-member using the += operator and a multiplication with (-1), but that might run into trouble in the (unlikely case) of subtracting two vectors v1-=v2 of unsigned int. This operation is reasonable if every element of v1 is bigger than every one of v2. So we will implement the saver version, implementing it as a member and doing -= for each element
	ThreeVector& operator-=(const ThreeVector& subtractMeVector){
				 mx-=subtractMeVector.x(); my-=subtractMeVector.y(); mz-=subtractMeVector.z();
				 return *this;};

	// *=, multiplication operator
	ThreeVector& operator*=(const double& scalarFactor){
				 mx*=scalarFactor; my*=scalarFactor; mz*=scalarFactor;
				 return *this;};

	// /=, division operator --- for reasons analog to the -= case we implement the /= operator seperately,e.g. 4/=2 is a reasonable operation for ints, 4 *= (1/2) is not
	ThreeVector& operator/=(const double& scalarDivisor){
				 mx/=scalarDivisor; my/=scalarDivisor; mz/=scalarDivisor;
				 return *this;};

	//// Vector Operations

	//cross-product
	ThreeVector cross(const ThreeVector& crossVec){
					  double X = my*crossVec.z() - mz*crossVec.y();
					  double Y = mz*crossVec.x() - mx*crossVec.z();
	                  double Z = mx*crossVec.y() - my*crossVec.x();
				 	  ThreeVector crossResultVec(X,Y,Z);
					  return crossResultVec;};

	//rotate
	ThreeVector& rotateX(const double& phi){
						double rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,phi,0,0);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the x axis
	ThreeVector& rotateY(const double& phi){ 	
						double rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,0,phi,0);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the y axis
	ThreeVector& rotateZ(const double& phi){ 	
						double rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,0,0,phi);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the z axis

	ThreeVector unit()const{ ThreeVector tempVector;
							tempVector=*this;
							return tempVector/=(tempVector.mag());
								//if(&this->mag!=0){ ThreeVector tempVector;
								//				tempVector=*this;
								//				return tempVector/=(tempVector.mag());}
								//else{return *this;} //We define it this way. It might come in handy.
							};

//	ThreeVector clone(){ ThreeVector clonedVector;
//		clonedVector = *this;
//		return clonedVector;};
	//ThreeVector clone(const ThreeVector& originalVector){ ThreeVector clonedVector(originalVector);
	//	return clonedVector;};
};

#endif




// abs function  Value of vector

double abs(const ThreeVector& absVector){ return absVector.mag();} //abs Value of vector

////Input and output operators

// << operator
 
std::ostream& operator<<(std::ostream& os, const ThreeVector& vOut){
	os << vOut.x() <<"\t"<< vOut.y() <<"\t"<< vOut.z();
	return os;}

// >> operator
 
std::istream& operator>>(std::istream& is, ThreeVector& vIn){
	double tmpX, tmpY, tmpZ;
	is >> tmpX>>tmpY>>tmpZ;
	vIn.setX(tmpX); 
	vIn.setY(tmpY); 
	vIn.setZ(tmpZ);
	return is;}

////boolean operators

bool operator==(const ThreeVector& vA,const ThreeVector& vB){ return (vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z()); }

bool operator!=(const ThreeVector& vA,const ThreeVector& vB){ return !(vA==vB); }

/* ADDITION */

// + operator
//we make + not a member function, so no 'ThreeVector::'
// we choose to template the + , and the following arithmetric operators as double operator+(double leftSummand, const double& rightSummand), instead of ThreeVector operator+(ThreeVector leftSummand, const ThreeVector& rightSummand). This has the advantage that we do not have to overload the + operator again for the LorentzVectors. The downside here is that we probably overload the + operator for _all_ types, even the fundamental ones. So fingers crossed that nothing breakes. It should be ok, as long as everything is defined in terms of the +=, *=, -=, /= operators.

ThreeVector operator+(const ThreeVector&  leftSummand, const ThreeVector& rightSummand){
	ThreeVector tempVector(leftSummand);
	//ThreeVector tempVector = leftSummand->clone(); //Lena
	tempVector+=rightSummand;
	return tempVector;}


// unary + operator

ThreeVector& operator+(ThreeVector& unaryPlusVector){
	return unaryPlusVector;}

/* SUBTRACTION */

// - operator

ThreeVector operator-(ThreeVector minuend, const ThreeVector& subtrahend){
	minuend-=subtrahend;
	return minuend;}

// unary - operator

ThreeVector& operator-(ThreeVector& unaryMinusVector){
	unaryMinusVector*=(-1);
	return unaryMinusVector;}

/* MULTIPLICATION */

// * operator -- scalar on the right

ThreeVector operator*(ThreeVector leftVectorFactor, const double& rightScalarFactor){
	leftVectorFactor*=rightScalarFactor;
	return leftVectorFactor;}

// * operator -- scalar on the left

ThreeVector operator*(const double& leftScalarFactor,ThreeVector rightVectorFactor){
	rightVectorFactor*=leftScalarFactor;
	return rightVectorFactor;}

/*DIVISION*/

// / operator -- there's only the case with the scalar on the right

ThreeVector operator/(ThreeVector leftVectorDividend, const double& rightScalarDivisor){
	leftVectorDividend/=rightScalarDivisor;
	return leftVectorDividend;}

//// Vector on Vector Operations
// dot-product

double operator*(const ThreeVector& U, const ThreeVector& V){
	double dotProduct = U.x()*V.x() + U.y()*V.y() + U.z()*V.z();
	return dotProduct;}




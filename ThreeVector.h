// @author: Christian Weber for Phys 678 Homework 9 Problem 1
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
template <typename aType>
class ThreeVector{
protected:
	// these are the three private variables that hold the three elements of the vector
	aType mx, my, mz;
	// get the 3x3 rotation matrix for x.y.z.(column vector) (in this order) rotations
	//xPhi is the angle in radiation of which we rotate around the x-Axis, yPhi, and zPhi analog. 
	//ATTENTION, rotations in 3d are not commutative. So this rotation matrix is to be understood to first a rotation around z, then around y, and last around x. If we want rotations in different orders, we have to do this by applying this matrix repeatedly with the approprite angles each time 0
	void getRotationMatrix(aType rotationMatrix[3][3],const aType &xPhi, const aType &yPhi,const aType &zPhi){
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

public:
	////constructors
	ThreeVector(){mx=0; my=0; mz=0;};	//default constructor
	ThreeVector(aType x, aType y, aType z){mx=x; my=y; mz=z;}; 	// set constructor
	ThreeVector(const ThreeVector &copyMeVector){ mx=copyMeVector.x(); my=copyMeVector.y(); mz=copyMeVector.z();}; //copy constructor

	//Destructor
	virtual ~ThreeVector(){};

	//// access members
	//return each element of the vector individually
	//since none of these methods are changing anything, we make it explicit by declaring them as const. This will also allow us to use them on a ThreeVector instance that has been declared as constant 
	
	aType x()const{return mx;}; //return x component of 3 vector
	aType y()const{return my;}; //return y component of 3 vector
	aType z()const{return mz;}; //return z component of 3 vector

	aType mag()	 const{return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));}; //return the magnitude of the vector
	aType phi()	 const{return atan2(y(),x());}; //return the azimuthal angle of the vector in the xy plane
	aType theta()const{return acos(z()/mag());}; //return the polar angle of the vector
	aType perp() const{return sqrt(pow(x(),2)+pow(y(),2));}; //return the transverse (to z) component of the vector

	//// set members
	//set each element of the vector individually
	void setX(aType val){mx = val;}; //set x component of 3 vector
	void setY(aType val){my = val;}; //set y component of 3 vector
	void setZ(aType val){mz = val;}; //set z component of 3 vector

	//array subscripting operator
	aType& operator[](const int index){
	switch(abs(index%3)){ 	case 0:  return mx; break;
							case 1:  return my; break;
							case 2:  return mz; break;
							default: return mx; break; // there is no way this should be called. But the -wall -pedantic -obnoxious compiler demands a non-local default return. So this is a bad hack. It'll work for now.
						}				};

	//Assignment Operator
	ThreeVector operator=(const ThreeVector& assignFromVector){ 
				mx=assignFromVector.x(); my=assignFromVector.y(); mz=assignFromVector.z();
				return *this;};
	//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.
	//NOTE, assigments are right now only between ThreeVector<aType> of the same <aType> supported

	// +=, plus operator
	ThreeVector& operator+=(const ThreeVector& addMeVector){
				 mx+=addMeVector.x(); my+=addMeVector.y(); mz+=addMeVector.z();
				return *this;};

	// -=, minus operator
	//we could implement this as a non-member using the += operator and a multiplication with (-1), but that might run into trouble in the (unlikely case) of subtracting two vectors v1-=v2 of unsigned int. This operation is reasonable if every element of v1 is bigger than every one of v2. So we will implement the saver version, implementing it as a member and doing -= for each element
	ThreeVector& operator-=(const ThreeVector& subtractMeVector){
				 mx-=subtractMeVector.x(); my-=subtractMeVector.y(); mz-=subtractMeVector.z();
				 return *this;};

	// *=, multiplication operator
	ThreeVector& operator*=(const aType& scalarFactor){
				 mx*=scalarFactor; my*=scalarFactor; mz*=scalarFactor;
				 return *this;};

	// /=, division operator --- for reasons analog to the -= case we implement the /= operator seperately,e.g. 4/=2 is a reasonable operation for ints, 4 *= (1/2) is not
	ThreeVector& operator/=(const aType& scalarDivisor){
				 mx/=scalarDivisor; my/=scalarDivisor; mz/=scalarDivisor;
				 return *this;};

	//// Vector Operations

	//cross-product
	ThreeVector cross(const ThreeVector& crossVec){
					  aType X = my*crossVec.z() - mz*crossVec.y();
					  aType Y = mz*crossVec.x() - mx*crossVec.z();
	                  aType Z = mx*crossVec.y() - my*crossVec.x();
				 	  ThreeVector<aType> crossResultVec(X,Y,Z);
					  return crossResultVec;};

	//rotate
	ThreeVector& rotateX(const aType& phi){aType rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,phi,0,0);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the x axis
	ThreeVector& rotateY(const aType& phi){ 	aType rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,0,phi,0);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the y axis
	ThreeVector& rotateZ(const aType& phi){ 	aType rotationMatrix[3][3] ={};
						getRotationMatrix(rotationMatrix,0,0,phi);
						productVectorMatrix(*this,rotationMatrix);
						return *this;}; //rotate the vector by angle phi (in radians) around the z axis

	ThreeVector unit()const{return *this/abs(*this);};

	//// auxiliary functions


	//void productVectorMatrix(ThreeVector<aType>& aVector,const aType rotationMatrix[3][3]);

};

#endif




////constructors

/*
template<typename aType>  		//default constructor
ThreeVector<aType>::ThreeVector() 
template<typename aType> 		// set constructor
ThreeVector<aType>::ThreeVector(aType x, aType y, aType z){mx=x; my=y; mz=z;} 
template<typename aType> 		//copy constructor
ThreeVector<aType>::ThreeVector(const ThreeVector &copyMeVector){ mx=copyMeVector.x(); my=copyMeVector.y(); mz=copyMeVector.z();}
//unless the methods .x, .y, .z are also declared as constant, we will get an error here.

////Destructor
//template<typename aType>  
//ThreeVector<aType>::~ThreeVector(){}


//// access methods
//return each element of the vector individually

template <typename aType>
aType ThreeVector<aType>::x()const{return mx;} //return x component of 3 vector
template <typename aType>
aType ThreeVector<aType>::y()const{return my;} //return y component of 3 vector
template <typename aType>
aType ThreeVector<aType>::z()const{return mz;} //return z component of 3 vector

// mag() method
template <typename aType>
aType ThreeVector<aType>::mag()const{return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));} //return the magnitude of the vector
// phi() method
template <typename aType> 
aType ThreeVector<aType>::phi()const{return atan2(y(),x());} //return the azimuthal angle of the vector in the xy plane
// theta() method
template <typename aType> 
aType ThreeVector<aType>::theta()const{ return acos(z()/mag());} //return the polar angle of the vector
// perp () method
template <typename aType> 
aType ThreeVector<aType>::perp()const{return sqrt(pow(x(),2)+pow(y(),2));} //return the transverse (to z) component of the vector
*/

// abs function  Value of vector
template <typename aType>
aType abs(const ThreeVector<aType>& absVector){ return absVector.mag();} //abs Value of vector

/*
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
ThreeVector<aType> ThreeVector<aType>::operator=(const ThreeVector& assignFromVector){ mx=assignFromVector.x(); my=assignFromVector.y(); mz=assignFromVector.z();
return *this;}//This Assignment Operator is self-assignment safe, e.g. nothing gets deleted in any part of the self asignment process. And being self-assignment safe is preferably, to having an operator that needs protected from self assignment. So we do not even check here for self assignment.
//NOTE, assigments are right now only between ThreeVector<aType> of the same <aType> supported
*/
// << operator
template <typename aType> 
std::ostream& operator<<(std::ostream& os, const ThreeVector<aType>& vOut){
	os << vOut.x() <<"\t"<< vOut.y() <<"\t"<< vOut.z();
	return os;}
// >> operator
template <typename aType> 
std::istream& operator>>(std::istream& is, ThreeVector<aType>& vIn){
	aType tmpX, tmpY, tmpZ;
	is >> tmpX>>tmpY>>tmpZ;
	vIn.setX(tmpX); 
	vIn.setY(tmpY); 
	vIn.setZ(tmpZ);
	return is;}
/*
//array subscripting operator
template <typename aType>
aType& ThreeVector<aType>::operator[](const int index){
	switch(abs(index%3)){ 	case 0: return mx; break;
							case 1: return my; break;
							case 2: return mz; break;
							default: return mx; break; // there is no way this should be called. But the -wall -pedantic -obnoxious compiler demands a non-local default return. So this is a bad hack. It'll work for now.
				}
}
*/
//boolean operators
template <typename aType>
bool operator==(const ThreeVector<aType>& vA,const ThreeVector<aType>& vB){ return (vA.x()==vB.x())&&(vA.y()==vB.y())&&(vA.z()==vB.z()); }
template <typename aType>
bool operator!=(const ThreeVector<aType>& vA,const ThreeVector<aType>& vB){ return !(vA==vB); }

/*ARITHMETIC OPERATORS*/
/* ADITTION */
// += operator
/*
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::operator+=(const ThreeVector<aType>& addMeVector){
	mx+=addMeVector.x(); my+=addMeVector.y(); mz+=addMeVector.z();
	return *this;}
	*/
// + operator
//we make + not a member function, so no 'ThreeVector::'
template <typename aType>
ThreeVector<aType> operator+(ThreeVector<aType> leftSummand, const ThreeVector<aType>& rightSummand){
	leftSummand+=rightSummand;
	return leftSummand;}
// unary + operator
template <typename aType>
ThreeVector<aType>& operator+(ThreeVector<aType>& unaryPlusVector){
	return unaryPlusVector;}

/* SUBTRATION */
// -= operator
	/*
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::operator-=(const ThreeVector<aType>& subtractMeVector){
	mx-=subtractMeVector.x(); my-=subtractMeVector.y(); mz-=subtractMeVector.z();
	return *this;}
	*/
// - operator
//we make + not a member function, so no 'ThreeVector::'
template <typename aType>
ThreeVector<aType> operator-(ThreeVector<aType> minuend, const ThreeVector<aType>& subtrahend){
	minuend-=subtrahend;
	return minuend;}
// unary - operator
template <typename aType>
ThreeVector<aType>& operator-(ThreeVector<aType>& unaryMinusVector){
	unaryMinusVector*=(-1);
	return unaryMinusVector;}

/* MULTIPLICATION */
// *=, multiplication operator
	/*
template <typename aType>
ThreeVector<aType>&  ThreeVector<aType>::operator*=(const aType& scalarFactor){
	mx*=scalarFactor; my*=scalarFactor; mz*=scalarFactor;
	return *this;}
	*/
// * operator -- scalar on the right
template <typename aType>
ThreeVector<aType> operator*(ThreeVector<aType> leftVectorFactor, const aType& rightScalarFactor){
	leftVectorFactor*=rightScalarFactor;
	return leftVectorFactor;}
// * operator -- scalar on the left
template <typename aType>
ThreeVector<aType> operator*(const aType& leftScalarFactor,ThreeVector<aType> rightVectorFactor){
	rightVectorFactor*=leftScalarFactor;
	return rightVectorFactor;}

/*DIVISION*/
// /=, division operator
/*
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::operator/=(const aType& scalarDivisor){
	mx/=scalarDivisor; my/=scalarDivisor; mz/=scalarDivisor;
	return *this;}
*/
// / operator -- there's only the case with the scalar on the right
template <typename aType>
ThreeVector<aType> operator/(ThreeVector<aType> leftVectorDividend, const aType& rightScalarDivisor){
	leftVectorDividend/=rightScalarDivisor;
	return leftVectorDividend;}
/*
// unit() method
template <typename aType>
ThreeVector<aType> ThreeVector<aType>::unit()const{
	return *this/abs(*this);
}
*/

//// Vector on Vector Operations
// dot-product
template <typename aType>
aType operator*(const ThreeVector<aType>& U, const ThreeVector<aType>& V){
	aType dotProduct = U.x()*V.x() + U.y()*V.y() + U.z()*V.z();
	return dotProduct;}
//cross-product
	/*
template <typename aType>
ThreeVector<aType> ThreeVector<aType>::cross(const ThreeVector& crossVec){
	aType X = my*crossVec.z() - mz*crossVec.y();
	aType Y = mz*crossVec.x() - mx*crossVec.z();
	aType Z = mx*crossVec.y() - my*crossVec.x();
	ThreeVector<aType> crossResultVec(X,Y,Z);
	return crossResultVec;
}
*/
//rotations
//rotate around x axis
/*
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::rotateX(const aType& phi){ 	aType rotationMatrix[3][3] ={};
														getRotationMatrix(rotationMatrix,phi,0,0);
														productVectorMatrix(*this,rotationMatrix);
														return *this;}
//rotate around y axis
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::rotateY(const aType& phi){ 	aType rotationMatrix[3][3] ={};
														getRotationMatrix(rotationMatrix,0,phi,0);
														productVectorMatrix(*this,rotationMatrix);
														return *this;}
//rotate around z axis
template <typename aType>
ThreeVector<aType>& ThreeVector<aType>::rotateZ(const aType& phi){ 	aType rotationMatrix[3][3] ={};
														getRotationMatrix(rotationMatrix,0,0,phi);
														productVectorMatrix(*this,rotationMatrix);
														return *this;}
*/
//// auxiliary functions
// get the 3x3 rotation matrix for x.y.z.(column vector) (in this order) rotations
/*
template <typename aType>
void ThreeVector<aType>::getRotationMatrix(aType rotationMatrix[3][3],const aType &xPhi, const aType &yPhi,const aType &zPhi){
	rotationMatrix[0][0]= cos(yPhi)*cos(zPhi);
	rotationMatrix[0][1]=-cos(yPhi)*sin(zPhi);
	rotationMatrix[0][2]= sin(yPhi);
	rotationMatrix[1][0]= cos(zPhi)*sin(xPhi)*sin(yPhi) + cos(xPhi)*sin(zPhi);
	rotationMatrix[1][1]= cos(xPhi)*cos(zPhi)           - sin(xPhi)*sin(yPhi)*sin(zPhi);
	rotationMatrix[1][2]=-cos(yPhi)*sin(xPhi);
	rotationMatrix[2][0]=-cos(xPhi)*cos(zPhi)*sin(yPhi) + sin(xPhi)*sin(zPhi);
	rotationMatrix[2][1]= cos(zPhi)*sin(xPhi)           + cos(xPhi)*sin(yPhi)*sin(zPhi);
	rotationMatrix[2][2]= cos(xPhi)*cos(yPhi);
}
*/

// product between a matrix and a vector
template <typename aType>
void productVectorMatrix(ThreeVector<aType>& aVector,const aType rotationMatrix[3][3]){
	//define a array to store the resulting vectors elements temporary
	aType resultingVector[3] ={0,0,0};

	//perform the matrix multiplication elementwise
	for(int m=0;m<3;++m){ 
	 	for(int n=0;n<3;++n){ resultingVector[m] += rotationMatrix[m][n] * aVector[n]; }
	}
	//write the results into the aVector
	for(int m=0;m<3;++m){ aVector[m] = resultingVector[m];}
	//delete resultingVector;
}


////in case the method implementations are in a seperate .cxx file (i.e. seperate from the .h file)
// instantiate the ThreeVector class for the types that I expect to use -- I don't wanna write everything into the .h file, despite that being the other recommended solution to the otherwise extant linking problem
// see here for an explanation and example solutions to the problem -- https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
//template class ThreeVector<double>;
//template class ThreeVector<int>;

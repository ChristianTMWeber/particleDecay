// @author: Christian Weber for Phys 678 Homework 9 Problem 1
// Created on Wed Apr 20 16:55:20 2016

/*

LorentzVector.h

Contains the delerations of the LorentzVector class. A class derived from the ThreeVector clas

LorentzVector - A class that implements (real valued) four component  lorentz vectors in C++. We define our vector such that the components are (ct, x,y,z) and our metric such that the contravariant Lorentz vector is (ct,-x,-y,-z)

*/
#ifndef LorentzVector_h


// class decleration
class LorentzVector: public ThreeVector<double>{
protected:
	double ct;
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
		switch(abs(index%4)){ 	case 0: return ct; break;
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

};


#endif

////constructors

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
	
	



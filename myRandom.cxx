// @author: Christian Weber for Phys 678 Homework 9 Problem 1
// Created on Wed Apr 13 11:50:12 2016

/*

LCMRandomNumberGenerator - generates pseudo random numbers using the linear congruential generator algorithm
Unless explicitly set, the seed is based on the system time

*/
//load the packages that we need
#include "myRandom.h"
#include <iostream> // for cin, cout
#include <fstream> 
#include <time.h> //to get the current time
#include <cmath> // for abs
#include <limits> // for max float
using namespace std; // using the std namespace


//methods

//constructor methods
LCMRandomNumberGenerator::LCMRandomNumberGenerator(){
	// use current timer as seed if none is specified
	// better than a fixed value.
	time_t myTime;
	
	long seedIn = (time(&myTime))%100000; //take the mudolo of the current time with 10000. That prevents the term signed long (a*x+c) from overflowing and gives a period of about 4 weeks
	setSeed(seedIn);
}

LCMRandomNumberGenerator::LCMRandomNumberGenerator(long seedIn){
	setSeed(seedIn);
}

//destructor method
LCMRandomNumberGenerator::~LCMRandomNumberGenerator(){}

//// methods related to the seed


//set the seed
void LCMRandomNumberGenerator::setSeed(long seedIn){
	seed=long(seedIn); //just to be sure we get a long. 
	x = seed;
}

//return the seed
long LCMRandomNumberGenerator::getSeed(){
	return seed;
}

//// methods that provide random numbers
//get a randum integet between m-1 and 0
//the actual LCM generator, the base for all the other methods here that hand out random numbers
long  LCMRandomNumberGenerator::flatInt(){
	x = abs((a*x+c)%m); //take the abs, so that the number is non-zero in case we got an a negotive seed or in case a*x+c rolls over to negative from a particularly large seed. Usually here we would unsigned long, but the PSet calls for long as output and input for the seed. So we just stay at long.
	return x;
}

//get a random number out of the closed intervall [0,1]
//we will use this function as a base for the other random numbers
double LCMRandomNumberGenerator::flat(){
	return double(flatInt())/double(m-1);
}

//get a random number out of the closed intervall [a,b]
double LCMRandomNumberGenerator::flat(double a, double b){
	//determine if a<b or vice versa
	double smallN, bigN;
	
	if(b>a){bigN=b; smallN = a; }
	else{ 	if(a>b){ bigN=a	; smallN = b;}
			else { return a;}	}
		
	double width = bigN-smallN;
	
	return smallN+width*flat();
}

//get a random integer in the closed interval [m,n]
long  LCMRandomNumberGenerator::flatInt(long m, long n){
	return  long(flat(double(m),double(n)));
}


//get a rando exponentially distributed float with mean 'mean'
double LCMRandomNumberGenerator::exponential(double mean){
	//we do not want our random number to return inf=-log(0), but there is a small but non-zero chance that flat() returns 0
	//so in order to prevent that we do the fowlling
	
	double returnValue = flat();
	while(returnValue==0){returnValue=flat();}
	
	return -log(returnValue)/mean;
}

//get a random exponentially distributed float with mean '1'
double LCMRandomNumberGenerator::exponential(){
	return exponential(float(1));
}

double LCMRandomNumberGenerator::gaussian(){
	//we do not want our random number to return inf=sqrt(-2*log(1-1));, but there is a small but non-zero chance that flat() returns 1
	//so in order to prevent that we do the fowlling
	double randomNumberForRadius = flat();
	while(randomNumberForRadius==1){randomNumberForRadius=flat();}
	double r = sqrt(-2*log(1-randomNumberForRadius));
	
	double theta = 2*M_PI*flat();
	
	return r*cos(theta);
}

double LCMRandomNumberGenerator::gaussian(double mean, double sigma){
	return mean+gaussian()*sigma;
}

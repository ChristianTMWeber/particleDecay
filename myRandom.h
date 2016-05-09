// @author: Christian Weber for Phys 678 Homework 9 Problem 1 and Final Project
// Created on Wed Apr 13 11:50:12 2016
// Modified, Sun May 08

/*

LCMRandomNumberGenerator - generates pseudo random numbers using the linear congruential generator algorithm
Unless explicitly set, the seed is based on the system time

*/

#ifndef myRandom_h
#define myRandom_h
// class delceration
class LCMRandomNumberGenerator{
	private: 
		long  seed;
		const static long m = 1771875, a =2416, c=374441;
		//const static unsigned long m = 4294967296, a =1664525, c=1013904223; //use the suggested values from 'Numerical Recepies in C' to get a few more digits in our floating point random numbers
		long x;
		
		
	public: 
		//the class constructors
		LCMRandomNumberGenerator();
		LCMRandomNumberGenerator(long seed);
		
		//the class destructor
		~LCMRandomNumberGenerator();
		
		//the classes public methods
		void setSeed(long seed);
		long getSeed();
		
		long flatInt();
		long flatInt(long m, long n);
		
		double flat();
		double flat(double a, double b);
		
		double exponential();
		double exponential(double mean);
		
		double gaussian();
		double gaussian(double mean, double sigma);
		
};

#endif

// @author: Christian Weber for Phys 678 Homework 9 Problem 1
// Created on Wed Apr 13 11:50:12 2016

/*

Test my implementation of the LCM random number generator, by generating three sets of random numbers from different distributions and writing them to different files. I can read these our later with a programm of my choice to plot them.

*/
//load the packages that we need
#include <iostream> // for cin, cout
#include <fstream> 
#include <time.h> //to get the current time
#include "myRandom.h"
#include <cmath>
using namespace std; // using the std namespace


int main(int argc, char *argv[]) {
	//make a LCMRandomNumberGenerator object;
	LCMRandomNumberGenerator myRand;

	long nNumbersToGenerate = 1000000;

// generate and write flats
	// create an ofstream object
   std::ofstream ofs;
   // open a file to wrote the numbers to
   ofs.open ("flat.txt", std::ofstream::out | std::ofstream::app);
   //loop over a single number generation and appending event
 	for(int i=0; i<nNumbersToGenerate;i++){
 		 ofs << myRand.flat() <<"\n";
 	}
 	//close the file/ofstream object, so we can start with the next one
   ofs.close();
    
// generate and write exponentials
   // open a file to wrote the numbers to
  ofs.open ("exponential.txt", std::ofstream::out | std::ofstream::app);
  //loop over a single number generation and appending event
	for(int i=0; i<nNumbersToGenerate;i++){
		 ofs << myRand.exponential() <<"\n";
	}
	//close the file/ofstream object, so we can start with the next one
  ofs.close();
  
// generate and write gaussians
	// open a file to wrote the numbers to
  ofs.open ("gaussian.txt", std::ofstream::out | std::ofstream::app);
    //loop over a single number generation and appending event
	for(int i=0; i<nNumbersToGenerate;i++){
		 ofs << myRand.gaussian() <<"\n";
	}
	//close the file/ofstream object, so we can start with the next one
  ofs.close();
}

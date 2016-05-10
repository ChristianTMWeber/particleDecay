// @author: Christian Weber for Phys 678 Final Project: Particle Physics Simulations

// Created on Sat May 07 17:42:44 2016

/*
ParticleDecay.cxx

Simulates the decay of a (relativistic) J/psi meson into a electron positron pair

*/

//load our own files that we need
#include "ThreeVector.h"
#include "LorentzVector.h"
#include "myRandom.h"
//load the packages that we need
#include <iostream> // for cin, cout
#include <fstream> 
#include <cmath> 
#include <stdlib.h>     /* atoi, atof */

//we do not want to type 'std::' all the time, so includethe std namespace
using namespace std;

//// commence the decays 
int main(int argc, char *argv[]) {
	const double massJ = 3.096; // Mass of the J/psi meson in Units of GeV/c^2, and in general we will work in units where c=1
	const double massElectron = 0.0005109; //Mass of the electron and positron in Units of GeV/c^2, and in general we will work in units where c=1
	//call a LCMRandomNumberGenerator object to generate random nubmers
	LCMRandomNumberGenerator myRand;

	// store the number of decays to simulate here
	int nDecays;

//	//receive the J/psi momenta from the user in these
//	double pJx, pJy, pJz; 

	////to ease distinction, we will end all Lorentz / four-vectors in 4, and all spacial / three-vectors in 3
	
	//declare four-momenta for J/psi
	LorentzVector JMomentum4;

	//declare four-momenta for the decay products
	LorentzVector electronMomentum4, positronMomentum4;

	//declare the center of mass (CoM) three-momentum for the electron (the positron ones is just the negative of it)
	ThreeVector<double> electronMomentumCoM3;
	//and also declare the magnitude of the electron CoM momentum seperately, we even know it apriori
	double electronMomentumMagnitudeCoM = sqrt( pow(massJ/2,2)-pow(massElectron,2));

	//we will genrate the direction of the electron CoM randomly. These variables should also be declared
	double phi, theta;


	// check and parse the passed commandline arguments
	
	if(argc!=5){ 
			cout<<"ParticleDecay.cxx - needs exactly 4 arguments passed to." << endl;
			cout<<"argument 1 - momentum of the J/psi along the x-axis in the lab frame in GeV/c^2." << endl;
			cout<<"argument 2 - momentum of the J/psi along the y-axis in the lab frame in GeV/c^2." << endl;
			cout<<"argument 3 - momentum of the J/psi along the z-axis in the lab frame in GeV/c^2." << endl;
			cout<<"argument 4 - number of decays to simulate." << endl;
			cout<<"Please call the programm again with the proper number of arguments." << endl;
			return 0;
			};

	
	//	pJx= atof(argv[1]), pJy = atof(argv[2]), pJz=atof(argv[3]);  // J/psi momentum in the Labframe in GeV/c^2

	nDecays = atoi(argv[4]);
	
	// set the elements of the J/psi four momentum vector
	JMomentum4.setX(atof(argv[1]));
	JMomentum4.setY(atof(argv[2]));
	JMomentum4.setZ(atof(argv[3]));
	JMomentum4.setE( sqrt( 	pow(massJ,2) + pow( abs(JMomentum4.vect()) ,2)) ); // J/psi energy in the Labframe in GeV/c^2
	


//////TESTING
// to make testing easier, create an ofstream object to write my data to somewhere
ofstream outputFileStream; outputFileStream.open ("ParticleDecayTest.txt");//, ofstream::out | ofstream::app);
	
	for(int n =0; n<nDecays; ++n ){
		
		//We know from energy and momentum conservation arguments the energies of the decay products in the center of mass frame
		electronMomentum4.setE(massJ/2);
		positronMomentum4.setE(massJ/2);
		
		// and we know the absolute value of the three-momentum for each decay product: electronMomentumMagnitudeCoM
		// but we need to decide in which direction they decay (in the center of mass frame)
		// let's generate coordinates for points uniformly distributed on the surface of the 3d unit sphere
		phi 	= 2 * M_PI *  myRand.flat();
		theta 	= acos( myRand.flat()*2-1);
		
		electronMomentumCoM3.setX(cos(phi)*sin(theta));
		electronMomentumCoM3.setY(sin(phi)*sin(theta));
		electronMomentumCoM3.setZ(cos(theta));
		
		// we set the direction of the three-momentum, now set the absolute value
		electronMomentumCoM3*=electronMomentumMagnitudeCoM;

		//now put the CoM momentum in the electron four-momentum
		electronMomentum4.setVect(electronMomentumCoM3);
		//conservation of momentum dictates that the positron flies off in the oposite direction
		positronMomentum4.setVect( (-electronMomentumCoM3) );

		//and now we boost back into the lab frame
		electronMomentum4.boost(JMomentum4);
		positronMomentum4.boost(JMomentum4);

		
		cout<< electronMomentum4 <<"\n" << positronMomentum4 <<"\n";

		
//outputFileStream<< electronMomentum4 <<"\n" << positronMomentum4 <<"\n";

	}
//outputFileStream.close();
	return 0;
}

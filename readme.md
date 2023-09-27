# ParticleDecay
A small project that simulates the decay of a J/psi meson into an electron-positron pair.

Based on an self written class of templated Three-Vector, a Lorentz-Vector class that inherits from the Three-Vector, and an implementation of a linear congruential pseudo random number generator.

Contains tests for the Three-Vector and Lorentz-Vector implementations.

## ParticleDecay

To build the program simulating the J/psi meson's decay run:
>make -f makeParticleDecay

This will will produce a file **ParticleDecay**.
To run then the  J/psi meson decay simulation run

>./ParticleDecay \<pX> \<pY> \<pZ> \<number of decay simulations>
>
pX, pY, and pZ, are the momenta of the J/psi in the lab frame along the x-, y-, and z-axes. and \<number of decay simulations> are the number of decays that we want to simulate.

> ./ParticleDecay -h

Will also print instructions.

E.g.:
>./ParticleDecay 0  0 10.1 1

Simulates the decay of one J/psi meson, traveling with 10 GeV/c^2 along the z-axis. 

The program returns for each decay two four-vectors. The first one is the four vector of the electron, the second is the positron's four-vector. The four vectors elements are (E, pX, pY, pZ), where E is the energy of the electron / positron, and pX, pY, and pZ are the momenta of the electron/positron along the x-, y-, and z-axes in the lab frame

e.g. the output takes the form:
|  | E [GeV] | pX [GeV/c] |pY [GeV/c]  | pZ [GeV/c] |
|-----------|-----------|-----------|-----------|-----------|
electron 1|9.16097 |0.918981   |       0.371371     |    9.10719 |
electron 2|1.4029   | -0.918981 |      -0.371371    |   0.992812|



## Test Three-Vector
To build the Three-Vector test run:
> make -f makeThreeVectorTest

This will produce a file **ThreeVectorTest**. Run it via

>./ThreeVectorTest

The program runs a number of tests on the ThreeVector implementation and prints out if the test result.

## Test Lorentz-Vector
To build the Lorentz-Vector test run:
> make -f makeLorentzVectorTest

This will produce a file **LorentzVectorTest**. Run it via

>./LorentzVectorTest

The program runs a number of tests on the Lorentz-Vector implementation and prints out if the test result.




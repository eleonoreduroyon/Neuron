#ifndef _CONSTANTS
#define _CONSTANTS

double const MembranePotentialTHRESHOLD(20.0); //Spike threshold
double const TAU(20); 
double const C(1);
//double RESISTANCE(20.0); //TAU/C;0 a 400; Membrane Resistance
double const RefractoryTIME(2.0); //How long the break is
double const H(.1); 
long const REFRACTORYSTEP = RefractoryTIME*10; //
double const JAMPLITUDE(.1);
long const DelaiSTEP(15);
double const VRESET(0.0);

#endif

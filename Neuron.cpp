//
//  Neuron.cpp
//  
//
//  Created by Ely on 10/2/17.
//
//

#include "Neuron.hpp"
#include "Constants.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Constructeurs
Neuron::Neuron(): MembranePotential_(0.0), NbrSpikes_(0.0), TimeSpikes_(0.0),refractory_(false), RefractoryBreakTime_(0.0){}
Neuron::Neuron(double MembranePotential, int NbrSpikes, double TimeSpikes, bool refractory): 
MembranePotential_(MembranePotential), NbrSpikes_(NbrSpikes), TimeSpikes_(TimeSpikes), refractory_(refractory), RefractoryBreakTime_(0.0){}

//Methodes
void Neuron :: update(double h, double I, double tStart, double tStop, double a, double b){
    double tSimulation(tStart);
    double InputCurrent;
    ofstream sortie("MembranePotential", ios::out|ios::app);
    if(sortie.fail()){
        cerr<< "Erreur: impossible d'ecrire dans le fichier"<< endl;
    }
    while(tSimulation < tStop){
        if((tSimulation<a) or (tSimulation>b)){
            InputCurrent = 0.0;
        }else{
            InputCurrent = I ;
            if(refractory_){
                MembranePotential_ = 0.0;
                RefractoryBreakTime_ += h;
                if(RefractoryBreakTime_>TAU){
					RefractoryBreakTime_= 0.0;
					refractory_= false;
				}
            }else if(MembranePotential_ > MembranePotentialTHRESHOLD){
                TimeSpikes_ = tSimulation;
                refractory_ = true;
            }
        }
        sortie << int2strg(MembranePotential_) << endl;
        MembranePotential_= (exp(-h/TAU)*MembranePotential_)+(InputCurrent*RESISTANCE*(1-exp(-h/TAU)));
        tSimulation +=  h;
    }
    sortie.close();
}

string Neuron::int2strg(double a) const{
    ostringstream s;
    s << a;
    string str = s.str();
    return str;
}

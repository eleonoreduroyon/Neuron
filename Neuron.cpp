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
#include <fstream> //maybe remove some

using namespace std;

//Constructeurs
Neuron::Neuron(): MembranePotential_(0.0), NbrSpikes_(0), TimeSpikes_(0),refractory_(false),
 RefractoryBreakStep_(0),InputCurrent_(0.0),tSimulation_(0){}


//Methodes
bool Neuron :: update(long StepsTaken){
    if(StepsTaken<=0){
        return false;
    }
    bool HasSpike(false);
    long tStop = tSimulation_+StepsTaken;
    while(tSimulation_ < tStop){
        if(MembranePotential_ > MembranePotentialTHRESHOLD){
            //Membrane potential is above threshold.
            refractory_ = true;
            HasSpike = true;
            //We store the spike and move on.
            TimeSpikes_ = tSimulation_;
            ++NbrSpikes_;
        }

        if(refractory_){
            //Neuron is refractory => reset memebrane potential to 0
            MembranePotential_ = 0.0;
            ++RefractoryBreakStep_;
            if(RefractoryBreakStep_ > REFRACTORYSTEP){
                RefractoryBreakStep_= 0.0;
                refractory_= false;
            }
        }else{
            MembranePotential_= (exp(-H/TAU)*MembranePotential_)+(InputCurrent_*20.0*(1-exp(-H/TAU)));
        }
    ++tSimulation_;
    }
    return HasSpike;
}

string Neuron::int2strg(double a) const{
    ostringstream s;
    s << a;
    string str = s.str();
    return str;
}

//Getters
double Neuron::GetMembranePotential_() const{
    return MembranePotential_;
}

long Neuron::GetTimeSpikes_() const{
    return TimeSpikes_;
}

//Setters
void Neuron::SetMembranePotential_(double MembranePotential){
    MembranePotential_=MembranePotential;
}
void Neuron::SetInputCurrent_(double InputCurrent){
    InputCurrent_=InputCurrent;
}

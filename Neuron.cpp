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
#include <cassert>

using namespace std;

//========================Constructeurs=======================
Neuron::Neuron(): MembranePotential_(0.0), NbrSpikes_(0), TimeSpikes_(0),refractory_(false), 
	RefractoryBreakStep_(0),InputCurrent_(0.0),tSimulation_(0){
        for(size_t n(0); n < DelaiSTEP+1;++n){
            Buffer_.push_back(0);
        }
      assert(TAU != 0);
      c1 = exp(-H/TAU);
      c2 = 20.0*(1-c1);
}

//=======================Destructeurs==========================
Neuron::~Neuron(){}

//========================Methodes=============================
bool Neuron :: update(long StepsTaken, long clock){
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
            //Reset BreakTime when over
            if(RefractoryBreakStep_ > REFRACTORYSTEP){
				MembranePotential_ = VRESET;
                RefractoryBreakStep_= 0.0;
                refractory_= false;
            }
        }else{
            MembranePotential_= (c1*MembranePotential_)+(InputCurrent_*c2);
            recieve(Buffer_[clock%(DelaiSTEP+1)]);
            Buffer_[clock%(DelaiSTEP+1)]=0;
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

void Neuron::recieve(int valeur){
	assert(valeur >= 0);
    MembranePotential_ += (valeur*JAMPLITUDE);
}

//====================Getters==================
double Neuron::GetMembranePotential_() const{
    return MembranePotential_;
}

long Neuron::GetTimeSpikes_() const{
    return TimeSpikes_;
}

vector<long> Neuron::GetBuffer_() const{
    return Buffer_;
}

//====================Setters====================
void Neuron::SetMembranePotential_(double MembranePotential){
    MembranePotential_=MembranePotential;
}
void Neuron::SetInputCurrent_(double InputCurrent){
    InputCurrent_=InputCurrent;
}

void Neuron::SetBuffer_(int i){
    Buffer_[i] += 1;
}


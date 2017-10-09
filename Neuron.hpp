//
//  Neuron.hpp
//  
//
//  Created by Ely on 10/2/17.
//
//

#pragma once 

#ifndef Neuron_hpp
#define Neuron_hpp

#include <string>

class Neuron{
    private:
//=============Attributs==============
    double MembranePotential_;
    long NbrSpikes_; //Num of spikes
    long TimeSpikes_; //Time of last spike
    bool refractory_; // Is Refractory or not
    long RefractoryBreakStep_; //Time after spike during which MembranePotential_ =0
    double InputCurrent_; // External Current
    long tSimulation_; //Internal Clock
    
    public:
//=============Constructeurs=========
    Neuron();
//=============Destructeur===========
    ~Neuron() = default;
//=============Methodes==============
    bool update(long StepsTaken);
    std::string int2strg(double a) const;
//=============Getters===============
    double GetMembranePotential_() const;
    long GetTimeSpikes_() const;
//=============Setters===============
    void SetMembranePotential_(double MembranePotential);
    void SetInputCurrent_(double InputCurrent);
};


#endif /* Neuron_hpp */

//
//  Neuron.hpp
//  
//
//  Created by Ely on 10/2/17.
//
//

#ifndef Neuron_hpp
#define Neuron_hpp

#include <string>
#include <vector>

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
    std::vector<long> Buffer_; //To deal with Delai
    double c1; //First Constant for the calculations of MembranePotential_
    double c2; //Second Constant for the calculations of MembranePotential_
    
    public:
//=============Constructeurs=========
    Neuron();
//=============Destructeur===========
    ~Neuron();
//=============Methodes==============
    bool update(long StepsTaken, long clock);
    void recieve(int valeur); //recieves stimulus from pre synaptic neuron
    std::string int2strg(double a) const; //converts int to string
//=============Getters===============
    double GetMembranePotential_() const;
    long GetTimeSpikes_() const;
    std::vector<long> GetBuffer_() const;
    long GetRefractoryBreakStep_() const;
    long GetNbrSpikes_() const;
//=============Setters===============
    void SetMembranePotential_(double MembranePotential);
    void SetInputCurrent_(double InputCurrent);
    void SetBuffer_(int i);
};


#endif /* Neuron_hpp */

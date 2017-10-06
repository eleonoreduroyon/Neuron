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

class Neuron{
    private:
//=============Attributs==============
        double MembranePotential_;
        int NbrSpikes_;
        double TimeSpikes_;
        bool refractory_;
        double RefractoryBreakTime_;
    
    public:
//=============Constructeurs=========
        Neuron();
        Neuron(double MembranePotential, int NbrSpikes, double TimeSpikes, bool refractory);
//=============Destructeur===========
       ~Neuron() = default;
//=============Methodes==============
        void update(double h, double I, double tStart, double tStop, double a , double b);
        std::string int2strg(double a) const;
};


#endif /* Neuron_hpp */

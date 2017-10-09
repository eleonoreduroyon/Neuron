//
//  main.cpp
//  
//
//  Created by Ely on 10/2/17.
//
//

#include "Neuron.hpp"
#include "Constants.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    ofstream sortie("MembranePotential", ios::out|ios::app);
    if(sortie.fail()){
        cerr<< "Erreur: impossible d'ecrire dans le fichier"<< endl;
    }

    Neuron N1;
    double Iext(1.01);
    long a(1000);
    long b(4000);
    long tStop(5000);
    bool HasSpikes(false);
    
    if (argc>1){
        Iext = atof(argv[1]);
    }
    
    for(int i(0);i<tStop; ++i){
        if((i<a) or (i>b)){  //outside the interval
            N1.SetInputCurrent_(0.0);
            N1.SetMembranePotential_(0.0);
        }else{
            N1.SetInputCurrent_(Iext);
            HasSpikes = N1.update(1);
            if(HasSpikes){
                cout<< "Spikes at t = "<< N1.GetTimeSpikes_()*H<<" ms." <<endl;
                HasSpikes = false;
            }
        }
         sortie << N1.int2strg(N1.GetMembranePotential_()) << endl;
    }
    sortie.close();
    
 
   
    return 0;
}



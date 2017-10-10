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
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
    ofstream sortie("MembranePotential", ios::out|ios::app);
    if(sortie.fail()){
        cerr<< "Erreur: impossible d'ecrire dans le fichier"<< endl;
    }

    vector<Neuron*> N1(2);
    
    double Iext(1.01);
    long a(1000);
    long b(4000);
    long tStop(5000);
    bool HasSpikes(false);
    long clock(0);
    
    if (argc>1){
        Iext = atof(argv[1]);
    }
    
    while(clock < tStop){
        for(size_t i(0); i< N1.size(); ++i){
            if((clock<a) or (clock>b)){  //outside the interval
                N1[i].SetInputCurrent_(0.0);
                N1[i].SetMembranePotential_(0.0);
            }else{
                N1[i].SetInputCurrent_(Iext);
                HasSpikes = N1[i].update(1);
                if(HasSpikes){
                    //we add a-tStart because tSimulation  starts at a
                    cout<< "Spikes at t = "<< (N1[i].GetTimeSpikes_()+a)*H<<" ms." <  <endl;
                    for(size_t j(0); j<N1[i].GetConnectedNeurons_.size(); ++j){
                            N1[i].GetConnectedNeurons_[j].recieve();
                    }
                    HasSpikes = false;
                }
            }
            sortie << N1[i].int2strg(N1[i].GetMembranePotential_()) << endl;
        }
        sortie.close();
        ++clock;
    }
 
   
    return 0;
}



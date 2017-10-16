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
#include <cstdlib>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]){
    ofstream sortie("MembranePotential", ios::out|ios::app);
    if(sortie.fail()){
        cerr<< "Erreur: impossible d'ecrire dans le fichier"<< endl;
    }
    
    int NbreNeuron(2);
    vector<Neuron> N1(NbreNeuron);
    
    assert(N1.size()!= 0);
    vector<vector<bool> > Connections(N1.size(), vector <bool> (N1.size()));
   
    //initialisation of the vector Connections
    for (size_t i(0); i< Connections.size(); ++i){
        for (size_t j(0); j< Connections[i].size(); ++j){
            Connections[i][j]=false;
        }
    }
   
   //the second neuron is connected to the first
    Connections[0][1]= true;
    
    
    double Iext(1.01);  //Amplitude of Current
    long a(1000);   //Start of Step Current
    long b(4000);   //End of Step Current
    long tStop(5000); //Total Simulation TIme
    bool HasSpikes(false);
    long clock(0);
    
    N1[0].SetInputCurrent_(Iext);
    N1[1].SetInputCurrent_(0.0);
    
    if (argc>1){
        Iext = atof(argv[1]);
    }
    
    while(clock < tStop){
        for(size_t i(0); i< N1.size(); ++i){
            if((clock<a) or (clock>b)){  //outside the interval
                N1[i].SetInputCurrent_(0.0);
                N1[i].SetMembranePotential_(0.0);
            }else{
				if(i==0){
					N1[i].SetInputCurrent_(Iext);
				} else{
					N1[i].SetInputCurrent_(0.0);
				}
                HasSpikes = N1[i].update(1, clock);
                if(HasSpikes){
                    //we add a-tStart because tSimulation  starts at a
                    cout<< "Spikes of "<< i+1 <<" at t = "<< (N1[i].GetTimeSpikes_()+a)*H << " ms." <<endl;
                   //
                    for(size_t j(0); j < Connections[i].size(); ++j){
                        if(Connections[i][j]){
                            N1[j].SetBuffer_(clock%(DelaiSTEP+1));
                        }
                    }
                    HasSpikes = false;
                }
            }
            sortie << N1[i].int2strg(N1[i].GetMembranePotential_()) << endl;
        }
        
        ++clock;
    }
 
   sortie.close();
    return 0;
}



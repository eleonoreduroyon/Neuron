//
//  main.cpp
//  
//
//  Created by Ely on 10/2/17.
//
//

#include "Neuron.hpp"

#include <iostream>

using namespace std;

int main(){
    Neuron N1;
    double h(.1);
    double I(15.0);
    double tStart(0.0); 
    double tStop(100.0);
    double a(20.0);
    double b(40.0);
    N1.update(h,I,tStart,tStop,a,b);
    return 0;
}

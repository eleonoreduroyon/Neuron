#include <iostream>
#include "Neuron.hpp"
#include "gtest/gtest.h"
#include <cmath>

//===============MembranePotentialValues============
TEST(NeuronTEST, PositiveInput){
	Neuron n;
	n.SetInputCurrent_(1.0);
	
	//First update test
	n.update(1, 1000);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0))- n.GetMembranePotential_(),0);
    
    //Test after several updates
    //*1*
    n.update(10000,1000);
        //MembranePotential_ should tend towards 20 but never spike
    EXPECT_EQ(0,n.GetNbrSpikes_());
    EXPECT_GT(1E-4, std::fabs(19.9999 - n.GetMembranePotential_()));
    //*2*
        //MembranePotential_ decay towards 0 without input current
    n.SetInputCurrent_(0.0);
    n.update(2000,1000);
    EXPECT_NEAR(0,n.GetMembranePotential_(), 1E-4);
}

TEST(NeuronTEST, NegativeInput){
    Neuron n;
    n.SetInputCurrent_(-1.0);
    
    //First update test
    n.update(1, 1000);
    EXPECT_EQ(-20.0*(1.0-exp(-0.1/20.0))- n.GetMembranePotential_(),0);
    
    //Test after several updates
    //*1*
    n.update(10000,1000);
        //MembranePotential_ should tend towards 20 but never spike
    EXPECT_EQ(0,n.GetNbrSpikes_());
    EXPECT_GT(1E-4, std::fabs(-19.9999 - n.GetMembranePotential_()));
    //*2*
        //MembranePotential_ decay towards 0 without input current
    n.SetInputCurrent_(0.0);
    n.update(2000,1000);
    EXPECT_NEAR(0,n.GetMembranePotential_(), 1E-4);
}

//=====================SpikeTime========================
TEST(NeuronTEST, TimeSpikes_){
	Neuron n;
	n.SetInputCurrent_(1.01);
    
    //Waiting for first spike
    n.update(924,1000);
    EXPECT_EQ(0,n.GetNbrSpikes_());
    n.update(1,1000);
    EXPECT_EQ(1, n.GetNbrSpikes_());
    EXPECT_EQ(0.0, n.GetMembranePotential_());
    
    //Waiting for second spike
    n.update(943,1000);
    EXPECT_EQ(1, n.GetNbrSpikes_());
    n.update(1);
    EXPECT_EQ(2, n.GetNbrSpikes_());
}

//=====================Post-Synaptic========================
TEST(NeuronTEST, NoPSSpike){
    Neuron n1;
    Neuron n2;
    n1.SetInputCurrent_(1.01);
    for(int i=0; i<925+DelaiSTEP; ++i){
        if(n1.update(1,1000+i)){
            EXPECT_EQ(0.0, n1.GetMembranePotential_());
        }
        n2.update(1,1000+i);
    }
    EXPECT_EQ(0.1,n2.GetMembranePotential_());
}

TEST(NeuronTEST, WithPSSpike){
    Neuron n1;
    Neuron n2;
    n1.SetInputCurrent_(1.01);
    n2.SetInputCurrent_(1.0);
    for(int i=0; i<1869+DelaiSTEP; ++i){
        if(n1.update(1,1000+i)){
            EXPECT_EQ(0.0, n1.GetMembranePotential_());
        }
        n2.update(1,1000+i);
    }
    
    //Before n2 spikes
    EXPECT_EQ(0,n2.GetNbrSpikes_());
    n2.update(1,1869+DelaiSTEP+1000);
    //After n2 spikes
    EXPECT_EQ(0,n2.GetMembranePotential_());
    EXPECT_EQ(1,n2.GetNbrSpikes_());
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

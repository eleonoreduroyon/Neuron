#include <iostream>
#include "Neuron.hpp"
#include "gtest/gtest.h"
#include <cmath>

TEST(NeuronTEST, MembranePotential_){
	Neuron n;
	n.SetInputCurrent_(1.0);
	
	//First update test
	n.update(1, 1000);
	EXPECT_EQ(20.0*(1.0-exp(-0.1/20.0))- n.GetMembranePotential_(),0);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

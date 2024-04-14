/*

 SpaceCraftDynamics.cpp

 This File inherits from the DynamicModel base class and is where I implement
 a Space Craft orbiting from the moon



    Written by: Ricardo Rosales-Mesta
    MECHANICAL ENGINEERING 535.741
     
    Code style and framework taken from Prof. Urban's Optimal Control Theory  
    and Reinforcement Learning class Module 3 Problem Set

 
 */

#include "SpaceCraftDynamics.h"
#include <string>

using namespace std;

SpaceCraftDynamics::~SpaceCraftDynamics()
{
	delete randomMgr;
	cout << "Derived Class Destructor " << moduleName << endl;
}

SpaceCraftDynamics::SpaceCraftDynamics(int ID, char *fname, bool printFlag) :
		DynamicModel(ID, fname, printFlag),
		time_(0.0),
		init_time_(0.0),
		rn_pos_Proc(0),
		rn_vel_Proc(0)
{
	moduleName = fname;
	moduleName = moduleName + "_" + to_string(ID);
	cout << "Registering module: " << moduleName << endl;
    
    //define constants
	R = 1737000.4;  
	D = R + 400000;
	g = 1.62;
	M = 300;
	T = 90000;

	numStates_ = 4;
	setStateSize(numStates_); // Initializes the dynamic arrays in DynamicModel base class

	// This initializes the RandomNumberManager
    char name[]="randomMgr";
    randomMgr = new RandomNumberManager(1, name);

/*
 	 Define your states here so you have a consistent view of them

 	 x(0) -> x1 = r
 	 x(1) -> x2 = alpha
	 x(2) -> x3 = r_dot
	 x(3) -> x4 = r*alpha_dot

 */

};

void SpaceCraftDynamics::Init(int runNum, double *x0)
{
	integrateType_ = modelParams.integrationType;
	init_time_ = modelParams.init_time;

	time_ = init_time_;

	for (int i=0; i<numStates_; i++)
	{
		x_[i] = x0[i];
		x_init_[i] = x0[i];
	}

	Derivative(x_, time_);
}


void SpaceCraftDynamics::ReInit(int runNum)
{
	time_ = init_time_;

	for (int i=0; i<numStates_; i++)
	{
		x_[i] = x_init_[i];
	}

	Derivative(x_, 0);

	if (printFlag)
	{
		fprintf(p_node,"]; \n");

		fprintf(p_node,"x%i=[ \n", runNum);
	}
}

void SpaceCraftDynamics::Update(double *y_out)
{
	//double rv_pos;
	//double rv_vel;

	

	// CODE

	//pass on states 

	y_out[0] = x_[0]; //+ noise; // CODE
	y_out[1] = x_[1]; // + noise ;// CODE
	y_out[2] = x_[2]; 
	y_out[3] = x_[3];

	return;
}

void SpaceCraftDynamics::Derivative(double *x, double time)
{
	//double x1, x2, x3, x4;
	// map 
    double x1 = x[0]; // r
    double x2 = x[1]; // alpha
    double x3 = x[2]; // alpha*r dot
    double x4 = x[3]; // r*alpha dot
	double beta;

	// dynamic system defined 
    double x1_dot = x3;
    double x2_dot = x4 / x1;
    double x3_dot = (x4 * x4) / x1 - (g * R * R) / (x1 * x1) + (T / M) * sin(beta);
    double x4_dot = -(x3 * x4) / x1 + (T / M) * cos(beta);

	// update 
    x_dot_[0] = x1_dot;
    x_dot_[1] = x2_dot;
    x_dot_[2] = x3_dot;
    x_dot_[3] = x4_dot;
}

void SpaceCraftDynamics::State_Constraints()
{

}

void SpaceCraftDynamics::printStates(double time)
{

	fprintf(p_node,"%16.6f ", time);

	for (int i=0; i < numStates_; i++)
	{
		fprintf(p_node, " %16.6f ",x_[i]);
	}
	fprintf(p_node, "\n");

	return;

}


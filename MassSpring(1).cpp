/*

 MassSpring.cpp

 This File inherits from the DynamicModel base class and is where I implement
 a Mass Spring dynamic system

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu

      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#include "MassSPring.h"
#include <string>

using namespace std;

MassSpring::~MassSpring()
{
	delete randomMgr;
	cout << "Derived Class Destructor " << moduleName << endl;
}

MassSpring::MassSpring(int ID, char *fname, bool printFlag) :
		DynamicModel(ID, fname, printFlag),
		time_(0.0),
		init_time_(0.0),
		rn_pos_Proc(0),
		rn_vel_Proc(0)
{
	moduleName = fname;
	moduleName = moduleName + "_" + to_string(ID);
	cout << "Registering module: " << moduleName << endl;

	m = 2;
	k = 10;
	b = 3;

	numStates_ = 2;
	setStateSize(numStates_); // Initializes the dynamic arrays in DynamicModel base class

	// This initializes the RandomNumberManager
    char name[]="randomMgr";
    randomMgr = new RandomNumberManager(1, name);

/*
 	 Define your states here so you have a consistent view of them

 	 x(0) - x
 	 x(1) - x_dot (which is velocity)

 */

};

void MassSpring::Init(int runNum, double *x0)
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


void MassSpring::ReInit(int runNum)
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

void MassSpring::Update(double *y_out)
{
	double rv_pos;
	double rv_vel;

	// You should get your measurement noise RVs here, what call should you make?
	//

	// CODE


	// The first two outputs need to modified, how?

	y_out[0] = x_[0]; // CODE
	y_out[1] = x_[1]; // CODE
	y_out[2] = rv_pos;
	y_out[3] = rv_vel;

	return;
}

void MassSpring::Derivative(double *x, double time)
{

	double x_pos, x_dot, x_dot_dot;

	x_pos = x[0];
	x_dot = x[1];

	x_dot_dot = (-b*x_dot - k*x_pos)/m;

	x_dot_[0] = x_dot;
	x_dot_[1] = x_dot_dot;

}

void MassSpring::State_Constraints()
{

}

void MassSpring::printStates(double time)
{

	fprintf(p_node,"%16.6f ", time);

	for (int i=0; i < numStates_; i++)
	{
		fprintf(p_node, " %16.6f ",x_[i]);
	}
	fprintf(p_node, "\n");

	return;

}


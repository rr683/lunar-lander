/*

 Model.cpp

 This File inherits from the DynamicModel base class and is where you can implement
 any specific model of a dynamic system

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu

      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#include "Model.h"
#include <string>

using namespace std;

Model::~Model()
{
	cout << "Derived Class Destructor " << moduleName << endl;
	delete randomMgr;
}

Model::Model(int ID, char *fname, bool printFlag) :
		DynamicModel(ID, fname, printFlag),
		time_(0.0),
		init_time_(0.0),
		randomMgr(nullptr),
		rvThetaId(0),
		rvPosId(0)
{
	moduleName = fname;
	moduleName = moduleName + "_" + to_string(ID);
	cout << "Registering module: " << moduleName << endl;

	/*
	 	 Define your states here so you have a consistent view of them

	 	 x(0) - Theta
	 	 x(1) - Theta_dot
	 	 x(2) - Pos (x)
	 	 x(3) - Velocity (x_dot)

	 */

	// CODE
	numStates_ = 4;
	setStateSize(numStates_);


    char name[]="randomMgr";
    randomMgr = new RandomNumberManager(1, name);

};

void Model::Init(int runNum, double *x0)
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

	// Initialize your random number streams here
	//unsigned long int x_long = 123456789;


	// CODE
	//noise for angle
	rvThetaId = randomMgr -> registerRandomProcess(123456789+4,
									   RandomNumberManager::RandomNumType::Gaussian,
									   0, 0.1);

	//noise for position
	rvPosId = randomMgr -> registerRandomProcess(123456789+5,
									   RandomNumberManager::RandomNumType::Gaussian,
									   0, 0.5);

}

void Model::ReInit(int runNum)
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

void Model::Update(double *y_out)
{
	// You should get your measurement noise RVs here, what call should you make?

	double randVarThta;
	double randVarPos;

	// CODE

	//invoke method from randomMgr

	// fix this issue

	randVarThta = randomMgr->getRandomNumber(rvThetaId);
	randVarPos = randomMgr->getRandomNumber(rvPosId);

	y_out[0] = x_[0] + randVarThta;
	y_out[1] = x_[2] + randVarPos;
	//cout << "vt: " << randVarThta << " vp: " << randVarPos<< endl;
	y_out[2] = randVarThta;
	y_out[3] = randVarPos;


	return;
}

void Model::Derivative(double *x, double time)
{
	// This is where most of the model details go

	double m=.1, M=2.0, l=0.5, I=0.008333, g=9.81;

	double theta_double_dot, pos_double_dot;

	// CODE
	// mapping as seen above in comment
	double theta = x[0];
	double theta_dot = x[1];
	double pos = x[2];
	double vel = x[3];

	// dynamic equations and matrix set up
	double u_drive = sin(time);
	double a = I + m*l*l;
	double b = -m*l*cos(theta);
	double c = -m*l*cos(theta);
	double d = M + m;

	double determinant = a*d - b*c;
	//print(determinant)
	//determinant = 1.0;
	double B11 = m*g*l*sin(theta);
	double B21 = u_drive - m*l*pow(theta_dot,2)*sin(theta);
	double inverseA11 = d/determinant;
	double inverseA12 = -b/determinant;
	double inverseA21 = -c/determinant;
	double inverseA22 = a/determinant; 

	// x = inv(A)*B
	theta_double_dot = inverseA11*B11 + inverseA12*B21;
	pos_double_dot = inverseA21*B11 + inverseA22*B21;

	x_dot_[0] = theta_dot;
	x_dot_[1] = theta_double_dot;
	x_dot_[2] = vel;
	x_dot_[3] = pos_double_dot;
}

void Model::State_Constraints()
{

}

void Model::printStates(double time)
{
	cout<<"nStates: " <<numStates_ <<endl;

	fprintf(p_node,"%16.6f ", time);

	for (int i=0; i < numStates_; i++)
	{
		fprintf(p_node, " %16.6f ",x_[i]);
	}
	fprintf(p_node, "\n");

	return;

}

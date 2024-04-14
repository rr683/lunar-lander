/*

 SpaceCraftDynamics.h

 This File inherits from the DynamicModel base class and is I have implemented
 a Spacecraft Dynamics operating in the gravitational field of the moon. 


    Written by: Ricardo Rosales-Mesta
    MECHANICAL ENGINEERING 535.741

    Code style and framework taken from Prof. Urban's Optimal Control Theory  
    and Reinforcement Learning class Module 3 Problem Set


 */

#ifndef SPACECRAFTDYNAMICS_H_
#define SPACECRAFTDYNAMICS_H_


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "DynamicModel.h"
#include "SimConstants.h"

#include "RandNumGenerator.h"

using namespace SimConstants;

using namespace std;

class SpaceCraftDynamics : public DynamicModel
{
	public:

		SpaceCraftDynamics(int id, char *fname, bool printFlag);
		~SpaceCraftDynamics();

		ModelParams modelParams;

		virtual void Update(double *y_out) override;
		virtual void Derivative(double *x, double time) override;
		virtual void State_Constraints() override;

		virtual void Init(int runNum, double *x0) override;
		virtual void ReInit(int runNum) override;
		virtual void printStates(double time) override;

	protected:


	private:

		string moduleName;

		double time_;
		double init_time_;

        // define relevnt parameters. 
		double R, D, g, M, T;
		double beta = pi/2;

		// This is for managing the Random Processes

		RandomNumberManager *randomMgr;
		int rn_pos_Proc;
		int rn_vel_Proc;

};


#endif /* SPACECRAFTDYNAMICS_H_ */

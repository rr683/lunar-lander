/*

 MassSpring.h

 This File inherits from the DynamicModel base class and is I have implemented
 a Mass Spring System

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu

      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#ifndef MASSSPRING_H_
#define MASSSPRING_H_


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#include "DynamicModel.h"
#include "SimConstants.h"

#include "RandNumGenerator.h"

using namespace SimConstants;

using namespace std;

class MassSpring : public DynamicModel
{
	public:

		MassSpring(int id, char *fname, bool printFlag);
		~MassSpring();

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

		double m, k, b;

		// This is for managing the Random Processes

		RandomNumberManager *randomMgr;
		int rn_pos_Proc;
		int rn_vel_Proc;

};


#endif /* MASSSPRING_H_ */

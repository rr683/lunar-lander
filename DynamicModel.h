/*
 DynamicModel.h

 This File is the base class for a DynamicModel. This file provides the structure that
 all Dynamic Models must have (and inherit), specific models are implemented in a derived class.

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu

      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#ifndef DYNAMICMODEL_H_
#define DYNAMICMODEL_H_

#include <iostream>

using namespace std;

class DynamicModel
{
	public:

		struct ModelParams
		{
			int integrationType;
			double init_time;
		};

		DynamicModel(bool printFlag);
		DynamicModel(int id, char *fname, bool printFlag);

		virtual ~DynamicModel();

		void setStateSize(int numStates);

		virtual void Init(int runNum, double *x);
		virtual void ReInit(int runNum);
		virtual void Update(double *y_out);
		virtual void Derivative(double *x, double time);
		virtual void Integrate(double time, double dt);
		virtual void State_Constraints();

		int getNumStates();
		void getStates(double time, double *x_out);
		virtual void printStates(double time);

	protected:

		FILE *p_node;

		int id;
		string moduleName;

		int numStates_;
		int integrateType_;
		double init_time_;
		int runNum_;

		void Euler(double time, double dt);
		void AB2(double time, double dt);
		void ABAM(double time, double dt); //Question2 
		void RK2(double time, double dt);
		void RK4(double time, double dt);

		double *x_init_;
		double *x_; //State
	    double *x_dot_; //Derivatives
	    double *x_dot_past_; //P1 Time step prior derivative

	    double *X1;
	    double *X2;

		bool printFlag;

	private:
};



#endif /* DYNAMICMODEL_H_ */

/*

 RandNumGenerator.h

 This provides the mechanisms for a random number generator and implements
 both Uniform and Gaussian random processes

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu

      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#ifndef RANDNUMGENERATOR_H_
#define RANDNUMGENERATOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "SimConstants.h"

using namespace SimConstants;

using namespace std;

class RandomNumberManager
{
	public:

		enum RandomNumType
		{
			Uniform,
			Gaussian
		};

		struct RandomNumberObject
		{
			RandomNumType type;
			int id;
			unsigned long int x;
			unsigned long int y;
			unsigned long int z;
			unsigned long int w;
			double a;
			double b;
			double sigma;
			double mean;
		};

		RandomNumberManager(int id, char *fname);
		~RandomNumberManager();

		int registerRandomProcess(unsigned long int x_, RandomNumType type_, double a, double b);

		double getRandomNumber(int id_);

	protected:

		double generateRandomVariable(int id_);

	private:

		int procId;
		double scale;

		// This creates a vector list of the random process streams accessed by id
		vector<RandomNumberObject> processList;
};


#endif /* RANDNUMGENERATOR_H_ */

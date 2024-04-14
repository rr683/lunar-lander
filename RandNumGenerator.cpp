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

#include "RandNumGenerator.h"
#include "SimConstants.h"
#include <math.h>


RandomNumberManager::RandomNumberManager(int id, char *fname)
{
	procId = 0;
	scale = 1.0 / ( pow(2,32) - 1 );
}

RandomNumberManager::~RandomNumberManager()
{
}

int RandomNumberManager::registerRandomProcess(unsigned long int x_, RandomNumType type_, double a, double b)
{
	RandomNumberObject randObject;
	int procId_ = procId;

	// randObject variables are accessed by the following notation
	randObject.x = x_; // x_ is the initial seed for the process


	// What other portions of randObject can be defined here?
	// Hint: It should be common to either type of process...

	// CODE
	//randObject.type = type_; 
	//randObject.a = a;
	//randObject.b = b;





	if (type_ == Uniform)
	{
		// What parts of the object randObject need to be initialized here?
		// Hint: It should be specific to Uniform

		// CODE
	
		//unsigned long int t=0;
		randObject.x = 123456789;
		randObject.y = 362436069;
		randObject.z = 521288629;
		randObject.w = 88675123;
		randObject.a = a;
		randObject.b = b;
		randObject.id = procId;


		processList.push_back(randObject);
		procId = procId + 1;

	}
	else if (type_ == Gaussian)
	{
		// What parts of the object randObject need to be initialized here?
		// Hint: It should be specific to Gaussian

		// CODE
		RandomNumberObject randObject1;
		randObject1.id = procId;
		randObject1.x = 123456789+1;
		randObject1.y = 362436069;
		randObject1.z = 521288629;
		randObject1.w = 88675123;
		randObject1.mean = a;
		randObject1.sigma = b;


		// Remember a Gaussian RV needs two uniform RV streams
		// Define first
		// Gaussian needs to RV (U) streams, here is the second one:
		
		// CODE
		processList.push_back(randObject1);
		procId = procId + 1;

		RandomNumberObject randObject2;
		randObject2.id = procId;
		randObject2.x = 123456789+2;
		randObject2.y = 362436069;
		randObject2.z = 521288629;
		randObject2.w = 88675123;
		randObject2.mean = a;
		randObject2.sigma = b;

		processList.push_back(randObject2);
		procId = procId + 1;
	}

	return procId_;
}

double RandomNumberManager::getRandomNumber(int id_)
{
	double rv, big_X; 	// Final RV output
	double U1, U2; 		// Temporary Uniform(0,1) RV variables

	switch (processList[id_].type)
	{

	case Uniform :

		// What Equation for Uniform RVs should go here?

		// CODE
		U1 = generateRandomVariable(id_);
		// Based on processList(id_)
		rv = processList[id_].a + 
			 (processList[id_].b * - processList[id_].a)*U1;

		break;

	case Gaussian :

		// What Equation for Gaussian RVs should go here?

		// CODE Get U1 and U2 from the uniform Random Number Generator id_ and id_ + 1

		// U1 ~ Based on processList(id_) and U2 ~ processList(id_+1)
		U1 = generateRandomVariable(id_);
		U2 = generateRandomVariable(id_ + 1);
		// equation Module 3C
		big_X = sqrt(-2*log(U1))*(cos(2*pi*U2));
		rv = big_X*processList[id_].sigma + processList[id_].mean;

		cout << "rv value:" << rv << endl;
		break;
	}

	return rv;
	
}

double RandomNumberManager::generateRandomVariable(int id_)
{
	double rv;
	unsigned long int t=0;
	unsigned long int x = 123456789+3;
	unsigned long int y = 362436069;
	unsigned long int z = 521288629;
	unsigned long int w = 88675123;

	// What code should be provided here?
	// Hint: This should generate the uniform[0,1] random number stream

   // CODE
   // Module 3C/D
   // t = (1664525 * processList[id_].x + 1013904223) % (unsigned long int)(pow(2, 32));
    processList[id_].x = x;
	t = x^(x<<11);
	x = y;
	y = z;
	z = w;
	w = (w^(w>>19))^(t^(t>>8));
    rv = (double)w / (1/scale);


	return rv;
}







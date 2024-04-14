/*
This File Controls Execution of a Dynamic simulation

      Copyright (c) 2019

      Written by: Thomas J. Urban
      Phone:      (443) 778-7605
      email:      thomas.urban@jhuapl.edu
      Copyright:  This subroutine is the sole property of Johns Hopkins University
                  Whiting School of Engineering and may not be used or duplicated
                  without the express permission of the Johns Hopkins University
                  Whiting School of Engineering.
 */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <chrono>

#include "SimExec.h"
#include "RandNumGenerator.h"

using namespace std;

// HELP
/*
 * This File is the top level file of the simulation. You will use this to setup
 * and run the simulation and you can also use it to write a file to test
 * your random number generator implementation
 *
 */

int main() {

    //---------------------------------------------------
	//
	// This code just starts a timer because I like to know how long things take
    auto start = std::chrono::system_clock::now();
    auto start_time = std::chrono::system_clock::to_time_t(start);

    cout << endl;cout<< endl;
    cout << "Starting simulation at " << ctime(&start_time) << endl;

    //---------------------------------------------------
    //
    // The following section of code: 1- defines an object mySim of type SimExec
    // and executes the simulation. The code actually just loops until mySim status
    // changes to done (0)

    SimExec mySim(1,1);

    while ( mySim.Status() )
    {
    	mySim.Run();

    }

    //---------------------------------------------------
    //
    // The following section of code can be used to complete Problem 3
    // it will define the random processes for the Uniform and Gaussian RVs
    // draw 10,000 numbers of both, and write to a file....

    // This defines an object myRandomNumberManager of type RandomNumberManager

    char name[]="myRandomNumberManager";
    RandomNumberManager myRandomNumberManager(1, name);

    FILE *p_node; // This defines a pointer for a file to write the random numbers

	p_node=fopen("randomNums.m", "w"); // Open a file randomNums.m
	fprintf(p_node,"x=[ \n");

	// Define variables to "hold" the id for the RV process stream

	int rvNumStream_Uniform; // Define a variable for the Uniform Random Number Stream
	int rvNumStream_Gaussian; // Define a variable for the Uniform Random Number Stream

	// Register random processes for the two random number streams

	// CODE
    //int id1 = myRandomNumberManager(123456789,'Uniform', 0.0, 20.0);
    rvNumStream_Uniform = myRandomNumberManager.registerRandomProcess(123456789, RandomNumberManager::RandomNumType::Uniform,12.0,4.0);
    rvNumStream_Gaussian = myRandomNumberManager.registerRandomProcess(123456789+1, RandomNumberManager::RandomNumType::Gaussian, 12.0, 4.0);


	// Question? What values were given to rvNumStream_Uniform and rvNumStream_Gaussian?

    double rv1, rv2;
    for (int j = 0; j<10000; j++) // Loop 10,000 times
    {
    	for (int rnProc=0; rnProc < 2; rnProc++) // Why 0 <= rnProc < 2? See question above
    	{
            if(rnProc ==0) {
                rv1 = myRandomNumberManager.getRandomNumber(rvNumStream_Uniform);

            }
            else {
                rv2 = myRandomNumberManager.getRandomNumber(rvNumStream_Gaussian);

            }
    

    		// CODE
    		fprintf(p_node, "%d %16.6f %16.6f ",rv1, rv2); // This write the RV out and leaves a space
    	}

    	fprintf(p_node, " \n "); // This creates a new line

    }

    cout << endl;

    cout << endl;

    fprintf(p_node, " ]; "); // End the file with a ] (for MATLAB)
    fclose(p_node); // Close the file

    //---------------------------------------------------
	//
	// This code completes the timer

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    auto end_time = chrono::system_clock::to_time_t(end);

    cout << endl;cout << endl;
    cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

	return 0;

}

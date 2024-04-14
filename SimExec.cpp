/*

 SimExec.h

 This File provides the Simulation framework for simulating Dynamic Models

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
#include <stdlib.h>
#include <iostream>
#include "math.h"

#include "Model.h"
#include "MassSpring.h"
#include "SpaceCraftDynamics.h"
#include "SimExec.h"
#include "SimConstants.h"

SimExec::SimExec(int ID, int RunsPerSim):
	id(0),
	runsPerSim(0),
	time(0.0),
	dt(0),
	end_time(0),
	run_status(0),
	time_Tolerance(0),
	stop_flag(true)
{
	// Initialize the simulation variables

	cout << "Initializing Simulation ID=" << id << endl;

	id = ID;
	runsPerSim = RunsPerSim;
	time = 0;
	dt = .01;
	end_time = 480;
	run_status = 1;
	time_Tolerance = 1e-8;
	stop_flag = false;
}

SimExec::~SimExec()
{
	cout << "Terminating Simulation ID=" << id << endl;
}

int SimExec::Status()
{
	return run_status;
}

void SimExec::Run()
{
	/*
	// This is my example Mass Spring system
	char name1[]="MassSpring";
	MassSpring massSpring(2, name1, true);

	massSpring.modelParams.integrationType = 4;
	massSpring.modelParams.init_time = 0.0;

	double x1_0[2]={1.0, 0};  // Define a vector of initial conditions
	double y1[4]; // 2 outputs for x, v, RV_pos, RV_vel

	//--------------------------------------------------------------------------
	// Define the Model for the Inverted Pendulum

	char name[]="invPend";
	Model invPend(1, name, true);

	// CODE
	invPend.modelParams.init_time = 0.0;
	invPend.modelParams.integrationType = 5;

	double x0[4] = {0.0, 0.0, 0.0, 0.0};
	double y2[4];
	invPend.Init(1, x0);

	*/

	char name2 [] = "SpaceCraft";
	SpaceCraftDynamics SpaceCraft(1, name2, true);

	SpaceCraft.modelParams.init_time = 0.0;
	SpaceCraft.modelParams.integrationType = 5; //RK4
	
	double x3[4] = {1737000.4, 0.5, 0.5, 0.5}; //{r, alpha, rdot, alphadot} initial conditions
	double y3[4];
	//SpaceCraft.Init(1,x3);



	//--------------------------------------------------------------------------
	// Open a file for the output of the simulation

    FILE *p_node1, *p_node2, *p_node3;

	//p_node1=fopen("MassSpringOutput.m", "w");
	//fprintf(p_node1,"y1=[ \n");

	//p_node2=fopen("InvPendOutput.m", "w");
	//fprintf(p_node2,"y2=[ \n");

	// p_node 3 to open .m file
	p_node3=fopen("SpaceCraftOut.m", "w");
	fprintf(p_node3,"y3=[ \n");


	//--------------------------------------------------------------------------
	// Execute the simulation

	int runCount = 1;
	while (runCount <= runsPerSim)
	{

		// Initialize the model
		//massSpring.Init(1, x1_0);

		// CODE
		//invPend.Init(1, x0);
		SpaceCraft.Init(1, x3);

		// Print Mass Spring initial state
		//massSpring.printStates(time);
		SpaceCraft.printStates(time);
		// CODE
		//invPend.printStates(time);
		SpaceCraft.printStates(time);
		// Loop the Sim until done
		while ( !stop_flag )
		{
			cout << "Time: " << time << endl;

			//massSpring.Integrate(time, dt);

			// CODE
			//invPend.Integrate(time, dt);
			SpaceCraft.Integrate(time, dt);
			time = time + dt;

			//---------------------------------------------------------
			// Collect output of Mass Spring and print to file

			/*
			//massSpring.Update(y1);
			//massSpring.printStates(time);

			

    		fprintf(p_node1, " %16.6f ",time);
	    	for (int i=0; i< 4; i++) // How big is y1?
	    	{
	    		fprintf(p_node1, " %16.6f ",y1[i]);
	    	}

	    	fprintf(p_node1, " \n ");

	    	//---------------------------------------------------------
	    	// Collect output of Inverted Pendulum

	    	// CODE
			invPend.Update(y2);
			invPend.printStates(time);

			fprintf(p_node2, " %16.6f ",time);
	    	for (int i=0; i< 4; i++) // How big is y1?
	    	{
	    		fprintf(p_node2, " %16.6f ",y2[i]);
	    	}

	    	fprintf(p_node2, " \n ");

			*/

	    	//---------------------------------------------------------
			//Collect output of Spacecraft Dynamics Model

			SpaceCraft.Update(y3);
			SpaceCraft.printStates(time);

			fprintf(p_node3, " %16.6f ",time);
	    	for (int i=0; i< 4; i++) // How big is y1?
	    	{
	    		fprintf(p_node3, " %16.6f ",y3[i]);
	    	}

	    	fprintf(p_node3, " \n ");


			// Check stopping condition
			if ( abs((time - end_time)) < time_Tolerance || time < -.05)
			{
				cout << "Time: " << time << endl;

				stop_flag  = true;
			}
		}

		// Close the files
		/*
	    fprintf(p_node1, " ]; ");
	    fclose(p_node1);

	    fprintf(p_node2, " ]; ");
	    fclose(p_node2);
		*/

		fprintf(p_node3, "]; ");
		fclose(p_node3);


		cout << "Finished Run " << runCount << endl;
		cout << endl;

		runCount = runCount + 1;
	}

	run_status = 0;
}

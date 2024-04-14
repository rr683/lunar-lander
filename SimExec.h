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

#ifndef SIMEXEC_H_
#define SIMEXEC_H_

using namespace std;

class SimExec
{
	public:

		SimExec(int id, int runsPerSim);
		~SimExec();

		void Run();
		int Status();

	protected:

	private:

		int id;
		int runsPerSim;

		double time, dt, end_time;

		int run_status;
		double time_Tolerance;
		bool stop_flag;

};


#endif /* SIMEXEC_H_ */

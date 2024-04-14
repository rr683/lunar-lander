/*
 * SimConstants.h
 *
 *  Created on: May 17, 2019
 *      Author: urbantj1
 */

#ifndef SIMCONSTANTS_H_
#define SIMCONSTANTS_H_

#include <math.h>

namespace SimConstants
{
	static const double m2ft = 3.280833333333540;
	static const double ft2m = 0.3048006096012;
    static const double in2ft = 1.0/12.0;
	static const double in2m = in2ft*ft2m;
	static const double inch_meter = in2ft*ft2m;

	static double lbm_kg = 0.45359237;
	static double lbm_in2_kg_m2 = 0.000292639653429;

	static double pi = asin(1)*2;
	static double r2d = 180/pi;
	static double d2r = pi/180;
}

#endif /* SIMCONSTANTS_H_ */

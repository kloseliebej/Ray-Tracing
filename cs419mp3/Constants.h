#ifndef __CONSTANTS__
#define __CONSTANTS__
//#419begin #type=<1> #src=<http://josephconley.com/blog/2008/9/12/ray-tracer.html>
#include <stdlib.h>
#include "MyRGBColor.h"

const double 	PI 			= 3.1415926535897932384;
const double 	TWO_PI 		= 6.2831853071795864769;
const double 	PI_ON_180 	= 0.0174532925199432957;
const double 	invPI 		= 0.3183098861837906715;
const double 	invTWO_PI 	= 0.1591549430918953358;

const double 	kEpsilon 	= 0.00000001;
const double	kHugeValue	= 1.0E10;

const MyRGBColor	black(0.0);
const MyRGBColor	white(1.0);
const MyRGBColor	red(1.0, 0.0, 0.0);

const float 	invRAND_MAX = 1.0 / (float)RAND_MAX;

#endif

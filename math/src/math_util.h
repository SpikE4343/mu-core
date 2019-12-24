#ifndef __math_util_h_INCLUDED__
#define __math_util_h_INCLUDED__

#include "vector.h"

#define MAX(a,b) (((a) < (b)) ? b : a)
#define MIN(a,b) (((a) > (b)) ? b : a)

#define CLAMP(m, v, mx) (MAX(m, MIN(v, mx)))


float standardDeviation(Vector3f_t* samples, int axis, int count, float average);

#endif
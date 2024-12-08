#include "solve.h"

// a0x0 + a1x1 = c0
// b0x0 + b1x1 = c1
//
// b0(a0x0 + a1x1) = b0(c0)
// a0(b0x0 + b1x1) = a0(c1)
//
// a0b0(x0) + a1b0(x1) = b0c0
// a0b0(x0) + a0b1(x1) = a0c1
//
// (a1b0 - a0b1)x1 = (b0c0 - a0c1)
void two_solve(double a0,
			   double a1,
			   double c0,
			   double b0,
			   double b1,
			   double c1,
			   double *x0,
			   double *x1) {
	double m1 = a1*b0 - a0*b1,
		   y1 = b0*c0 - a0*c1;

	assert(m1 != 0);

	*x1 = y1 / m1;
	*x0 = (c0 - a1 * (*x1)) / a0;
}

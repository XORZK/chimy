#ifndef SOLVE_H
#define SOLVE_H

#pragma once
#include <stdio.h>
#include <assert.h>

// a0x0 + a1x1 = c0
// b0x0 + b1x1 = c1
void two_solve(double a0,
			   double a1,
			   double c0,
			   double b0,
			   double b1,
			   double c1,
			   double *x0,
			   double *x1);

#endif

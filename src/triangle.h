#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include "vec.h"
#include <stdbool.h>

typedef struct {
	v2 vt1;
	v2 vt2;
	v2 vt3;
} triangle;

triangle* create_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

void delete_triangle(triangle *t);

// barycentric
// https://blackpawn.com/texts/pointinpoly/default.html
bool in_triangle(v2 v, v2 p1, v2 p2, v2 p3);

void print_triangle(triangle *t);

#endif

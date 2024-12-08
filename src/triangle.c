#include "triangle.h"
#include <stdlib.h>

triangle* create_triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
	triangle *t = (triangle*) malloc(sizeof(triangle));

	t->vt1.x = x1;
	t->vt1.y = y1;
	t->vt2.x = x2;
	t->vt2.y = y2;
	t->vt3.x = x3;
	t->vt3.y = y3;

	return t;
}

void delete_triangle(triangle *t) {
	if (t)
		free(t);
}

bool in_triangle(v2 p, v2 A, v2 B, v2 C) {
	v2 s0 = { C.x - A.x, C.y - A.y },
	   s1 = { B.x - A.x, B.y - A.y },
	   s2 = { p.x - A.x, p.y - A.y };

	double d00 = dot(&s0, &s0, 2),
		   d01 = dot(&s0, &s1, 2),
		   d02 = dot(&s0, &s2, 2),
		   d11 = dot(&s1, &s1, 2),
		   d12 = dot(&s1, &s2, 2);

	// d02 = d00u + d01v
	// d12 = d01u + d11v
	// d11(d02) = d11d00u + d11d01v
	// d01(d12) = d01d01u + d01d11v
	// d01d12 - d02d11 = (d01d01 - d11d00)u
	double u = (d01*d12 - d02*d11)/(d01*d01 - d00*d11),
		   v = (d02 - d00 * u)/(d01);

	return (u >= 0 && v >= 0 && u + v <= 1);
}

void print_triangle(triangle *t) {
	if (!t)
		return;

	v2 p1 = t->vt1, p2 = t->vt2, p3 = t->vt3;
	printf("{(%f, %f), (%f, %f), (%f, %f)}\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

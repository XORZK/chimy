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

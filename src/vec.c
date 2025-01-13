#include "vec.h"
#include <math.h>
#include <stdlib.h>

v2* create_v2(double x, double y) {
	v2 *v = (v2*) malloc(sizeof(v2));

	v->x = x;
	v->y = y;

	return v;
}

v3* create_v3(double x, double y, double z) {
	v3 *v = (v3*) malloc(sizeof(v3));

	v->x = x;
	v->y = y;
	v->z = z;

	return v;
}

v4* create_v4(double x1, double x2, double x3, double x4) {
	v4 *v = (v4*) malloc(sizeof(v4));

	v->x1 = x1;
	v->x2 = x2;
	v->x3 = x3;
	v->x4 = x4;

	return v;
}

v3i* create_v3_int(int x, int y, int z) {
	v3i* v = (v3i*) malloc(sizeof(v3i));

	v->x1 = x;
	v->x2 = y;
	v->x3 = z;

	return v;
}

void* add_v(void *a1, void *a2, size_t s) {
	switch (s) {
		case (2): {
			v2 *p1 = (v2*) a1, *p2 = (v2*) a2;
			return (void*) create_v2(p1->x + p2->x,
									 p1->y + p2->y);
	    }
		case (3): {
			v3 *p1 = (v3*) a1, *p2 = (v3*) a2;
			return (void*) create_v3(p1->x + p2->x,
									 p1->y + p2->y,
									 p1->z + p2->z);
		}
		case (4): {
			v4 *p1 = (v4*) a1, *p2 = (v4*) a2;
			return (void*) create_v4(p1->x1 + p2->x1,
									 p1->x2 + p2->x2,
									 p1->x3 + p2->x3,
									 p1->x4 + p2->x4);
		}
	}

	return (void*) (0);
}

void* sub_v(void *a1, void *a2, size_t s) {
	switch (s) {
		case (2): {
			v2 *p1 = (v2*) a1, *p2 = (v2*) a2;
			return (void*) create_v2(p1->x - p2->x,
									 p1->y - p2->y);
	    }
		case (3): {
			v3 *p1 = (v3*) a1, *p2 = (v3*) a2;
			return (void*) create_v3(p1->x - p2->x,
									 p1->y - p2->y,
									 p1->z - p2->z);
		}
		case (4): {
			v4 *p1 = (v4*) a1, *p2 = (v4*) a2;
			return (void*) create_v4(p1->x1 - p2->x1,
									 p1->x2 - p2->x2,
									 p1->x3 - p2->x3,
									 p1->x4 - p2->x4);
		}
	}

	return (void*) (0);
}

double dot(void *a1, void *a2, size_t s) {
	switch (s) {
		case (2): {
			v2 *p1 = (v2*) a1, *p2 = (v2*) a2;
			return (p1->x) * (p2->x) +
				   (p1->y) * (p2->y);
		}
		case (3): {
			v3 *p1 = (v3*) a1, *p2 = (v3*) a2;
			return (p1->x * p2->x +
				    p1->y * p2->y +
				    p1->z * p2->z);
		}
		case (4): {
			v4 *p1 = (v4*) a1, *p2 = (v4*) a2;
			return  (p1->x1 * p2->x1 +
				     p1->x2 * p2->x2 +
				     p1->x3 * p2->x3 +
				     p1->x4 * p2->x4);
		}
	}

	return 0;
}

void* scale_v(void *a1, double scalar, size_t s) {
	switch (s) {
		case (2): {
			v2 *p1 = (v2*) a1;
			return (void*) create_v2(p1->x * scalar,
									 p1->y * scalar);
		}
		case (3): {
			v3 *p1 = (v3*) a1;
			return (void*) create_v3(p1->x * scalar,
									 p1->y * scalar,
									 p1->z * scalar);
		}
		case (4): {
			v4 *p1 = (v4*) a1;
			return (void*) create_v4(p1->x1 * scalar,
									 p1->x2 * scalar,
									 p1->x3 * scalar,
									 p1->x4 * scalar);
		}
	}

	return (void*) 0;
}

bool equal_v(void *a1, void *a2, size_t s1, size_t s2) {
	if (s1 != s2)
		return 0;

	switch (s1) {
		case (2): {
			v2 *p1 = (v2*) a1, *p2 = (v2*) a2;
			return (p1->x == p2->x &&
					p1->y == p2->y);
		}
		case (3): {
			v3 *p1 = (v3*) a1, *p2 = (v3*) a2;
			return (p1->x == p2->x &&
					p1->y == p2->y &&
					p1->z == p2->z);
		}
		case (4): {
			v4 *p1 = (v4*) a1, *p2 = (v4*) a2;
			return (p1->x1 == p2->x1 &&
					p1->x2 == p2->x2 &&
					p1->x3 == p2->x3 &&
					p1->x4 == p2->x4);
		}
	}

	return 0;
}

bool not_equal_v(void *a1, void *a2, size_t a, size_t b) {
	return !equal_v(a1, a2, a, b);
}

double magnitude(void *a1, size_t a) {
	switch (a) {
		case (2): {
			v2 *p1 = (v2*) a1;
			double x = p1->x,
				   y = p1->y;
			return sqrt(x*x + y*y);
		}
		case (3): {
			v3 *p1 = (v3*) a1;
			double x = p1->x,
				   y = p1->y,
				   z = p1->z;
			return sqrt(x*x + y*y + z*z);
		}
		case (4): {
			v4 *p1 = (v4*) a1;
			double x1 = p1->x1,
				   x2 = p1->x2,
				   x3 = p1->x3,
				   x4 = p1->x4;
			return sqrt(x1*x1 + x2*x2 + x3*x3 + x4*x4);
		}
	}

	return 0;
}

double cosine(void *a1, void *a2, size_t a) {
	double dp = dot(a1, a2, a);
	double m1 = magnitude(a1, a), m2 = magnitude(a2, a);
	return dp / (m1 * m2);
}

void print_v(void *v, size_t a) {
	switch (a) {
		case (2):
			printf("(%.3f, %.3f)", ((v2*)v)->x, ((v2*)v)->y);
			break;
		case(3):
			printf("(%.3f, %.3f, %.3f)", ((v3*)v)->x, ((v3*)v)->y, ((v3*)v)->z);
			break;
		case(4):
			printf("(%.3f, %.3f, %.3f, %.3f)", ((v4*)v)->x1,
											   ((v4*)v)->x2,
											   ((v4*)v)->x3,
											   ((v4*)v)->x4);
			break;

	}
	printf("\n");
}

void swap_v2(v2 *a, v2 *b) {
	assert(a && b);
	v2 tmp = *a;
	*a = *b;
	*b = tmp;
}

double dist_v2(v2 *a, v2 *b) {
	return sqrt((a->x - b->x) * (a->x - b->x) +
				(a->y - b->y) * (a->y - b->y));
}

v3 cross(v3 a, v3 b) {
	v3 c = { a.y * b.z - a.z * b.y,
			 a.z * b.x - a.x * b.z,
			 a.x * b.y - a.y * b.x };

	return c;
}

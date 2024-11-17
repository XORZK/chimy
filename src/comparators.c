#include "comparators.h"
#include "vec.h"
#include "segment.h"

int cmp_double(const void *a, const void *b) {
	double d1 = *(double*) a, d2 = *(double*) b;

	return (d1 > d2) - (d1 < d2);
}

int cmp_int(const void *a, const void *b) {
	int d1 = *(int*) a, d2 = *(int*) b;

	return (d1 > d2) - (d1 < d2);
}

int cmp_float(const void *a, const void *b) {
	float d1 = *(float*) a, d2 = *(float*) b;

	return (d1 > d2) - (d1 < d2);
}

int sort_v2_by_x(const void *a, const void *b) {
	v2 p1 = *(v2*) a, p2 = *(v2*) b;

	return (p1.x > p2.x) - (p1.x < p2.x);
}

int sort_v2_by_y(const void *a, const void *b) {
	v2 p1 = *(v2*) a, p2 = *(v2*) b;

	return (p1.y > p2.y) - (p1.y < p2.y);
}

int sort_v3_by_x(const void *a, const void *b) {
	v3 p1 = *(v3*) a, p2 = *(v3*) b;

	return (p1.x > p2.x) - (p1.x < p2.x);
}

int sort_v3_by_y(const void *a, const void *b) {
	v3 p1 = *(v3*) a, p2 = *(v3*) b;

	return (p1.y > p2.y) - (p1.y < p2.y);
}

int sort_v3_by_z(const void *a, const void *b) {
	v3 p1 = *(v3*) a, p2 = *(v3*) b;

	return (p1.z > p2.z) - (p1.z < p2.z);
}

int sort_segment_v2_by_x(const void *a, const void *b) {
	segment_v2 s1 = *(segment_v2*) a,
			   s2 = *(segment_v2*) b;

	return (s1.p1.x > s2.p1.x) - (s1.p1.x < s2.p1.x);
}

int sort_segment_v2_by_y(const void *a, const void *b) {
	segment_v2 s1 = *(segment_v2*) a,
			   s2 = *(segment_v2*) b;

	return (s1.p1.y > s2.p1.y) - (s1.p1.y < s2.p1.y);
}


int sort_segment_v3_by_x(const void *a, const void *b) {
	segment_v3 s1 = *(segment_v3*) a,
			   s2 = *(segment_v3*) b;

	return (s1.p1.x > s2.p1.x) - (s1.p1.x < s2.p1.x);
}

int sort_segment_v3_by_y(const void *a, const void *b) {
	segment_v3 s1 = *(segment_v3*) a,
			   s2 = *(segment_v3*) b;

	return (s1.p1.y > s2.p1.y) - (s1.p1.y < s2.p1.y);
}

int sort_segment_v3_by_z(const void *a, const void *b) {
	segment_v3 s1 = *(segment_v3*) a,
			   s2 = *(segment_v3*) b;

	return (s1.p1.z > s2.p1.z) - (s1.p1.z < s2.p1.z);
}

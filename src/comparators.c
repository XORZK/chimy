#include "comparators.h"
#include "vec.h"
#include "segment.h"
#include "tuple.h"

#include <math.h>

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

int cmp_ccw_v2_centroid(const void *p1, const void *p2, v2 center) {
	double cx = center.x, cy = center.y;

	v2 a = *(v2*) p1,
	   b = *(v2*) p2;

	if (a.x >= cx && b.x < cx) return 1;
	if (a.x < cx && b.x >= cx) return -1;
	if (a.x == cx && b.x == cx) {
		return (fabs(a.y - cy) > fabs(b.y - cy) ? 1 : -1);
	}

	int det = (a.x - cx) * (b.y - cy) - (b.x - cx) * (a.y - cy);

	if (det < 0)
		return 1;

	if (det > 0)
		return -1;

	float d1 = (a.x - cx) * (a.x - cx) + (a.y - cy) * (a.y - cy),
		  d2 = (b.x - cx) * (b.x - cx) + (b.y - cy) * (b.y - cy);

	return (d1 > d2 ? 1 : d2 == d1 ? 0 : -1);
}

int cmp_ccw_v2(const void *p1, const void *p2) {
	v2 c = { 0, 0 };
	return cmp_ccw_v2_centroid(p1, p2, c);
}

int search_first_x(const void *a, const void *b) {
	segment_v2 segment = *(segment_v2*) a;
	double px = *(double*) b;

	return cmp_double(&segment.p1.x, &px);
}

int search_second_x(const void *a, const void *b) {
	segment_v2 segment = *(segment_v2*) a;
	double px = *(double*) b;

	return cmp_double(&segment.p2.x, &px);
}

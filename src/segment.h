#ifndef SEGMENT_H
#define SEGMENT_H

#pragma once
#include "vec.h"
#include "list.h"

// segment from p1 to p2
// p1.x <= p2.x
typedef struct {
	v2 p1, p2;
} segment_v2;

// p1.x <= p2.x
typedef struct {
	v3 p1, p2;
} segment_v3;

segment_v2* create_segment_v2(double x1, double y1, double x2, double y2);

void delete_segment_v2(segment_v2 *segment);

segment_v3* create_segment_v3(double x1, double y1, double z1,
							  double x2, double y2, double z2);

void delete_segment_v3(segment_v3 *segment);

double slope_v2(segment_v2 *s);

double interp_v2(segment_v2 *s, double x);

// Assumptions:
// - No vertical segments
// - No two segments intersect at their endpoints
// - No three (or more) segments have common POI
// - All endpoints & POI have different x-coordinates
// - No segment overlap
// Let X be the set of all x-coords of segments in p
// Traverse X in order (L -> R)
// Do stuff

// list* bentley_ottmann(polygon *p); --> list* bentley_ottmann(list *segments)
list* bentley_ottmann(list *segments);

list* brute_force_line_intersection(list *segments);

#endif

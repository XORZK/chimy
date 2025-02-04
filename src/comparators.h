#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "vec.h"

int cmp_double(const void *a, const void *b);

int cmp_int(const void *a, const void *b);

int cmp_float(const void *a, const void *b);

int sort_v2_by_x(const void *a, const void *b);

int sort_v2_by_y(const void *a, const void *b);

int sort_v3_by_x(const void *a, const void *b);

int sort_v3_by_y(const void *a, const void *b);

int sort_v3_by_z(const void *a, const void *b);

int sort_segment_v2_by_x(const void *a, const void *b);

int sort_segment_v2_by_y(const void *a, const void *b);

int sort_segment_v3_by_x(const void *a, const void *b);

int sort_segment_v3_by_y(const void *a, const void *b);

int sort_segment_v3_by_z(const void *a, const void *b);

int cmp_ccw_v2(const void *a, const void *b);

// search
int search_first_x(const void *a, const void *b);

int search_second_x(const void *a, const void *b);

bool is_cw_v3(v3 a, v3 b, v3 c);

bool is_ccw_v3(v3 a, v3 b, v3 c);

#endif

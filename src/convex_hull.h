#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "list.h"

// https://en.wikipedia.org/wiki/Convex_hull_algorithms
// smallest polygon that encloses all points in the set
list* gift_wrapping(list* points);

list* graham_scan(list* points);

#endif

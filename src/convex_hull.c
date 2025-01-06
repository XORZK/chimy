#include "convex_hull.h"
#include "vec.h"

double cross(v2 p, v2 q, v2 r) {
	double v = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	return v;
}

// https://en.wikipedia.org/wiki/Convex_hull_algorithms
// smallest polygon that encloses all points in the set
list* gift_wrapping(list* points) {
	list *hull = init_list(sizeof(v2), 5);

	v2 left = *(v2*) get_element(points, 0);

	for (int j = 1; j < points->length; j++) {
		v2 p = *(v2*) get_element(points, j);

		if (p.x < left.x)
			left = p;
	}

	v2 curr = left;

	while (1) {
		push(hull, &curr);

		v2 q = *(v2*) get_element(points, 0);

		for (int j = 0; j < points->length; j++) {
			v2 r = *(v2*) get_element(points, j);
			if ((q.x == curr.x && q.y == curr.y) || cross(curr, q, r) > 0)
				q = r;
		}

		curr = q;

		if (curr.x == left.x && curr.y == left.y)
			break;
	}

	return hull;
}


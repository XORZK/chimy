#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"
#include "segment.h"
#include "queue.h"
#include "comparators.h"
#include "tuple.h"

int sort_event_tree(const void *a, const void *b) {
	double c1 = *(double*) (((tuple*) a)->b),
		   c2 = *(double*) (((tuple*) b)->b);

	return (c1 > c2) - (c1 < c2);
}

segment_v2* create_segment_v2(double x1, double y1, double x2, double y2) {
	if (x1 > x2)
		return create_segment_v2(x2, y2, x1, y1);

	segment_v2* segment = (segment_v2*) malloc(sizeof(segment_v2));

	v2 p1 = { x1, y1 },
	   p2 = { x2, y2 };

	segment->p1 = p1;
	segment->p2 = p2;

	return segment;
}

void delete_segment_v2(segment_v2 *segment) {
	if (segment)
		free(segment);
}

segment_v3* create_segment_v3(double x1, double y1, double z1,
							  double x2, double y2, double z2) {
	if (x1 > x2)
		return create_segment_v3(x2, y2, z2, x1, y1, z1);

	segment_v3* segment = (segment_v3*) malloc(sizeof(segment_v3));

	v3 p1 = { x1, y1, z1 },
	   p2 = { x2, y2, z2 };

	segment->p1 = p1;
	segment->p2 = p2;

	return segment;
}

void delete_segment_v3(segment_v3 *segment) {
	if (segment)
		free(segment);
}

double slope_v2(segment_v2 *s) {
	if (!s)
		return 0;

	return (s->p2.y - s->p1.y) / (s->p2.x - s->p1.x);
}

// assumes s is not vertical
double interp_v2(segment_v2 *s, double x) {
	double m = slope_v2(s),
		   b = s->p1.y - m * s->p1.x;

	return m * x + b;
}

/**
// TODO
// assume segments contains segment_v2 type
// https://en.wikipedia.org/wiki/Bentley–Ottmann_algorithm
list* bentley_ottmann(list *segments) {
	if (!segments)
		return (list*) NULL;

	list* sorted_segments = sort(segments, sort_v2_by_x);

	// event queue
	// queue* q = init_queue(segments->type_size, segments->length, is_v2 ? sort_v2_by_x : sort_v3_by_x);
	queue* q = init_queue(sizeof(v2), 2 * segments->length, sort_v2_by_x);
	avl_tree* tree = init_avl_tree(sizeof(segment_v2) + sizeof(tuple), sort_event_tree);

	// initialization
	for (int j = 0; j < sorted_segments->length; j++) {
		segment_v2 s = *(segment_v2*) get_element(sorted_segments, j);
		queue_insert(q, &s.p1);
		queue_insert(q, &s.p2);
	}

	// main loop
	while (!queue_is_empty(q)) {
		void *top = pop_min(q);
		v2 event = *(v2*) top;

		// find associated segment
		int first_idx = binary_search(sorted_segments, &event.x, search_first_x),
			second_idx = binary_search(sorted_segments, &event.x, search_second_x);

		// TODO: make avl tree hold pairs where second
		//	     value in the pair is actually the crossing point at y
		//	     and then sort by that crossing point

		// left endpoint
		if (second_idx == -1) {
			segment_v2 s = *(segment_v2*) get_element(sorted_segments, first_idx);
			double y = interp_v2(&s, event.x); // crossing point
			tuple *t = create_tuple(&s, &y, sizeof(segment_v2), sizeof(double));
			avl_node *inserted = avl_tree_insert(tree, t);
			// find predecessor (T) and successor (R)
			// T.y < y, R.y > y
			avl_node *T = NULL, *R = NULL;

			if (inserted->left != NULL) {
				for (T = inserted->left; T != NULL; T = T->right);
			} else {
				// largest ancestor of node smaller than node
				// node is a right child of ancestor
				avl_node *curr = inserted;

				while (curr != NULL) {
					if (T == NULL || (sort_event_tree(curr->data, inserted->data) < 0 && sort_event_tree(curr->data, T->data) > 0))
						T = curr;
					curr = curr->parent;
				}
			}

			if (inserted->right != NULL) {
				for (R = inserted->right; R != NULL; R = R->left);
			} else {
				// smallest ancestor of node greater than node
				avl_node *curr = inserted;

				while (curr != NULL) {
					// curr->data > inserted->data
					// curr->data < R->data
					if (R == NULL || (sort_event_tree(curr->data, inserted->data) > 0 && sort_event_tree(curr->data, R->data) < 0))
						R = curr;
					curr = curr->parent;
				}
			}

			destroy_tuple(t);
		} else {
			segment_v2 s = *(segment_v2*) get_element(sorted_segments, second_idx);
		}

		free(top);
	}

	destroy_list(sorted_segments);
	destroy_queue(q);
	destroy_avl_tree(tree);

	return (list*) NULL;
}*/

// assumes no two lines overlap
// time complexity: O(n^2)
list* brute_force_line_intersection(list *segments) {
	int N = segments->length;
	list* intersections = init_list(sizeof(v2), (N * (N-1)) / 2);

	for (int j = 0; j < N; j++) {
		for (int k = j+1; k < N; k++) {
			// check POI between s1, s2
			segment_v2 *s1 = (segment_v2*) get_element(segments, j),
					   *s2 = (segment_v2*) get_element(segments, k);

			// if s2.v2.x < s1.v1.x or s1.v2.x < s2.v1.x, continue
			if (s2->p2.x < s1->p1.x || s1->p2.x < s2->p1.x) {
				continue;
			}

			v2 p;

			bool is_v1 = (s1->p1.x == s1->p2.x),
				 is_v2 = (s2->p1.x == s2->p2.x);

			// TODO: vertical lines
			if (is_v1 && is_v2) continue;
			else if (is_v1 || is_v2) {
				// get point on s2 at s1.x
				double m = slope_v2(is_v1 ? s2 : s1),
					   b = (is_v1 ? s2->p1.y - m * s2->p1.x
							      : s1->p1.y - m * s1->p1.x);

				double x = (is_v1 ? s1->p1.x : s2->p1.x),
					   y = m * x + b;
				p.x = x;
				p.y = y;
			} else {
				// slope, intercept
				double m1 = slope_v2(s1),
					   m2 = slope_v2(s2);

				double b1 = s1->p1.y - m1 * s1->p1.x,
					   b2 = s2->p1.y - m2 * s2->p1.x;

				if (m1 == m2) { continue; } // parallel

				// m1x + b1 = m2x + b2
				// x = (b2-b1) / (m1-m2)
				double px = (b2 - b1) / (m1 - m2),
					   py = m1 * px + b1;

				p.x = px;
				p.y = py;
			}

			if (s1->p1.x <= p.x && p.x <= s1->p2.x &&
			    s2->p1.x <= p.x && p.x <= s2->p2.x) {
				push(intersections, &p);
			}
		}
	}

	return intersections;
}

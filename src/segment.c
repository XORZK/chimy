#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "segment.h"
#include "queue.h"
#include "comparators.h"

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


// TODO
// assume segments contains segment_v2 type
list* bentley_ottmann(list *segments) {
	if (!segments)
		return (list*) NULL;

	// event queue
	// queue* q = init_queue(segments->type_size, segments->length, is_v2 ? sort_v2_by_x : sort_v3_by_x);
	queue* q = init_queue(sizeof(v2), 2 * segments->length, sort_v2_by_x);

	for (int j = 0; j < segments->length; j++) {
		segment_v2 s = *(segment_v2*) get_element(segments, j);
		queue_insert(q, &s.p1);
		queue_insert(q, &s.p2);
	}

	while (!queue_is_empty(q)) {
		// main loop
		void *q_top = pop_min(q);
		v2 p = *(v2*) q_top;
		printf("(%f, %f)\n", p.x, p.y);
		free(q_top);
	}

	destroy_queue(q);

	return (list*) NULL;
}

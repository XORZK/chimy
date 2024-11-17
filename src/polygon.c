#include <assert.h>
#include <stdlib.h>
#include "segment.h"
#include "polygon.h"

polygon* init_polygon(bool is_v2) {
	polygon* p = (polygon*) malloc(sizeof(polygon));

	assert(p);

	p->is_v2 = is_v2;
	p->vertices = init_list(p->is_v2 ? sizeof(v2) : sizeof(v3), 10);
	p->edges = init_list(sizeof(pair), 10);
	p->vertex_count = 0;
	p->edge_count = 0;

	return p;
}

void push_vertex(polygon *p, void *v) {
	if (!p)
		return;

	push(p->vertices, v);
	p->vertex_count++;
}

void add_edge(polygon *p, int j, int k) {
	if (j < 0 || j >= p->vertex_count || k < 0 || k >= p->vertex_count || j == k)
		return;

	if (j > k) {
		add_edge(p, k, j);
	} else {
		pair E = { j, k };
		push(p->edges, &E);
		p->edge_count++;
	}
}

void* get_vertex(polygon *p, int idx) {
	if (!p)
		return (void*) NULL;

	return get_element(p->vertices, idx);
}

pair get_edge(polygon *p, int idx) {
	if (idx < 0 || idx >= p->edge_count) {
		pair E = { -1, -1 };
		return E;
	}

	void* E = get_element(p->edges, idx);

	return *((pair*) E);
}

// https://en.wikipedia.org/wiki/Polygon_triangulation
list* ear_clipping(polygon *p) {
	return NULL;
}

void destroy_polygon(polygon *p) {
	if (!p)
		return;

	destroy_list(p->vertices);
	destroy_list(p->edges);
	free(p);
}

list* get_segments(polygon *p) {
	if (!p) {
		return (list*) (NULL);
	}

	list* l = init_list((p->is_v2 ? sizeof(segment_v2) : sizeof(segment_v3)), 10);

	for (int j = 0; j < p->edge_count; ++j) {
		pair E = get_edge(p, j);

		void *vt1 = get_vertex(p, E.first),
			 *vt2 = get_vertex(p, E.second);

		if (p->is_v2) {
			v2 *a1 = (v2*) vt1, *a2 = (v2*) vt2;
			segment_v2 segment = { (a1->x < a2->x ? (*a1) : (*a2)), (a1->x < a2->x ? (*a2) : (*a1)) };
			push(l, &segment);
		} else {
			v3 *a1 = (v3*) vt1, *a2 = (v3*) vt2;
			segment_v3 segment = { (a1->x < a2->x ? (*a1) : (*a2)), (a1->x < a2->x ? (*a2) : (*a1)) };
			push(l, &segment);
		}
	}

	return l;
}

#include <assert.h>
#include <stdlib.h>
#include "comparators.h"
#include "segment.h"
#include "polygon.h"
#include "ll.h"
#include "triangle.h"

polygon* init_polygon() {
	polygon* p = (polygon*) malloc(sizeof(polygon));

	assert(p);

	p->centroid.x = p->centroid.y = 0;
	p->vertices = init_list(sizeof(v2), 10);
	p->edges = init_list(sizeof(pair), 10);
	p->vertex_count = 0;
	p->edge_count = 0;

	return p;
}

void push_vertex(polygon *p, void *v) {
	if (!p)
		return;

	v2 vt = *(v2*) v;

	p->centroid.x = ((p->centroid.x * p->vertex_count) + vt.x) / (p->vertex_count+1);
	p->centroid.y = ((p->centroid.y * p->vertex_count) + vt.y) / (p->vertex_count+1);

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

v2* get_vertex(polygon *p, int idx) {
	if (!p)
		return (v2*) NULL;

	return (v2*) get_element(p->vertices, idx);
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
// Assume p is simple
list* ear_clipping(polygon *p) {
	if (p->vertex_count <= 2)
		return NULL;

	list *tf = init_list(sizeof(v2), p->vertex_count);
	list *triangles = init_list(sizeof(triangle), p->vertex_count - 2);

	for (int j = 0; j < p->vertex_count; j++) {
		v2 *t = (v2*) sub_v(get_vertex(p, j), &p->centroid, 2);
		push(tf, t);
		free(t);
	}

	list* v = sort(tf, cmp_ccw_v2);
	ll* verts = init_ll(sizeof(v2));

	for (int j = 0; j < v->length; j++) {
		v2 *element = get_element(v, j);
		v2 shifted = { element->x + p->centroid.x, element->y + p->centroid.y };
		ll_push(verts, &shifted);
	}

	while (verts->size > 3) {
		ll_node *curr = verts->head;
		for (int k = 0; k < verts->size; k++) {
			bool is_inside = false;
			ll_node* p1 = curr->prev, *p2 = curr, *p3 = curr->next;
			ll_node *inside = p3->next;

			while (inside != p1) {
				if (in_triangle(*(v2*) inside->data, *(v2*) p1->data, *(v2*) p2->data, *(v2*) p3->data)) {
					is_inside = true;
					break;
				}

				inside = inside->next;
			}

			if (!is_inside) {
				double x1 = ((v2*) p1->data)->x,
					   y1 = ((v2*) p1->data)->y,
					   x2 = ((v2*) p2->data)->x,
                       y2 = ((v2*) p2->data)->y,
					   x3 = ((v2*) p3->data)->x,
					   y3 = ((v2*) p3->data)->y;

				triangle *t = create_triangle(x1, y1, x2, y2, x3, y3);
				push(triangles, t);
				delete_triangle(t);

				ll_pop(verts, p2);
				break;
			}

			curr = curr->next;
		}
	}

	if (verts->size == 3) {
		double x1 = ((v2*) verts->head->prev->data)->x,
			   y1 = ((v2*) verts->head->prev->data)->y,
			   x2 = ((v2*) verts->head->data)->x,
			   y2 = ((v2*) verts->head->data)->y,
			   x3 = ((v2*) verts->head->next->data)->x,
			   y3 = ((v2*) verts->head->next->data)->y;
		triangle *t = create_triangle(x1, y1, x2, y2, x3, y3);
		push(triangles, t);
		delete_triangle(t);
	}

	destroy_list(v);
	destroy_list(tf);
	destroy_ll(verts);

	return triangles;
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

	list* l = init_list(sizeof(segment_v2), p->edge_count);

	for (int j = 0; j < p->edge_count; ++j) {
		pair E = get_edge(p, j);

		void *vt1 = get_vertex(p, E.first),
			 *vt2 = get_vertex(p, E.second);

		v2 *a1 = (v2*) vt1, *a2 = (v2*) vt2;
		segment_v2 segment = { (a1->x < a2->x ? (*a1) : (*a2)), (a1->x < a2->x ? (*a2) : (*a1)) };
		push(l, &segment);
	}

	return l;
}

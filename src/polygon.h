#ifndef POLYGON_H
#define POLYGON_H

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "list.h"
#include "pair.h"
#include "vec.h"

// vertices
// edges connecting vertices
// edges: (v_j, v_k) connects vertex j to vertex k
typedef struct {
	bool is_v2; // dimension
	int64_t vertex_count, edge_count;
	list *vertices, *edges;
} polygon;

polygon* init_polygon(bool is_v2);

void push_vertex(polygon *p, void* v);

// connects vertex j to vertex k
// j < k
void add_edge(polygon *p, int j, int k);

void* get_vertex(polygon *p, int idx);

pair get_edge(polygon *p, int idx);

list* ear_clipping(polygon *p);

void destroy_polygon(polygon *p);

list* get_segments(polygon *p);

#endif

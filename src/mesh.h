#ifndef MESH_H
#define MESH_H

#include "list.h"
#include <string.h>

typedef struct mesh {
	list *F, *V;
} mesh;

mesh* init_mesh(const char* fn);

void sort_depths(mesh *m);

void sort_ccw_mesh(mesh *m);

void destroy_mesh(mesh *m);

#endif

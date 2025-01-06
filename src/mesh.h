#ifndef MESH_H
#define MESH_H

#include "list.h"
#include <string.h>

typedef struct mesh {
	list *F, *V;
} mesh;

mesh* init_mesh(const char* fn);

void destroy_mesh(mesh *m);

#endif

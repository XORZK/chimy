#include "mesh.h"
#include "vec.h"
#include <stdio.h>
#include <stdlib.h>

mesh* init_mesh(const char* fn) {
	mesh *m = (mesh*) malloc(sizeof(mesh));

	m->F = init_list(sizeof(v3i), 10);
	m->V = init_list(sizeof(v3), 10);

	FILE *file = fopen(fn, "r");

	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	char *token;
	char line[256];

	while (fgets(line, sizeof(line), file) != NULL) {
		bool is_face = (line[0] == 'f');

		token = strtok(line, " \n");

		double *v = (double*) malloc(sizeof(double) * 3);
		double *p = v;

		while (token != NULL) {
			if (token[0] != 'f' && token[0] != 'v') {
				*(p++) = atof(token);
			}

			token = strtok(NULL, " \n");
		}

		if (is_face) {
			v3i f = { (int) v[0] - 1, (int) v[1] - 1, (int) v[2] - 1 };
			push(m->F, (void*) &f);
		} else {
			v3 vt = { v[0], v[1], v[2] };
			push(m->V, (void*) &vt);
		}

		free(v);
	}

	fclose(file);

	return m;
}

void destroy_mesh(mesh *m) {
	if (!m)
		return;

	destroy_list(m->F);
	destroy_list(m->V);
}

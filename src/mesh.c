#include "mesh.h"
#include "vec.h"
#include "comparators.h"
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
			// sort ccw
			v3 vt = { v[0], v[1], v[2] };
			push(m->V, (void*) &vt);
		}

		free(v);
	}

	fclose(file);

	return m;
}

void sort_ccw_mesh(mesh *m) {
	if (!m)
		return;

	int l = m->F->length;

	for (int j = 0; j < l; j++) {
		v3i f = *(v3i*) get_element(m->F, j);
		v3i nf = { f.x1, f.x2, f.x3 };

		v3 origin = { 0.0, 0.0, 0.0 };
		v3 p1 = *(v3*) get_element(m->V, f.x1),
		   p2 = *(v3*) get_element(m->V, f.x2),
		   p3 = *(v3*) get_element(m->V, f.x3);

		// swap f.x1, f.x2
		if (is_ccw_v3(*(v3*) get_element(m->V, nf.x1),
					  *(v3*) get_element(m->V, nf.x2),
							 origin)) {
			int t = nf.x2; nf.x2 = nf.x1; nf.x1 = t;
		}

		// swap f.x1, f.x3
		if (is_ccw_v3(*(v3*) get_element(m->V, nf.x1),
					  *(v3*) get_element(m->V, nf.x3),
							 origin)) {
			int t = nf.x3; nf.x3 = nf.x1; nf.x1 = t;
		}

		// swap f.x2, f.x3
		if (is_ccw_v3(*(v3*) get_element(m->V, nf.x2),
					  *(v3*) get_element(m->V, nf.x3),
							 origin)) {
			int t = nf.x3; nf.x3 = nf.x2; nf.x2 = t;
		}

		if (nf.x1 != f.x1 || nf.x2 != f.x2 || nf.x3 != f.x3) {
			set_l(m->F, j, &nf);
		}
	}
}

// sort the order of the faces
// uses bubble sort (for now)
void sort_depths(mesh *m) {
	if (!m)
		return;

	int l = m->F->length;

	list *c_depths = init_list(sizeof(double), l);

	for (int j = 0; j < l; j++) {
		v3i f = *(v3i*) get_element(m->F, j);

		v3 p1 = *(v3*) get_element(m->V, f.x1),
		   p2 = *(v3*) get_element(m->V, f.x2),
		   p3 = *(v3*) get_element(m->V, f.x3);

		double zsum = (p1.z + p2.z + p3.z);

		push(c_depths, (void*) &zsum);
	}

	for (int j = 0; j < l-1; j++) {
		for (int k = 0; k < l-j-1; k++) {
			double f1 = *(double*) get_element(c_depths, k),
				   f2 = *(double*) get_element(c_depths, k+1);

			if (f1 < f2) {
				swap_list(m->F, k, k+1);
			}
		}
	}

	destroy_list(c_depths);
}

void destroy_mesh(mesh *m) {
	if (!m)
		return;

	destroy_list(m->F);
	destroy_list(m->V);
}

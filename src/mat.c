#include "mat.h"
#include <stdlib.h>
#include <assert.h>

m2* create_m2() {
	m2* m = (m2*) malloc(sizeof(m2));

	for (int j = 0; j < 4; j++) { m->v[j] = 0; }

	return m;
}

m3 *create_m3() {
	m3* m = (m3*) malloc(sizeof(m3));

	for (int j = 0; j < 9; j++) { m->v[j] = 0; }

	return m;
}

m4 *create_m4() {
	m4* m = (m4*) malloc(sizeof(m4));

	for (int j = 0; j < 16; j++) { m->v[j] = 0; }

	return m;
}

double* data(void *a1, size_t size) {
	assert(size >= 2 && size <= 4);
	double *p = NULL;

	if (size == 2) {
		p = ((m2*)a1)->v;
	} else if (size == 3) {
		p = ((m3*)a1)->v;
	} else if (size == 4) {
		p = ((m4*)a1)->v;
	} else {
		p = (double*) 0;
	}

	return p;
}

void set(void *a1, int r, int c, double v, size_t size) {
	double *p1 = data(a1, size);
	p1[r*size + c] = v;
}

void load(void *a1, double *p, size_t size) {
	double *p1 = data(a1, size);

	for (int j = 0; j < size*size; j++) {
		*(p1 + j) = *(p+j);
	}
}

void* scale_m(void *a1, double s, size_t size) {
	double *p1 = data(a1, size);
	double *p2 = (double*) malloc(sizeof(double) * size * size);

	for (int j = 0; j < size*size; j++) {
		*(p2+j) = (*(p1 + j)) * s;
	}

	void *m = (size == 2 ? (void*) create_m2() :
			   size == 3 ? (void*) create_m3() :
						   (void*) create_m4());

	load(m, p2, size);

	free(p2);

	return m;
}

void* add_m(void *a1, void *a2, size_t size) {
	double *p1 = data(a1, size), *p2 = data(a2, size);
	double *p3 = (double*) malloc(sizeof(double) * size * size);

	for (int j = 0; j < size*size; j++) {
		*(p3+j) = *(p1+j) + *(p2+j);
	}

	void *m = (size == 2 ? (void*) create_m2() :
			   size == 3 ? (void*) create_m3() :
						   (void*) create_m4());

	load(m, p3, size);

	free(p3);

	return m;
}

void* sub_m(void *a1, void *a2, size_t size) {
	void *n_a2 = scale_m(a2, -1, size);
	void *diff = add_m(a1, n_a2, size);
	free(n_a2);

	return diff;
}

// matmul
// | a1 a2 |
// | a3 a4 |
//	   x
// | b1 b2 |
// | b3 b4 |
//     =
// |(a1*b1+a2*b3) (a1*b2+a2*b4) |
// |(a3*b1+a4*b3) (a3*b2+a4*b4) |
void* matmul(void *a1, void *a2, size_t size) {
	double *p1 = data(a1, size), *p2 = data(a2, size);
	double *p3 = (double*) malloc(sizeof(double) * size * size);

	// entry at: (r,c) = (j,k)
	// jth row of a1 inner prod w/ kth col of a2
	for (int j = 0; j < size; j++) {
		for (int k = 0; k < size; k++) {
			double entry = 0.0;
			for (int l = 0; l < size; l++) {
				entry += p1[j*size+l] * p2[l*size+k];
			}
			p3[j*size+k] = entry;
		}
	}

	void *m = (size == 2 ? (void*) create_m2() :
			   size == 3 ? (void*) create_m3() :
						   (void*) create_m4());

	load(m, p3, size);

	free(p3);

	return m;
}

bool equal_m(void *a1, void *a2, size_t s1, size_t s2) {
	if (s1 != s2) return 0;
	double *p1 = data(a1, s1), *p2 = data(a2, s1);

	for (int j = 0; j < s1*s1; j++) {
		if (*(p1+j) != *(p2+j)) {
			return 0;
		}
	}

	return 1;
}

bool not_equal_m(void *a1, void *a2, size_t s1, size_t s2) {
	return !equal_m(a1, a2, s1, s2);
}

void print_m(void *a1, size_t a) {

	double *p = data(a1, a);

	for (int j = 0; j < a; j++) {
		for (int k = 0; k < a; k++) {
			printf("%3.3f ", p[j*a + k]);
		}
		printf("\n");
	}
}

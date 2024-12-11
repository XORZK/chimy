#ifndef VEC_H
#define VEC_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct {
	double x, y;
} v2;

typedef struct {
	double x, y, z;
} v3;

typedef struct {
	double x1, x2, x3, x4;
} v4;

v2* create_v2(double x, double y);

v3* create_v3(double x, double y, double z);

v4* create_v4(double x1, double x2, double x3, double x4);

void* add_v(void *a1, void *a2, size_t size);

void* sub_v(void *a1, void *a2, size_t size);

double dot(void *a1, void *a2, size_t size);

void* scale_v(void *a1, double scalar, size_t size);

bool equal_v(void *a1, void *a2, size_t s1, size_t s2);

bool not_equal_v(void *a1, void *a2, size_t a, size_t b);

double magnitude(void *a1, size_t a);

double cosine(void *a1, void *a2, size_t a);

void print_v(void *v, size_t a);

void swap_v2(v2 *a, v2 *b);

double dist_v2(v2 *a, v2 *b);

#endif

#ifndef MAT_H
#define MAT_H

#pragma once
#include <stdio.h>
#include <stdbool.h>

// | x1 x2 |
// | y1 y2 |
typedef struct {
	double v[4];
} m2;

// | x1 x2 x3 |
// | y1 y2 y3 |
// | z1 z2 z3 |
typedef struct {
	double v[9];
} m3;

// | a1 a2 a3 a4 |
// | b1 b2 b3 b4 |
// | c1 c2 c3 c4 |
// | d1 d2 d3 d4 |
typedef struct {
	double v[16];
} m4;

m2* create_m2();

m3* create_m3();

m4* create_m4();

void set(void *a1, int r, int c, double v, size_t size);

void load(void *a1, double *p, size_t size);

void* add_m(void *a1, void *a2, size_t size);

void* sub_m(void *a1, void *a2, size_t size);

void* matmul(void *a1, void *a2, size_t size);

void* scale_m(void *a1, double s, size_t size);

bool equal_m(void *a1, void *a2, size_t s1, size_t s2);

bool not_equal_m(void *a1, void *a2, size_t s1, size_t s2);

double determinant(void *a1, size_t a);

void print_m(void *a1, size_t a);

#endif

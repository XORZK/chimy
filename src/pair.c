#include <stdlib.h>
#include <stdio.h>
#include "pair.h"

pair* create_pair(int a, int b) {
	pair* p = (pair*) malloc(sizeof(pair));

	p->first = a;
	p->second = b;

	return p;
}

pair* add_pair(pair *p1, pair *p2) {
	if (!p1 || !p2) {
		return (p2 ? p2 : p1 ? p1 : NULL);
	}

	return create_pair(p1->first + p2->first, p1->second + p2->second);
}

pair* sub_pair(pair *p1, pair *p2) {
	if (!p1 || !p2) {
		return (p2 ? p2 : p1 ? p1 : NULL);
	}

	return create_pair(p1->first - p2->first, p1->second - p2->second);
}

pair* scale_pair(pair *p1, double scalar) {
	if (!p1)
		return (pair*) NULL;

	return create_pair(p1->first * scalar, p1->second * scalar);
}

void print_pair(pair *p) {
	if (!p)
		return;

	printf("(%d, %d)\n", p->first, p->second);
}

void destroy_pair(pair *p) {
	if (p)
		free(p);
}

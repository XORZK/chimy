#ifndef PAIR_H
#define PAIR_H

// simple pair structure
typedef struct {
	int first, second;
} pair;

pair* create_pair(int a, int b);

pair* add_pair(pair *p1, pair *p2);

pair* sub_pair(pair *p1, pair *p2);

pair* scale_pair(pair *p1, double scalar);

void print_pair(pair *p1);

void destroy_pair(pair *p);

#endif

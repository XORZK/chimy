#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>

// doubly linked list
typedef struct ll_node {
	void *data;
	struct ll_node *prev, *next;
} ll_node;

typedef struct ll {
	ll_node *head, *tail;
	int size;
	int ds;
} ll;

void ll_node_set_next(ll_node *prev, ll_node *next);

void ll_node_set_prev(ll_node *prev, ll_node *next);

ll_node* create_ll_node(void *d, int ds);

ll* init_ll(int ds);

ll_node *pop_front(ll *list);

void ll_push(ll* list, void *d);

void ll_pop_by_idx(ll *list, int idx);

void ll_pop(ll* list, ll_node *node);

void print_ll(ll* list, void (*prtf)(const void *));

void destroy_ll_node(ll_node *node);

void destroy_ll(ll* list);

#endif

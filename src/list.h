#ifndef LIST_H
#define LIST_H

#pragma once
#include <stdbool.h>

// generic array structure in c
// void* everywhere
typedef struct {
	void* data;
	int type_size;
	int length, capacity;
} list;

list* init_list(int tsize, int c);

void push(list *l, void *v);

void delete(list *l, int idx);

void* get_element(list *l, int idx);

void destroy_list(list *l);

list* copy_list(list *l);

list* sort(list *l, int (*cmp)(const void *, const void *));

int binary_search(list *l, void *data, int (*cmp)(const void *, const void *));

#endif

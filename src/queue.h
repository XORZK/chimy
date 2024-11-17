#ifndef QUEUE_H
#define QUEUE_H

#pragma once
#include <stdbool.h>

void mem_swap(void* dat, int j, int k, int type_size);

// min heap priority queue
// create generic priority_queue
// everything is void* again!
// comparator function needs to be passed in at initialization.
//
// properties:
// 1. every parent node has a value less than or equal to its children
//    min value of the heap is always at the root
// 2. min heap is a complete binary tree
//    (all levels are filled except last)
typedef struct {
	void *data;
	int type_size;
	int length, capacity;
	int (*cmp)(const void *, const void *); // cmp for the generic data type stored in queue
} queue;

queue* init_queue(int tsize, int c, int (*comparator)(const void *, const void *));

void queue_insert(queue *q, void *v);

void* pop_min(queue *q);

void heapify(queue *q, int j);

bool queue_is_empty(queue *q);

void destroy_queue(queue *q);

#endif

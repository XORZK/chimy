#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAP_PARENT(x) (((x)-1)/2)
#define HEAP_LEFT(x) (2 * (x) + 1)
#define HEAP_RIGHT(x) (2 * (x) + 2)

void mem_swap(void* dat, int j, int k, int type_size) {
	void *tmp = malloc(type_size);
	void *p1 = dat + (j * type_size),
		 *p2 = dat + (k * type_size);

	memcpy(tmp, p1, type_size);
	memcpy(p1, p2, type_size);
	memcpy(p2, tmp, type_size);

	free(tmp);
}

queue* init_queue(int t_size, int c, int (*comparator)(const void *, const void *)) {
	queue* q = (queue*) malloc(sizeof(queue));

	assert(q);

	q->type_size = t_size;
	q->length = 0;
	q->capacity = c;
	q->data = (void*) malloc(t_size * c);
	q->cmp = comparator;

	return q;
}

// 1. insert v at last available position
// 2. compare data to parent data, if v.data < v.parent.data
//    swap(v, v.parent)
void queue_insert(queue *q, void *v) {
	if (!q || !v)
		return;

	if (q->length >= q->capacity) {
		q->capacity += 10;
		q->data = realloc(q->data, q->type_size * q->capacity);
	}

	memcpy(q->data + q->length * q->type_size, v, q->type_size);

	int j = q->length;

	// cmp(x, y) > 0 --> x > y
	// cmp(x, y) < 0 --> x < y
	// cmp(x, y) = 0 --> x = y
	while (j != 0 && q->cmp(q->data + j * q->type_size, q->data + HEAP_PARENT(j) * q->type_size) < 0) {
		mem_swap(q->data, j, HEAP_PARENT(j), q->type_size);
		j = HEAP_PARENT(j);
	}

	q->length++;
}

// 1. replace root w/ last element
// 2. delete last element from heap
// 3. heapify --> find l, r children: swap with min(l,r) if needed
void* pop_min(queue *q) {
	if (!q)
		return (void*) NULL;

	void *top = malloc(q->type_size);

	memcpy(top, q->data, q->type_size);

	// swap 0 w/ q->length-1
	int idx = q->length-1;
	mem_swap(q->data, 0, q->length-1, q->type_size);

	q->length--;

	heapify(q, 0);

	return top;
}

void heapify(queue *q, int j) {
	if (!q)
		return;

	if (q->length <= 1)
		return;
	else if (q->length == 2 && q->cmp(q->data, q->data + q->type_size) > 0) {
		mem_swap(q->data, 0, 1, q->type_size);
	} else {
		while (1) {
			int r = HEAP_RIGHT(j), l = HEAP_LEFT(j);
			void *ptr_j = q->data + j * q->type_size,
				 *ptr_l = q->data + l * q->type_size,
				 *ptr_r = q->data + r * q->type_size;
			if (j >= q->length || (q->cmp(ptr_j, ptr_r) <= 0 && q->cmp(ptr_j, ptr_l) <= 0)) {
				break;
			}

			// c > 0 -> r > l
			// c < 0 -> r < l
			int c = q->cmp(ptr_r, ptr_l);

			if (r < q->length && c <= 0 && q->cmp(ptr_j, ptr_r) > 0) {
				mem_swap(q->data, j, r, q->type_size);
				j = r;
			} else if (l < q->length && c > 0 && q->cmp(ptr_j, ptr_l) > 0) {
				mem_swap(q->data, j, l, q->type_size);
				j = l;
			} else {
				break;
			}
		}
	}
}

bool queue_is_empty(queue *q) {
	if (!q)
		return 1;

	return (q->length == 0);
}

void destroy_queue(queue *q) {
	if (!q)
		return;

	if (q->data)
		free(q->data);

	free(q);
}

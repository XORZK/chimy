#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

list* init_list(int tsize, int c) {
	list* l = (list*) malloc(sizeof(list));

	assert(l);

	l->length = 0;
	l->capacity = c;
	l->type_size = tsize;
	l->data = (void*) malloc(tsize * c);

	return l;
}

void push(list *l, void *v) {
	if (!l || !v)
		return;

	if (l->length >= l->capacity) {
		l->capacity += 10;
		l->data = realloc(l->data, l->type_size * l->capacity);
	}

	memcpy(l->data + l->length * l->type_size, v, l->type_size);

	l->length++;
}

void delete(list *l, int idx) {
	if (idx < 0 || idx >= l->length)
		return;

	// don't use memmove
	// too tired for this.
	// just copy
	for (int j = idx; j < l->length-1; j++) {
		memcpy(l->data + j * l->type_size, l->data + (j+1) * l->type_size, l->type_size);
	}

	l->length--;
}

void* get_element(list *l, int idx) {
	if (idx < 0 || idx >= l->length)
		return NULL;

	return (void*) (l->data + idx * l->type_size);
}

void destroy_list(list *l) {
	if (!l)
		return;

	if (l->data)
		free(l->data);

	free(l);
}

list* copy_list(list *l) {
	list *c = init_list(l->type_size, l->length);

	for (int j = 0; j < l->length; j++) {
		push(c, get_element(l, j));
	}

	return c;
}

list* merge_lists(list *l1, list *l2, int (*cmp)(const void *, const void *)) {
	int m = l1->length, n = l2->length;
	list* merged = init_list(l1->type_size, m + n);
	int j = 0, k = 0;

	while (j < m && k < n) {
		int c = cmp(get_element(l1, j), get_element(l2, k));

		// l1[j] > l2[k]
		if (c < 0) {
			push(merged, get_element(l1, j));
			++j;
		} else {
			push(merged, get_element(l2, k));
			++k;
		}
	}

	while (j < m) { push(merged, get_element(l1, j)); ++j; }
	while (k < n) { push(merged, get_element(l2, k)); ++k; }

	return merged;
}

// merge sort on l
// O(n log n)
list* sort(list *l, int (*cmp)(const void *, const void *)) {
	if (!l)
		return l;

	if (l->length == 1)
		return l;

	int ts = l->type_size;

	list *left = init_list(ts, l->length / 2),
		 *right = init_list(ts, (l->length + 1) / 2);;

	// O(n)
	for (int j = 0; j < l->length; j++) {
		if (j < l->length / 2) {
			push(left, get_element(l, j));
		} else {
			push(right, get_element(l, j));
		}
	}

	list *l1 = sort(right, cmp), *l2 = sort(left, cmp);

	if (l1 != right)
		destroy_list(right);

	if (l2 != left)
		destroy_list(left);

	// O(n)
	list *s = merge_lists(l1, l2, cmp);

	destroy_list(l1);
	destroy_list(l2);

	return s;
}

int binary_search(list *l, void *data, int (*cmp)(const void *, const void *)) {
	int s = 0, e = l->length-1;

	while (s <= e) {
		int mid = (s + e) / 2;
		int c = cmp(get_element(l, mid), data);

		if (c == 0)
			return mid;
		else if (c > 0) // l[mid] > data
			e = mid - 1;
		else
			s = mid + 1;
	}

	return -1;
}

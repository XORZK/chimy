#include "ll.h"
#include <string.h>

void ll_node_set_next(ll_node *prev, ll_node *next) {
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

void ll_node_set_prev(ll_node *prev, ll_node *next) {
	ll_node_set_next(prev, next);
}

ll_node* create_ll_node(void *d, int ds) {
	ll_node* n = (ll_node*) malloc(sizeof(ll_node));
	n->data = (void*) malloc(ds);
	memcpy(n->data, d, ds);
	n->prev = n->next = NULL;
	return n;
}

ll* init_ll(int ds) {
	ll* list = (ll*) malloc(sizeof(ll));
	list->size = 0;
	list->ds = ds;
	list->head = list->tail = NULL;

	return list;
}

void ll_push(ll* list, void *d) {
	if (!list)
		return;

	ll_node *n = create_ll_node(d, list->ds);

	if (list->head == NULL) {
		list->head = list->tail = n;
		list->head->next = list->head->prev = list->head;
	} else {
		ll_node_set_next(list->tail, n);
		list->tail = n;
		ll_node_set_next(n, list->head);
	}

	list->size++;
}

void ll_pop_by_idx(ll *list, int idx) {
	if (!list)
		return;

	while (idx < 0)
		idx += list->size;

	idx %= list->size;

	ll_node *c = list->head;

	for (int j = 0; j < idx; j++) c = c->next;

	ll_pop(list, c);
}

void ll_pop(ll* list, ll_node *node) {
	if (!list)
		return;

	if (list->size == 0)
		return;

	if (node == list->head) {
		if (list->head->next != list->head) {
			ll_node_set_next(node->prev, node->next);
			list->head = node->next;
		} else {
			list->head = list->tail = NULL;
		}
	} else if (node == list->tail) {
		ll_node_set_next(node->prev, list->head);
	} else {
		ll_node_set_next(node->prev, node->next);
	}

	destroy_ll_node(node);

	list->size--;

	if (list->size == 1)
		list->head->next = list->head->prev = list->head;
}

void print_ll(ll* list, void (*prtf)(const void *)) {
	if (!list)
		return;

	ll_node *c = list->head;

	do {
		prtf(c->data);
		c = c->next;
	} while (c != list->head);

	printf("\n");
}

void destroy_ll_node(ll_node *node) {
	if (!node)
		return;

	free(node->data);
	node->next = node->prev = NULL;
	free(node);
}

void destroy_ll(ll* list) {
	if (!list)
		return;

	if (list->head) {
		list->head->prev->next = NULL;

		ll_node *c = list->head, *n = c->next;

		while (c != NULL) {
			destroy_ll_node(c);

			c = n;
			n = c->next;
		}
	}

	list->head = list->tail = NULL;
	free(list);
}

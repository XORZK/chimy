#ifndef LIST_H
#define LIST_H

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

list* sort(list *l, int (*cmp)(const void *, const void *));

#endif

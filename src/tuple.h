#ifndef TUPLE_H
#define TUPLE_H

typedef struct tuple {
	void *a, *b;
} tuple;

tuple* create_tuple(void *a, void *b, int a_size, int b_size);

void destroy_tuple(tuple *t);

#endif

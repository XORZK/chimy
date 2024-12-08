#include "tuple.h"
#include <stdlib.h>
#include <string.h>

tuple* create_tuple(void *f, void *s, int a_size, int b_size) {
	tuple *t = (tuple*) malloc(sizeof(tuple));

	t->a = malloc(a_size);
	t->b = malloc(b_size);

	memcpy(t->a, f, a_size);
	memcpy(t->b, s, b_size);

	return t;
}

void destroy_tuple(tuple *t) {
	if (!t) return;

	if (t->a) free(t->a);
	if (t->b) free(t->b);

	free(t);
}

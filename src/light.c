#include <stdio.h>
#include <stdlib.h>
#include "light.h"

light* init_light() {
	v3 p = { 0.0, 0.0, 1.0 };

	light* l = (light*) malloc(sizeof(light));
	l->pos = p;

	return l;
}

void destroy_light(light *l) {
	if (!l)
		return;

	free(l);
}

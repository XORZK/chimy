#include "color.h"
#include <stdlib.h>

color* create_color(uint8_t R, uint8_t G, uint8_t B, uint8_t A) {
	color* c = (color*) malloc(sizeof(color));

	c->R = R;
	c->G = G;
	c->B = B;
	c->A = A;

	return c;
}

void delete_color(color *c) {
	if (c)
		free(c);
}

#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"

// https://www.cs.ubc.ca/~lsigal/teaching08/LN09_Shading.pdf
//
//
typedef struct light {
	v3 pos;
} light;

light* init_light();

void destroy_light(light *l);

#endif

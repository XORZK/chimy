#ifndef COLOR_H
#define COLOR_H

#pragma once
#include <stdint.h>

typedef struct {
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
} color;

color* create_color(uint8_t R, uint8_t G, uint8_t B, uint8_t A);

void delete_color(color *c);

#endif

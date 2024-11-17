#ifndef WINDOW_H
#define WINDOW_H
#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "color.h"
#include "triangle.h"
#include "polygon.h"
#include "vec.h"

#define RENDERER_DELAY 15

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;
	int delay;
	bool quit;
	color *color;
	const char* title;
} window;

window* init_window(const char* title, int width, int height);

void destroy_window(window *w);

void tick(window *w);

void output_screen(window *w);

void set_color(window *w, int r, int g, int b);

void draw_point_v2(window *w, v2 v);

void draw_line_v2(window *w, v2 a, v2 b);

void draw_wireframe_circle_v2(window *w, v2 center, double radius);

void draw_filled_circle_v2(window *w, v2 center, double radius);

void draw_wireframe_triangle(window *w, triangle *t);

void draw_wireframe_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3);

void draw_filled_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3);

void draw_filled_triangle(window *w, triangle *t);

void draw_wireframe_rectangle_v2(window *w, v2 v, int width, int height);

void draw_filled_rectangle_v2(window *w, v2 v, int width, int height);

void draw_wireframe_square_v2(window *w, v2 v, int length);

void draw_filled_square_v2(window *w, v2 v, int length);

void draw_wireframe_polygon(window *w, polygon *p);

#endif

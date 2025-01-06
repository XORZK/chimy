#ifndef WINDOW_H
#define WINDOW_H
#pragma once
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "camera.h"
#include "color.h"
#include "triangle.h"
#include "mesh.h"
#include "polygon.h"
#include "vec.h"

#define RENDERER_DELAY 15

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;
	int delay;
	bool quit;
	color *color, *bg_color;
	const char* title;
	cam *camera;
} window;

window* init_window(const char* title, int width, int height);

void init_default_camera(window *w);

void init_camera(window *w, double fov, double n, double f);

void destroy_window(window *w);

void tick(window *w);

void draw_bg(window *w);

void set_bg_color(window *w, int r, int g, int b);

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

v2 ndc_to_screen(window *w, v3 p);

void draw_point_v3(window *w, v3 v);

void draw_line_v3(window *w, v3 a, v3 b);

void draw_wireframe_circle_v3(window *w, v3 center, double r);

void draw_filled_circle_v3(window *w, v3 center, double r);

void draw_wireframe_triangle_v3(window *w, v3 vt1, v3 vt2, v3 vt3);

void draw_filled_triangle_v3(window *w, v3 vt1, v3 vt2, v3 vt3);

void draw_wireframe_rectangle_v3(window *wd, v3 v, int w, int h);

void draw_filled_rectangle_v3(window *wd, v3 v, int w, int h);

void draw_wireframe_square_v3(window *w, v3 v, int l);

void draw_filled_square_v3(window *w, v3 v, int l);

void draw_mesh(window *w, mesh *m);

#endif

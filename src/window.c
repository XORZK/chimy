#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pair.h"
#include "window.h"

window* init_window(const char* title, int width, int height) {
	window* w = (window*) malloc(sizeof(window));

	assert(w);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return NULL;
	}

	w->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (!w->window) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	w->renderer = SDL_CreateRenderer(w->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!w->renderer) {
		SDL_DestroyWindow(w->window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return NULL;
	}

	w->width = width;
	w->height = height;
	w->title = title;
	w->quit = false;
	w->delay = RENDERER_DELAY;

	return w;
}

void destroy_window(window *w) {
	if (!w)
		return;

	if (w->renderer)
		SDL_DestroyRenderer(w->renderer);

	if (w->window)
		SDL_DestroyWindow(w->window);

	delete_color(w->color);

	free(w);
	SDL_Quit();
}

void tick(window *w) {
	assert(w);
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			w->quit = true;
		}
	}
}

void output_screen(window *w) {
	assert(w);

	SDL_RenderPresent(w->renderer);

	SDL_Delay(w->delay);
}

void set_color(window *w, int r, int g, int b) {
	if (w->color)
		free(w->color);

	w->color = create_color(r, g, b, 0xFF);
	SDL_SetRenderDrawColor(w->renderer, r, g, b, 0xFF);
}

void draw_point_v2(window *w, v2 v) {
	SDL_RenderDrawPoint(w->renderer, v.x, v.y);
}

void draw_line_v2(window *w, v2 a, v2 b) {
	SDL_RenderDrawLine(w->renderer, a.x, a.y, b.x, b.y);
}

// Bresenham's Circle Drawing Algorithm
void draw_wireframe_circle_v2(window *w, v2 center, double radius) {
	// start from (x,y) = (0, radius)
	// either choose (x,y) = (x+1, y) or (x+1,y-1)

	double x = 0.0, y = radius;
	double d = 3 - 2 * radius;
	while (x <= y) {
		v2 p1 = { center.x + x, center.y + y },
		   p2 = { center.x - x, center.y + y },
		   p3 = { center.x + x, center.y - y },
		   p4 = { center.x - x, center.y - y },
		   p5 = { center.x + y, center.y + x },
		   p6 = { center.x - y, center.y + x },
		   p7 = { center.x + y, center.y - x },
		   p8 = { center.x - y, center.y - x };

		draw_point_v2(w, p1);
		draw_point_v2(w, p2);
		draw_point_v2(w, p3);
		draw_point_v2(w, p4);
		draw_point_v2(w, p5);
		draw_point_v2(w, p6);
		draw_point_v2(w, p7);
		draw_point_v2(w, p8);

		if (d < 0) {
			d = d + (4*x) + 6;
		} else {
			d = d + 4 * (x-y) + 10;
			y--;
		}

		++x;
	}
}

void draw_filled_circle_v2(window *w, v2 center, double radius) {
	double x = 0.0, y = radius;
	double d = 3 - 2 * radius;
	while (x <= y) {
		v2 p1 = { center.x + x, center.y + y },
		   p2 = { center.x + x, center.y - y },
		   p3 = { center.x + y, center.y + x },
		   p4 = { center.x + y, center.y - x },
		   p5 = { center.x - x, center.y + y },
		   p6 = { center.x - x, center.y - y },
		   p7 = { center.x - y, center.y + x },
		   p8 = { center.x - y, center.y - x };

		draw_line_v2(w, p1, p2);
		draw_line_v2(w, p3, p4);
		draw_line_v2(w, p5, p6);
		draw_line_v2(w, p7, p8);

		if (d < 0) {
			d = d + (4*x) + 6;
		} else {
			d = d + 4 * (x-y) + 10;
			y--;
		}

		++x;
	}
}

void draw_wireframe_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3) {
	draw_line_v2(w, vt1, vt2);
	draw_line_v2(w, vt1, vt3);
	draw_line_v2(w, vt2, vt3);
}

void draw_wireframe_triangle(window *w, triangle *t) {
	if (!t)
		return;
	draw_wireframe_triangle_v2(w, t->vt1, t->vt2, t->vt3);
}

void draw_filled_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3) {
	if (vt1.x > vt2.x)
		swap_v2(&vt1, &vt2);

	if (vt1.x > vt3.x) {
		swap_v2(&vt1, &vt3);
	}

	if (vt2.x > vt3.x) {
		swap_v2(&vt2, &vt3);
	}

	double m12 = (vt2.y - vt1.y) / (vt2.x - vt1.x),
		   m23 = (vt3.y - vt2.y) / (vt3.x - vt2.x),
		   m13 = (vt3.y - vt1.y) / (vt3.x - vt1.x);

	double midline = vt2.x - vt1.x;

	for (int dx = 0; dx <= vt3.x - vt1.x; dx++) {
		int y1 = vt1.y + m13 * dx, y2 = -1;
		if (dx < midline) { // not past midline: use line from v1 -> v2
			y2 = vt1.y + m12 * dx;
		} else { // past midline: use line from v2 -> v3
			y2 = vt2.y + m23 * (dx - midline);
		}

		v2 p1 = { vt1.x + dx, y1 },
		   p2 = { vt1.x + dx, y2 };

		draw_line_v2(w, p1, p2);
	}
}

void draw_filled_triangle(window *w, triangle *t) {
	if (!t)
		return;

	draw_filled_triangle_v2(w, t->vt1, t->vt2, t->vt3);
}

// v: top left
void draw_wireframe_rectangle_v2(window *w, v2 v, int width, int height) {
	if (width < 0)
		width *= -1;

	if (height < 0)
		height *= -1;

	// v: top left
	// p1: top right
	// p2: bottom left
	// p3: bottom right
	v2 p1 = { v.x + width, v.y },
	   p2 = { v.x, v.y + height },
	   p3 = { v.x + width, v.y + height };

	draw_line_v2(w, v, p1);
	draw_line_v2(w, v, p2);
	draw_line_v2(w, p2, p3);
	draw_line_v2(w, p1, p3);
}

void draw_filled_rectangle_v2(window *w, v2 v, int width, int height) {
	if (width < 0)
		width *= -1;

	if (height < 0)
		height *= -1;

	for (int y = 0; y < height; y++) {
		v2 p1 = { v.x, v.y + y }, p2 = { v.x + width, v.y + y };
		draw_line_v2(w, p1, p2);
	}
}

void draw_wireframe_square_v2(window *w, v2 v, int length) {
	draw_wireframe_rectangle_v2(w, v, length, length);
}

void draw_filled_square_v2(window *w, v2 v, int length) {
	draw_filled_rectangle_v2(w, v, length, length);
}

void draw_wireframe_polygon(window *w, polygon *p) {
	for (int j = 0; j < p->edge_count; ++j) {
		pair E = get_edge(p, j);

		void *vt1 = get_vertex(p, E.first),
			 *vt2 = get_vertex(p, E.second);

		draw_line_v2(w, *((v2*) vt1), *((v2*) vt2));
	}
}

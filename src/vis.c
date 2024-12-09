#include <SDL2/SDL.h>
#include "window.h"
#include "polygon.h"

int main(void) {
	window *w = init_window("heron", 500, 500);
	polygon *poly = init_polygon(true);
	list *points = init_list(sizeof(v2), 10);

	SDL_Event e;

	set_bg_color(w, 0x00, 0x00, 0x00);
	set_color(w, 0xFF, 0, 0);

	bool vis = false;

	while (!w->quit) {
		draw_bg(w);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				w->quit = true;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				v2 p = { x, y };
				push_vertex(poly, &p);
				push(points, &p);
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case (SDLK_ESCAPE):
						delete(points, points->length-1);
						break;
					case (SDLK_SPACE):
						if (vis)
							vis = false;
						else if (!vis && poly->vertex_count >= 3)
							vis = true;
						break;
				}
			}
		}

		for (int j = 0; j < points->length; j++) {
			v2 p = *(v2*) get_element(points, j);
			draw_filled_circle_v2(w, p, 5);
		}

		if (vis) {
			list *triangles = ear_clipping(poly);

			for (int j = 0; j < triangles->length; j++) {
				triangle *t = (triangle*) get_element(triangles, j);
				draw_wireframe_triangle(w, t);
			}

			destroy_list(triangles);
		}

		output_screen(w);
	}

	destroy_list(points);
	destroy_polygon(poly);
	destroy_window(w);
}

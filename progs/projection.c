#include <SDL2/SDL.h>
#include "../src/window.h"
#include "../src/mesh.h"

int main(void) {
	int x, y;

	window *w = init_window("heron", 500, 500);

	SDL_Event e;

	set_bg_color(w, 0x00, 0x00, 0x00);
	set_color(w, 0xFF, 0x00, 0x00);

	printf("L: %.2f, R: %.2f, T: %.2f, B: %.2f\n", w->camera->l, w->camera->r, w->camera->t, w->camera->b);

	v3 p = { 0, 0, 0.1 };

	mesh *m = init_mesh("./obj/isohedron.obj");

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	double delta = 0.05;

	while (!w->quit) {
		draw_bg(w);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				w->quit = true;

			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case (SDLK_w): { shift_pos(w->camera, 0, 0, -delta); break; }
					case (SDLK_s): { shift_pos(w->camera, 0, 0, +delta); break; }
					case (SDLK_d): { shift_pos(w->camera, +delta, 0, 0); break; }
					case (SDLK_a): { shift_pos(w->camera, -delta, 0, 0); break; }
					case (SDLK_SPACE): { shift_pos(w->camera, 0, state[SDL_SCANCODE_LSHIFT] ? -delta : +delta, 0); break; }
					default: break;
				}
			}
		}

		draw_mesh(w, m);

		output_screen(w);
	}

	destroy_window(w);
	destroy_mesh(m);
}

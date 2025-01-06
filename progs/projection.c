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

	while (!w->quit) {
		draw_bg(w);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				w->quit = true;
		}

		draw_mesh(w, m);

		output_screen(w);
	}

	destroy_window(w);
	destroy_mesh(m);
}

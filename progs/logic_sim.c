#include <stdio.h>
#include <SDL2/SDL.h>
#include "../src/window.h"
#include "../llama_sim/src/gate.h"

void draw_not_gate(window *w, int x, int y) {
	// (x,y) is top left
	v2 p1 = { x, y };
	set_color(w, 0xFF, 0xFF, 0xFF);
	draw_wireframe_square_v2(w, p1, 50);
}

int main(void) {
	window *w = init_window("circuit", 1000, 1000);

	SDL_Event e;

	set_bg_color(w, 0x00, 0x00, 0x00);

	while (!w->quit) {
		draw_bg(w);

		draw_not_gate(w, 250, 250);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				w->quit = true;
			}
		}

		output_screen(w);
	}

	destroy_window(w);
}

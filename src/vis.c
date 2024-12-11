#include <SDL2/SDL.h>
#include "avl.h"
#include "comparators.h"
#include "ll.h"
#include "polygon.h"
#include "window.h"

void add_to_poly(polygon *poly, avl_node *node) {
	if (!node)
		return;

	if (!poly)
		return;

	push_vertex(poly, (v2*) node->data);

	if (node->right)
		add_to_poly(poly, node->right);

	if (node->left)
		add_to_poly(poly, node->left);
}

void draw_point(window *w, avl_node *node) {
	if (!node)
		return;

	if (!w)
		return;

	v2 p = *(v2*) node->data;
	draw_filled_circle_v2(w, p, 10);

	if (node->right != NULL)
		draw_point(w, node->right);

	if (node->left != NULL)
		draw_point(w, node->left);
}

int main(void) {
	int x, y;
	window *w = init_window("heron", 500, 500);
	polygon *poly = init_polygon(true);
	avl_tree *points = init_avl_tree(sizeof(v2), sort_v2_by_x);
	avl_node *recent = NULL, *hover = NULL;

	SDL_Event e;

	set_bg_color(w, 0x00, 0x00, 0x00);
	set_color(w, 0xFF, 0, 0);

	bool vis = false, dragging = false;

	while (!w->quit) {
		draw_bg(w);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				w->quit = true;
			}

			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&x, &y);
				v2 p = { x, y };
				avl_node *node = avl_search(points, &p);

				if (node) {
					hover = node;
				}

				if (hover) {
					if (dist_v2((v2*) hover->data, &p) > 20) {
						hover = NULL;
					} else if (dragging) {
						memcpy(hover->data, &p, sizeof(v2));
					}
				}
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				// make drag functionality
				// can rearrange vertices of a polygon
				SDL_GetMouseState(&x, &y);
				v2 p = { x, y };

				if (hover) {
					dragging = true;
				} else {
					recent = avl_tree_insert(points, &p);
				}
			} else if (e.type == SDL_MOUSEBUTTONUP) {
				dragging = false;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case (27): // esc
						avl_tree_delete_node(points, recent);
						recent = NULL;
						break;
					case (13): // enter
						if (vis) {
							vis = false;
							destroy_polygon(poly);
							poly = init_polygon(true);
						} else {
							if (points->size >= 3) {
								vis = true;
								add_to_poly(poly, points->root);
							}
						}
						break;
				}
			}
		}

		draw_point(w, points->root);

		if (hover) {
			set_color(w, 0, 0xFF, 0);
			draw_filled_circle_v2(w, *(v2*) hover->data, 10);
			set_color(w, 0xFF, 0, 0);
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

	destroy_avl_tree(points);
	destroy_polygon(poly);
	destroy_window(w);
}

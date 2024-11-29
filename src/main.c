#include <SDL2/SDL.h>
#include "avl.h"
#include "bst.h"
#include "vec.h"
#include "mat.h"
#include "list.h"
#include "queue.h"
#include "segment.h"
#include "window.h"
#include "triangle.h"

void prtf_int(const void *a) {
	printf("%d", *(int*) a);
}

int cmp(const void *a, const void *b) {
	int x = *(int*) a,
		y = *(int*) b;

	return (x > y ? 1 : x < y ? -1 : 0);
}

int main(void) {
	/*
	window *w = init_window("heron", 500, 500);
	polygon *p = init_polygon(true);

	v2 p1 = { 100, 200 },
	   p2 = { 200, 300 },
	   p3 = { 400, 200 };

	push_vertex(p, &p1);
	push_vertex(p, &p2);
	push_vertex(p, &p3);

	add_edge(p, 0, 1);
	add_edge(p, 0, 2);
	add_edge(p, 2, 1);

	while (!w->quit) {
		tick(w);

		set_color(w, 0xff, 0x00, 0x00);

		draw_wireframe_polygon(w, p);

		output_screen(w);
	}

	destroy_window(w);

	destroy_polygon(p);

	list *l = init_list(sizeof(segment_v2), 10);

	v2 p1 = { 2, 6 },
	   p2 = { 8, 4 },
	   p3 = { 3, 9 },
	   p4 = { 5, 7 },
	   p5 = { 1, -1 },
	   p6 = { 5, 2 };

	segment_v2 s1 = { p1, p2 },
			   s2 = { p3, p4 },
			   s3 = { p5, p6 };

	push(l, &s1);
	push(l, &s2);
	push(l, &s3);

	bentley_ottmann(l);

	destroy_list(l);

	return 0;*/

	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;

	avl_tree* tree = init_avl_tree(sizeof(int), cmp);
	tree->prtf = prtf_int;

	//   2
	// 1   4
	//    3 5
	avl_tree_insert(tree, &a);
	avl_tree_insert(tree, &b);
	avl_tree_insert(tree, &c);
	avl_tree_insert(tree, &d);
	avl_tree_insert(tree, &e);


	inorder_print_avl_tree(tree);

	printf("\n");

	avl_tree_delete(tree, &d);

	//   2
	// 1   3
	//      5

	inorder_print_avl_tree(tree);

	avl_tree_delete(tree, &a);

	printf("\n");

	//   3
	// 2   5
	inorder_print_avl_tree(tree);

	avl_tree_insert(tree, &f);

	printf("\n");

	inorder_print_avl_tree(tree);

	avl_tree_delete(tree, &b);

	printf("\n");

	inorder_print_avl_tree(tree);

	return 0;
}

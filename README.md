# chimy
A 3D software renderer built in C using SDL2.

<p align="center" width="100%">
    <img width="100%" src="https://raw.githubusercontent.com/XORZK/chimy/refs/heads/main/img/ss1.png">
	isohedron mesh
</p>

## why c?
*chimy* is a project I've been working on for a while now. While originally created in C++, recently, I've decided to rewrite it in C. Going backwards a little bit, I know. 

I wanted a more complete understanding of memory management, and low level programming. Start from the bottom and work my way up. I didn't want everything to be handed to me, and so instead of using pre-written libraries containing pre-written data structures and algorithms, I wrote 99% of the code utilized in the renderer myself.

## data structures
- [avl.h](/src/avl.h): generic self-balancing binary search tree.
- [bst.h](/src/bst.h): generic binary search tree.
- [comparators.h](/src/comparators.h): for sorting and comparisons of generic structures (BSTs, AVLs, queues, lists, etc), we need generic comparators which take `void*` arguments and are organized in this header.
- [list.h](/src/list.h): generic, dynamic list structure that utilizes pointers to a `void*` array.
- [ll.h](/src/ll.h): generic, linked list structure used for polygon triangulation.
- [mat.h](/src/mat.h): represents matrices in $\mathbb{R}^{2 \times 2}$, $\mathbb{R}^{3 \times 3}$, and $\mathbb{R}^{4 \times 4}$ respectively.
- [queue.h](/src/queue.h): generic queue data structure, used primarily in the Bentley-Ottmann algorithm.
- [vec.h](/src/vec.h): represents vectors in $\mathbb{R}^2$, $\mathbb{R}^3$, and $\mathbb{R}^4$ respectively.

## demo: polygon triangulation
Polygon triangulation is one of the most vital parts of this program in my opinion. Decomposing polygons into simpler triangles, which makes a lot of operations much simpler, such as drawing meshes composed of thousands of polygons.
<p align="center">
  <img src="https://raw.githubusercontent.com/XORZK/chimy/refs/heads/main/img/triangulation_demo.gif" alt="triangulation demo">
  <br>
  polygon triangulation demo
</p>

## initializing a window
> creating a quick and simple program that draws a 2D triangle to the screen.
```c
int main(void) {
	int width = 500, height = 500;

	window *w = init_window("title", width, height);
	SDL_Event e;

	set_bg_color(w, 0x00, 0x00, 0x00);
	set_color(w, 0xFF, 0x00, 0x00); // set draw color to red

	// vertices of the triangle
	v2 p1 = { 100, 100 },
	   p2 = { 200, 200 },
	   p3 = { 400, 300 };

	while (!w->quit) {
		draw_bg(w);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				w->quit = true;
			}

			// react to other inputs here
			if (e.type == SDL_KEYDOWN) {	
				// ....
			}
		}

		// draws a (non-filled) triangle
		draw_wireframe_triangle_v2(w, p1, p2, p3);

		output_screen(w);
	}

	destroy_window(w); // frees the screen
}
```

## structs and functions

### `vec.h`
```c
typedef struct {
	double x, y;
} v2;
```
```c
typedef struct {
	double x, y, z;
} v3;
```
```c
typedef struct {
	double x1, x2, x3, x4;
} v4;
```
```c
typedef struct {
	int x1, x2, x3;
} v3i;
```

### `list.h`
```c
typedef struct {
	void* data;
	int type_size;
	int length, capacity;
} list;
```
- `list* init_list(int tsize, int c):` initializes a list that holds objects of size `tsize` with capacity `c`
- `void set_l(list *l`


### `triangle.h`
```c
typedef struct {
	v2 vt1;
	v2 vt2;
	v2 vt3;
} triangle;
```

### `polygon.h`
```c
// vertices
// edges connecting vertices
// edges: (v_j, v_k) connects vertex j to vertex k
typedef struct {
	int64_t vertex_count, edge_count;
	v2 centroid;
	list *vertices, *edges;
} polygon;
```

### `mesh.h`
```c
typedef struct mesh {
	list *F, *V;
} mesh;
```

### `window.h`
- `void set_color(window *w, int r, int g, int b):` sets the render color to (r,g,b).
- `void draw_point_v2(window *w, v2 v):` draws a 2D point at `v`.
- `void draw_line_v2(window *w, v2 p1, v2 p2):` draws a line that connects `p1` and `p2`.
- `void draw_wireframe_circle_v2(window *w, v2 p, double r):` draws a circle centered at `p` with radius `r`.
- `void draw_filled_circle_v2(window *w, v2 p, double r):` draws a filled circled centered at `p` with radius `r`.
- `void draw_wireframe_triangle(window *w, triangle *t):` draws a triangle w/ vertices `t->vt1`, `t->vt2`, `t->vt3`.
- `void draw_wireframe_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3):` draws a triangle w/ vertices `vt1`, `vt2`, `vt3`.
- `void draw_filled_triangle_v2(window *w, v2 vt1, v2 vt2, v2 vt3):` draws a filled triangle w/ vertices `vt1`, `vt2`, `vt3`.
- `void draw_wireframe_rectangle_v2(window *w, v2 v, int w, int h):` draws a rectangle w/ width `w` and height `h`, top left corner positioned at `v`.
- `void draw_filled_rectangle_v2(window *w, v2 v, int w, int h):` draws a filled rectangle w/ width `w` and height `h`, top left corner positioned at `v`.
- `void draw_wireframe_square_v2(window *w, v2 v, int l):` draws a square w/ length `l` and top left corner positioned at `v`.
- `void draw_filled_square_v2(window *w, v2 v, int l):` draws a filled square w/ length `l` and top left corner positioned at `v`.
- `void draw_wireframe_polygon(window *w, polygon *p):` draws a polygon defined by `p`.
- `void draw_point_v3(window *w, v3 v):` draws the 3D point at `v`.
- `void draw_line_v3(window *w, v3 p1, v3 p2):` draws a line that connects `p1` and `p2` in 3D.
- `void draw_wireframe_circle_v3(window *w, v3 p, double r):` draws a circle in 3D centered at `p` with radius `r`.
- `void draw_filled_circle_v3(window *w, v3 p, double r):` draws a filled circle in 3D centered at `p` with radius `r`.
- `void draw_wireframe_triangle_v3(window *w, v3 vt1, v3 vt2, v3 vt3):` draws a triangle in 3D defined by vertices `vt1`, `vt2`, and `vt3`.
- `void draw_filled_triangle_v3(window *w, v3 vt1, v3 vt2, v3 vt3):` draws a filled triangle in 3D defined by vertices `vt1`, `vt2`, and `vt3`.
- `void draw_wireframe_rectangle_v3(window *w, v3 v, int w, int h):` draws a rectangle in 3D with top left corner at `v`, width `w` and height `h`.
- `void draw_filled_rectangle_v3(window *w, v3 v, int w, int h):` draws a filled rectangle in 3D with top left corner at `v`, width `w` and height `h`.
- `void draw_wireframe_square_v3(window *w, v3 v, int l):` draws a square in 3D with top left corner at `v`, and length `l`.
- `void draw_filled_square_v3(window *w, v3 v, int l):` draws a filled square in 3D with top left corner at `v` and length `l`.
- `void draw_mesh(window *w, mesh *m):` draws a 3D mesh defined by `m`.

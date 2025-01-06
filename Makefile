OUT=chimy
IN=src/vec.c src/mat.c src/window.c src/color.c src/triangle.c src/list.c src/polygon.c src/pair.c src/segment.c src/queue.c src/bst.c src/avl.c src/comparators.c src/tuple.c src/ll.c src/convex_hull.c src/camera.c src/mesh.c progs/projection.c
LIB=-lSDL2

default:
	gcc -g -std=c17 -O3 -lm $(IN) -o $(OUT) $(LIB) && ./$(OUT)

docs:
	doxygen $(DOC)


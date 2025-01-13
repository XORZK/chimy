OUT=chimy
IN=src/vec.c src/mat.c src/window.c src/color.c src/triangle.c src/list.c src/polygon.c src/pair.c src/segment.c src/queue.c src/bst.c src/avl.c src/comparators.c src/tuple.c src/ll.c src/convex_hull.c src/camera.c src/mesh.c src/light.c progs/logic_sim.c
LIB_IN=llama_sim/src/wire.c llama_sim/src/gate.c llama_sim/src/switch.c
LIB=-lSDL2

default:
	gcc -g -std=c17 -O3 -lm $(LIB_IN) $(IN) -o $(OUT) $(LIB) && ./$(OUT)

docs:
	doxygen $(DOC)


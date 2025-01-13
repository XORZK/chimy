# chimy
A 3D software renderer built in C using SDL2.

<p align="center" width="100%">
    <img width="100%" src="https://raw.githubusercontent.com/XORZK/chimy/refs/heads/main/img/ss1.png">
	isohedron
</p>

## why c?
*chimy* is a project I've been working on for a while now. While originally created in C++, recently, I've decided to rewrite it in C. Going backwards a little bit, I know. 

I wanted a more complete understanding of memory management, and low level programming. Start from the bottom and work my way up. I didn't want everything to be handed to me, and so instead of using pre-written libraries containing pre-written data structures and algorithms, I wrote 99% of the code utilized in the renderer myself.

## data structures
- [list.h](/src/list.h): generic, dynamic list structure that utilizes pointers to a `void*` array.
- [ll.h](/src/ll.h): generic, linked list structure used for polygon triangulation.
- [vec.h](/src/vec.h): represents vectors in $\mathbb{R}^2$, $\mathbb{R}^3$, and $\mathbb{R}^4$ respectively.
- [mat.h](/src/mat.h): represents matrices in $\mathbb{R}^{2 \cross 2}$, $\mathbb{R}^{3 \cross 3}$, and $\mathbb{R}^{4 \cross 4}$

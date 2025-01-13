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

## polygon triangulation
polygon triangulation is one of 
<p align="center">
  <img src="https://raw.githubusercontent.com/XORZK/chimy/refs/heads/main/img/triangulation_demo.gif" alt="triangulation demo">
  <br>
  polygon triangulation simulation
</p>


#ifndef AVL_H
#define AVL_H

#pragma once
#include <stdbool.h>

// avl tree: self balancing binary search tree
// balance factor of node X
// BF(X) = Height(X->Right) - Height(X->Left)
// BF(X) < 0: Left Heavy
// BF(X) > 0: Right Heavy
// BF(X) = 0: Balanced
typedef struct avl_node {
	void *data;
	struct avl_node *left;
	struct avl_node *right;
	struct avl_node *parent;
	int height;
	char balance_factor;
} avl_node;

typedef struct {
	avl_node *root;
	int type_size;
	int size;
	int height;
	int (*cmp)(const void *, const void *);
	void (*prtf)(const void *);
} avl_tree;

void swap_avl_node_ptr(avl_node **p1, avl_node **p2);

bool is_right_child(avl_node *node);

bool is_left_child(avl_node *node);

int avl_count_children(avl_node *node);

void set_right(avl_node *parent, avl_node *child);

void set_left(avl_node *parent, avl_node *child);

void rotate(avl_node *a, avl_node *b, avl_node *c, int type);

avl_node* create_avl_node(void *v, int tsize);

avl_tree* init_avl_tree(int tsize, int (*comparator)(const void *, const void *));

void update_avl_heights(avl_node *node);

void update_node_heights(avl_node *node);

void update_balance_factors(avl_node *node, char dh);

avl_node* avl_tree_insert(avl_tree *tree, void *data);

void avl_tree_delete(avl_tree *tree, void *data);

void avl_tree_delete_node(avl_tree *tree, avl_node *node);

void destroy_avl_node(avl_node *node);

void inorder_print_avl_node(avl_node *node, void print(const void *));

void inorder_print_avl_tree(avl_tree *tree);

void recursively_destroy_avl_nodes(avl_node *node);

void destroy_avl_tree(avl_tree *tree);

#endif

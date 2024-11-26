#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_avl_node_ptr(avl_node **p1, avl_node **p2) {
	avl_node *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

bool is_right_child(avl_node *node) {
	if (!node || node->parent == NULL)
		return false;

	return (node->parent->right == node);
}

bool is_left_child(avl_node *node) {
	if (!node || node->parent == NULL)
		return false;

	return (node->parent->left == node);
}

void set_right(avl_node *parent, avl_node *child) {
	if (parent)
		parent->right = child;
	if (child)
		child->parent = parent;
}

void set_left(avl_node *parent, avl_node *child) {
	if (parent)
		parent->left = child;
	if (child)
		child->parent = parent;
}

// a < b < c
// type:
// 0: LL
// 1: RR
// 2: LR
// 3: RL
avl_node* avl_rotate(avl_node *x, avl_node *y, avl_node *z, int type) {
	bool zr = is_right_child(z);
	// T1 -> T4: child branches of x,y,z from L -> R
	// depends on rotation type
	avl_node *T1, *T2, *T3, *T4;
	avl_node *a, *b, *c;
	avl_node *parent = z->parent;
	if (type == 0) {
		T1 = z->left; T2 = y->left; T3 = x->left; T4 = x->right;
		a = z; b = y; c = x;
	} else if (type == 1) {
		T1 = x->left; T2 = x->right; T3 = y->right; T4 = z->right;
		a = x; b = y; c = z;
	} else if (type == 2) {
		T1 = z->left; T2 = x->left; T3 = x->right; T4 = y->right;
		a = z; b = x; c = y;
	} else {
		T1 = y->left; T2 = x->left; T3 = x->right; T4 = z->right;
		a = y; b = x; c = z;
	}

	if (type == 0) {
		set_left(b, a);
		set_right(a, T2);
	} else if (type == 1) {
		set_right(b, c);
		set_left(c, T3);
	} else if (type == 2) {
		set_right(a, b);
		set_right(b, c);
		set_left(c, T3);
		avl_rotate(c, b, a, 0);
	} else {
		set_left(c, b);
		set_left(b, a);
		set_right(a, T2);
		avl_rotate(a, b, c, 1);
	}

	if (type <= 1) {
		if (zr)
			set_right(parent, b);
		else
			set_left(parent, b);
	}

	update_node_heights(a);
	update_node_heights(c);
	update_node_heights(b);

	return b;
}

// x->parent = y
// y->parent = z
int determine_rotation_type(avl_node *x, avl_node *y, avl_node *z) {
	if (!x || !y || !z)
		return -1;

	bool xr = is_right_child(x), yr = is_right_child(y);

	return ((xr && yr) ? 0 : (!yr && !xr) ? 1 : (yr && !xr) ? 2 : 3);
}

avl_node* create_avl_node(void *v, int tsize) {
	avl_node* node = (avl_node*) malloc(sizeof(avl_node));

	node->data = malloc(tsize);

	memcpy(node->data, v, tsize);

	node->left = node->right = node->parent = NULL;
	node->balance_factor = 0;
	node->height = 1;

	return node;
}

avl_tree* init_avl_tree(int tsize, int (*comparator)(const void *, const void *)) {
	avl_tree* tree = (avl_tree*) malloc(sizeof(avl_tree));

	tree->root = NULL;
	tree->type_size = tsize;
	tree->cmp = comparator;
	tree->size = tree->height = 0;

	return tree;
}

void update_avl_heights(avl_node *node) {
	if (!node)
		return;

	update_node_heights(node);

	update_avl_heights(node->parent);
}

void update_node_heights(avl_node *node) {
	if (!node)
		return;

	int rh = (node->right ? node->right->height : 0),
		lh = (node->left ? node->left->height : 0);

	node->height = 1 + (rh > lh ? rh : lh);
	node->balance_factor = (char) (rh - lh);
}

void update_balance_factors(avl_node *node, char dh) {
	if (node == NULL)
		return;

	node->balance_factor += dh;

	if (node->parent != NULL) {
		update_balance_factors(node->parent, is_right_child(node) ? 1 : -1);
	}
}

void avl_tree_insert(avl_tree *tree, void *data) {
	if (!tree)
		return;

	avl_node *new_node = create_avl_node(data, tree->type_size);

	// standard bst insert
	if (tree->root == NULL) {
		tree->root = new_node;
	} else {
		avl_node *curr = tree->root;

		while (1) {
			int c = tree->cmp(curr->data, data);

			if (c > 0) {
				if (curr->left == NULL) {
					curr->left = (struct avl_node*) new_node;
					new_node->parent = curr;
					break;
				} else {
					curr = curr->left;
				}
			} else {
				if (curr->right == NULL) {
					curr->right = (struct avl_node*) new_node;
					new_node->parent = curr;
					break;
				} else {
					curr = curr->right;
				}
			}
		}

		// recursively go up and change balance factors
		// O(log n)
		update_avl_heights(curr);

		avl_node *x = new_node, *y = NULL, *z = NULL;
		// trace back to the first node whose grandparent is unbalanced
		while (1) {
			y = x->parent;
			z = (y == NULL ? NULL : y->parent);

			if (!z || z->balance_factor == 2 || z->balance_factor == -2)
				break;
			else
				x = x->parent;

		}

		bool is_root = (z == tree->root); // need to check if z is root

		if (z) {
			int type = determine_rotation_type(x, y, z);
			avl_node *b = avl_rotate(x, y, z, type);

			if (is_root) {
				tree->root = b;
			}
		}
	}

	tree->size++;
}

void destroy_avl_node(avl_node *node) {
	if (!node)
		return;

	if (node->parent != NULL) {
		if (is_right_child(node))
			node->parent->right = NULL;
		else
			node->parent->left = NULL;
	}

	node->right = node->left = node->parent = NULL;

	if (node->data)
		free(node->data);

	free(node);
}

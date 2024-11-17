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
	parent->right = child;
	child->parent = parent;
}

void set_left(avl_node *parent, avl_node *child) {
	parent->left = child;
	child->parent = parent;
}

avl_node* create_avl_node(void *v, int tsize) {
	avl_node* node = (avl_node*) malloc(sizeof(avl_node));

	node->data = malloc(tsize);

	memcpy(node->data, v, tsize);

	node->left = node->right = node->parent = NULL;
	node->balance_factor = 0;

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

void update_balance_factors(avl_node *node, char dh) {
	if (!node)
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
				} else {
					curr = curr->left;
				}
			} else {
				if (curr->right == NULL) {
					curr->right = (struct avl_node*) new_node;
					new_node->parent = curr;
				} else {
					curr = curr->right;
				}
			}
		}

		// recursively go up and change balance factors
		// O(log n)
		update_balance_factors(curr, is_right_child(new_node) ? 1 : -1);

		avl_node *x = new_node, *y = NULL, *z = NULL;
		// trace back to the first node whose grandparent is unbalanced
		while (1) {
			y = x->parent;
			z = (y == NULL ? NULL : y->parent);

			if (!z || z->balance_factor == 2 || z->balance_factor == -2)
				break;
		}

		if (z) {
			bool yr = is_right_child(y), xr = is_right_child(x);

			// 4 cases: depends on is_right_child(y) and is_right_child(x)
			// case 1: is_right_child(y), is_right_child(x)
			// T1, T2, T3, T4: z.left, y.left, x.left, x.right
			//
			// case 2: is_right_child(y), !is_right_child(x)
			// T1, T2, T3, T4: z.left, x.left, x.right, y.right
			//
			// case 3: !is_right_child(y), is_right_child(x)
			// T1, T2, T3, T4: y.left, x.left, x.right, z.right
			//
			// case 4: !is_right_child(y), !is_right_child(x)
			// T1, T2, T3, T4: x.left, x.right, y.right, z.right
			avl_node *T1 = (yr ? z->left : xr ? y->left : x->left),
			         *T2 = (yr != xr ? x->left : xr ? y->left : x->right),
			         *T3 = (yr != xr ? x->right : xr ? x->left : y->right),
			         *T4 = (!yr ? z->right : xr ? x->right : y->right);

			avl_node *a = x, *b = y, *c = z;

			// bubble sort unrolled
			// b->left = a
			// b->right = c
			if (tree->cmp(a,b) > 0) { swap_avl_node_ptr(&a, &b); }
			if (tree->cmp(b,c) > 0) { swap_avl_node_ptr(&b, &c); }
			if (tree->cmp(a,b) > 0) { swap_avl_node_ptr(&a, &b); }

			set_left(b, a);
			set_right(b, c);
			set_left(a, T1);
			set_right(a, T2);
			set_left(c, T3);
			set_right(c, T4);

			// TODO: fix balance factor on each node
			// T1, T2, T3, T4 balance factor still holds
			// just need to fix BF(a, b, c)
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

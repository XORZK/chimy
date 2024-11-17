#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bst_node* create_bst_node(void *v, int tsize) {
	bst_node* node = (bst_node*) malloc(sizeof(bst_node));

	node->data = malloc(tsize);

	memcpy(node->data, v, tsize);

	node->left = node->right = NULL;

	return node;
}

int count_children(bst_node *node) {
	if (!node)
		return -1;

	return (node->right != NULL) + (node->left != NULL);
}

bst* init_bst(int tsize, int (*comparator)(const void *, const void *)) {
	bst *tree = (bst*) malloc(sizeof(bst));

	tree->root = NULL;
	tree->type_size = tsize;
	tree->size = 0;
	tree->cmp = comparator;

	return tree;
}

void bst_insert(bst *tree, void *data) {
	if (!tree)
		return;

	if (tree->root == NULL) {
		tree->root = create_bst_node(data, tree->type_size);
	} else {
		bst_node *curr = tree->root;

		while (1) {
			int c = tree->cmp(curr->data, data);
			// data < curr->data
			// left
			if (c > 0) {
				if (curr->left == NULL) {
					curr->left = (struct bst_node*) create_bst_node(data, tree->type_size);
				} else {
					curr = curr->left;
				}
			} else {
				if (curr->right == NULL) {
					curr->right = (struct bst_node*) create_bst_node(data, tree->type_size);
				} else {
					curr = curr->right;
				}
			}
		}
	}

	tree->size++;
}

bst_node* bst_search(bst *tree, void *data) {
	if (!tree)
		return (bst_node*) NULL;

	bst_node *curr = tree->root;

	while (curr != NULL) {
		int c = tree->cmp(curr->data, data);
		if (c == 0)
			return curr;

		// data < curr->data
		if (c > 0)
			curr = curr->left;
		else
			curr = curr->right;
	}

	return NULL;
}

void bst_delete(bst *tree, void *data) {
	if (!tree)
		return;

	if (tree->size == 0)
		return;

	bst_node *curr = tree->root, *parent = tree->root;

	while (curr != NULL) {
		int c = tree->cmp(curr->data, data);

		if (c == 0)
			break;

		parent = curr;

		if (c > 0)
			curr = curr->left;
		else
			curr = curr->right;
	}

	if (!curr || !parent)
		return;

	int children = count_children(curr);
	bool right_child = (parent->right == curr);

	if (children == 0) {
		if (right_child)
			parent->right = NULL;
		else
			parent->left = NULL;

		destroy_bst_node(curr);
	} else if (children == 1) {
		bst_node *curr_child = (curr->right == NULL ? curr->left : curr->right);

		if (right_child)
			parent->right = curr_child;
		else
			parent->left = curr_child;

		destroy_bst_node(curr);
	} else {
		// find inorder successor: smallest value greater than curr
		bst_node* succ = NULL;
		if (curr->right->left != NULL) {
			succ = curr->right->left;
			while (succ->left != NULL)
				succ = succ->left;
		} else {
			// go up currs parents until parent is a left child
			// because for curr to be in left branch of some node, it must be smaller
			// but if parent is a right child, then curr must be larger than that parent
			// start at root
			// if data < succ, go left
			// if data > succ.left, right branch of succ.left
			bst_node* its = tree->root;
			while (its != NULL) {
				// its->data > curr->data
				if (tree->cmp(its->data, curr->data) > 0) {
					succ = its;
					its = its->left;
				} else {
					its = its->right;
				}
			}
		}

		// found succ
		// remove succ
		// replace curr with succ
		void *copy = malloc(tree->type_size);
		memcpy(copy, succ->data, tree->type_size);

		bst_delete(tree, succ->data);

		free(curr->data);
		curr->data = copy;
	}
}

void destroy_bst_node(bst_node *node) {
	if (!node)
		return;

	node->right = node->left = NULL;

	if (node->data)
		free(node->data);

	free(node);
}

void recursively_destroy_nodes(bst_node *node) {
	if (!node)
		return;

	recursively_destroy_nodes(node->right);
	recursively_destroy_nodes(node->left);
	destroy_bst_node(node);
}

// TODO: doesn't destroy every node only root
// need to traverse and destroy recursively
void destroy_tree(bst *tree) {
	if (!tree)
		return;

	recursively_destroy_nodes(tree->root);

	free(tree);
}

void print_tree(bst_node *root, void (*prtf)(const void *)) {
	if (!root)
		return;

	print_tree(root->left, prtf);
	prtf(root->data);
	print_tree(root->right, prtf);
}

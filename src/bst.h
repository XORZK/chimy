#ifndef BST_H
#define BST_H

// generic bst
// need comparator off the bat.
typedef struct bst_node {
	void *data;
	struct bst_node *left;
	struct bst_node *right;
} bst_node;

typedef struct {
	bst_node *root;
	int type_size;
	int size;
	int (*cmp) (const void *, const void *);
} bst;

bst_node* create_bst_node(void *v, int tsize);

int count_children(bst_node *node);

bst* init_bst(int tsize, int (*comparator)(const void *, const void *));

void bst_insert(bst *tree, void *data);

bst_node* bst_search(bst *tree, void *data);

void bst_delete(bst *tree, void *data);

void destroy_bst_node(bst_node *node);

void recursively_destroy_nodes(bst_node *node);

void destroy_tree(bst *tree);

void print_tree(bst_node *tree, void (*prtf)(const void *));

#endif

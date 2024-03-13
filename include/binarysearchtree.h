#ifndef BST
#define BST

#include "binarysearchtreenode.h"

struct BinarySearchTree {
  struct BinarySearchTreeNode *root;
};

typedef struct BinarySearchTree BinarySearchTree;

void print_node(struct BinarySearchTreeNode *n);
void print_t_po(struct BinarySearchTreeNode *t);
BinarySearchTree BinarySearchTree_init(int *data, int size);
void BinarySearchTree_insert_tree_node(struct BinarySearchTree *t, int x);
void BinarySearchTree_insert_node(struct BinarySearchTreeNode *c, int x);
BinarySearchTreeNode BinarySearchTree_search_tree_node(struct BinarySearchTree *t, int x);
BinarySearchTreeNode BinarySearchTree_search_node(struct BinarySearchTreeNode *c, int x);

#endif

#ifndef BST
#define BST

#include "binarysearchtreenode.h"

struct BinarySearchTree {
  struct BinarySearchTreeNode *root;
  int size;
};
typedef struct BinarySearchTree BinarySearchTree;

void BinarySearchTree_init(struct BinarySearchTree *t, int *datum, int size);
struct BinarySearchTreeNode* BinarySearchTree_init_rec(int arr[], int start, int end);
struct BinarySearchTreeNode* BinarySearchTree_search(struct BinarySearchTreeNode *x, int k);
void BinarySearchTree_insert(struct BinarySearchTree *t, int z);
void BinarySearchTree_delete(struct BinarySearchTree *t, int d);
BinarySearchTreeNode BinarySearchTree_successor(struct BinarySearchTreeNode *x);
BinarySearchTreeNode BinarySearchTree_predecessor(struct BinarySearchTreeNode *x);
BinarySearchTreeNode BinarySearchTree_max(struct BinarySearchTreeNode *x);
BinarySearchTreeNode BinarySearchTree_min(struct BinarySearchTreeNode *x);
void BinarySearchTree_in_order(struct BinarySearchTreeNode *x);
void BinarySearchTree_pre_order(struct BinarySearchTreeNode *x);
void BinarySearchTree_post_order(struct BinarySearchTreeNode *x);

#endif

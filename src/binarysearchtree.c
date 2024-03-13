#include "../include/binarysearchtree.h"
#include <stdio.h>
#include <stdlib.h>

void BinarySearchTree_init(struct BinarySearchTree *t, int *datum, int size) {
  struct BinarySearchTreeNode *r = malloc(sizeof(struct BinarySearchTreeNode));
  r = BinarySearchTree_init_rec(datum, 0, size);
  t->root = r;
}

struct BinarySearchTreeNode *BinarySearchTree_init_rec(int datum[], int start,
                                                       int end) {
  if (start > end)
    return NULL;

  int mid = (start + end) / 2;

  struct BinarySearchTreeNode *root =
      &((BinarySearchTreeNode){datum[mid], NULL, NULL, NULL});

  root->left = BinarySearchTree_init_rec(datum, start, mid - 1);
  root->right = BinarySearchTree_init_rec(datum, mid + 1, end);

  return root;
}

struct BinarySearchTreeNode* BinarySearchTree_search(struct BinarySearchTreeNode *x, int k) {
  if (x == NULL) {
    return x;
  } else if (x && x->data == k) {
    return x;
  } else if (k < x->data) {
    return BinarySearchTree_search(x->left, k);
  } else {
    return BinarySearchTree_search(x->right, k);
  }
}

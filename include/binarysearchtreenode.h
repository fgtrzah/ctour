#ifndef BSTNode
#define BSTNode

struct BinarySearchTreeNode {
  int data;
  struct BinarySearchTreeNode *left;
  struct BinarySearchTreeNode *right;
  struct BinarySearchTreeNode *parent;
};
typedef struct BinarySearchTreeNode BinarySearchTreeNode;

#endif

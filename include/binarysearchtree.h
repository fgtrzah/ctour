#ifndef BST_H
#define BST_H

typedef struct BSTTreeNode {
  int data;
  struct BSTTreeNode *left;
  struct BSTTreeNode *right;
} BSTTreeNode;

typedef struct BST {
  BSTTreeNode *root;
} BST;

// Function prototypes
BST* createBST();
BST* initializeBST(int datum[], int n);
void destroyBST(BST *bst);
void insert(BST *bst, int data);
void removeNode(BST *bst, int data);
BSTTreeNode* search(BST *bst, int data);
void inorderTraversal(BSTTreeNode *root);
void preorderTraversal(BSTTreeNode *root);
void postorderTraversal(BSTTreeNode *root);

#endif /* BST_H */

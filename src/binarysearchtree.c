#include "../include/binarysearchtree.h"

#include <stdio.h>
#include <stdlib.h>

// Function to create a new tree
BST *createBST() {
  BST *bst = (BST *)malloc(sizeof(BST));
  if (bst) {
    bst->root = NULL;
  }
  return bst;
}

BST *initializeBST(int datum[], int n) {
  BST *bst = createBST();

  for (int i = 0; i < n; i++) {
    insert(bst, datum[i]);
  }

  return bst;
}

// Function to destroy the tree
void destroyTree(BSTTreeNode *root) {
  if (root) {
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
  }
}

void destroyBST(BST *bst) {
  if (bst) {
    destroyTree(bst->root);
    free(bst);
  }
}

void insertNode(BSTTreeNode **root, int data) {
  if (*root == NULL) {
    BSTTreeNode *newNode = (BSTTreeNode *)malloc(sizeof(BSTTreeNode));
    if (newNode) {
      newNode->data = data;
      newNode->left = NULL;
      newNode->right = NULL;
      *root = newNode;
    }
  } else {
    if (data < (*root)->data) {
      insertNode(&((*root)->left), data);
    } else if (data > (*root)->data) {
      insertNode(&((*root)->right), data);
    }
  }
}

void insert(BST *bst, int data) {
  if (bst) {
    insertNode(&(bst->root), data);
  }
}

BSTTreeNode *findMin(BSTTreeNode *root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

BSTTreeNode *deleteNode(BSTTreeNode *root, int data) {
  if (root == NULL) {
    return root;
  } else if (data < root->data) {
    root->left = deleteNode(root->left, data);
  } else if (data > root->data) {
    root->right = deleteNode(root->right, data);
  } else {
    // Node with only one child or no child
    if (root->left == NULL) {
      BSTTreeNode *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      BSTTreeNode *temp = root->left;
      free(root);
      return temp;
    }

    BSTTreeNode *temp = findMin(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }
  return root;
}

void removeNode(BST *bst, int data) {
  if (bst && bst->root) {
    bst->root = deleteNode(bst->root, data);
  }
}

BSTTreeNode *searchNode(BSTTreeNode *root, int data) {
  if (root == NULL || root->data == data) {
    return root;
  }
  if (root->data < data) {
    return searchNode(root->right, data);
  }
  return searchNode(root->left, data);
}

BSTTreeNode *search(BST *bst, int data) {
  if (bst) {
    return searchNode(bst->root, data);
  }
  return NULL;
}

void inorderTraversal(BSTTreeNode *root) {
  if (root) {
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
  }
}

void preorderTraversal(BSTTreeNode *root) {
  if (root) {
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
  }
}

// Function for postorder traversal
void postorderTraversal(BSTTreeNode *root) {
  if (root) {
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
  }
}

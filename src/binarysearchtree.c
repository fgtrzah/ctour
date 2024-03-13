#include "../include/binarysearchtree.h"
#include <stdio.h>
#include <stdlib.h>

void print_node(struct BinarySearchTreeNode *n) {
  if (!n || !n->data) {
    printf("empty");
    return;
  }

  printf("%d\n", n->data);
  if (n->left)
    printf("%d ", n->left->data);
  if (n->right)
    printf("%d ", n->right->data);
}

void print_t_po(struct BinarySearchTreeNode *t) {
  if (!t || !t->data)
    return;

  print_node(t);
  print_t_po(t->left);
  print_t_po(t->right);
}

BinarySearchTree BinarySearchTree_init(int * data, int size) {
  printf("%lu\t%lu\t\n", sizeof(data), sizeof(int));
  struct BinarySearchTree *t =
      malloc(size * (sizeof(int) + 3 * sizeof(struct BinarySearchTreeNode)));
  t = &((BinarySearchTree){
      &((struct BinarySearchTreeNode){data[0], NULL, NULL, NULL})});

  __auto_type x = t;

  for (int i = 0; i < size; i++) {
    BinarySearchTree_insert_tree_node(t, data[i]);
  }

  struct BinarySearchTreeNode *ct = t->root;
  print_t_po(ct);
  return *t;
}

void BinarySearchTree_insert_tree_node(struct BinarySearchTree *t, int x) {
  if (!t->root) {
    struct BinarySearchTreeNode *nn =
        malloc(sizeof(int) + 3 * sizeof(struct BinarySearchTreeNode));
    nn->data = x;
    t->root = nn;
  } else {
    BinarySearchTree_insert_node(t->root, x);
  }
}

void BinarySearchTree_insert_node(struct BinarySearchTreeNode *c, int x) {
  int nnsize = sizeof(int) + sizeof(struct BinarySearchTreeNode);
  struct BinarySearchTreeNode *nn = malloc(nnsize);
  nn->data = x;

  if (x <= c->data) {
    if (c->left) {
      BinarySearchTree_insert_node(c->left, x);
    } else {
      c->left = nn;
      c->left->parent = c;
    }
  } else {
    if (c->right) {
      BinarySearchTree_insert_node(c->right, x);
    } else {
      c->right = nn;
      c->right->parent = c;
    }
  }
}

BinarySearchTreeNode
BinarySearchTree_search_tree_node(struct BinarySearchTree *t, int x) {
  if (!t) {
    return (BinarySearchTreeNode){-1, NULL, NULL, NULL};
  }

  return BinarySearchTree_search_node(t->root, x);
}

BinarySearchTreeNode
BinarySearchTree_search_node(struct BinarySearchTreeNode *c, int x) {
  if (!c || c->data == x) {
    return *c;
  }

  int cd = c->data;

  if (x < cd && c->left) {
    return BinarySearchTree_search_node(c->left, x);
  } else if (x > cd && c->right) {
    return BinarySearchTree_search_node(c->right, x);
  }

  return *c;
}

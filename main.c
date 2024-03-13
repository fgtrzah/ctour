#include "include/binarysearchtree.h"
#include "include/binarysearchtreenode.h"
#include "include/linkedlist.h"
#include "include/linkedlistnode.h"
#include "include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_stack() {
  struct Stack *stack = malloc(sizeof(struct Stack));

  Stack_init(stack);
  Stack_push(stack, 10);

  assert(Stack_peek(stack) == 10);
  Stack_push(stack, 20);
  assert(Stack_peek(stack) == 20);
  Stack_push(stack, 30);
  assert(Stack_peek(stack) == 30);

  Stack_push(stack, 40);

  assert(Stack_peek(stack) == 40);
  assert(Stack_pop(stack) == 40);
  assert(Stack_pop(stack) == 30);
  assert(Stack_pop(stack) == 20);
  assert(Stack_pop(stack) == 10);
  assert(Stack_pop(stack) == -1);
}

void test_linkedlist() {
  int lcap = sizeof(struct LinkedList) + 2 * sizeof(struct LinkedListNode) +
             sizeof(int);
  int llncap = sizeof(int) + 2 * sizeof(struct LinkedListNode);
  struct LinkedList *l = calloc(5, lcap);
  LinkedList_init(l, 2);

  assert(l->head->data == 2);
  assert(LinkedList_search(l, 0).data == 2);
  LinkedList_append(l, 4);
  assert(l->head->next->data == 4);
  struct LinkedListNode *nnr1 = malloc(llncap);
  *nnr1 = LinkedList_insert(l, 1, 3);

  assert(l->head->next->data == 3);
  assert(l->head->next->next->data == 4);

  struct LinkedList *m = malloc(2 * lcap + (2 * llncap));

  assert(LinkedList_delete(m, 0) == -1);
  assert(LinkedList_delete(NULL, 0) == -1);

  LinkedList_init(m, 1);
  LinkedList_append(m, 5);
  LinkedList_append(m, 6);
  LinkedList_append(m, 7);

  assert(LinkedList_delete(m, 3) == 7);
  assert(LinkedList_delete(m, 2) == 6);
  assert(LinkedList_delete(m, 1) == 5);
  assert(LinkedList_delete(m, 0) == 1);
}

void print_node(struct BinarySearchTreeNode *x) {
  printf("%d \n", x->data);
  printf("%p \n ", (void *)x->left);
  printf("%p \n ", (void *)x->right);
}

void test_bst() {
  int fixture[] = {1, 2, 3, 4, 10, 16, 17, 18, 25};
  int fsize = sizeof(fixture) / sizeof(fixture[0]);
  struct BinarySearchTree *t =
      malloc((sizeof(struct BinarySearchTree) +
              fsize * sizeof(struct BinarySearchTreeNode)));
  BinarySearchTree_init(t, fixture, fsize);
  printf("%d \n", BinarySearchTree_search(t->root, 10)->data);
  print_node((void *) t->root);
  assert(1);
}

int main() {
  test_stack();
  test_linkedlist();
  test_bst();

  printf("All tests passed successfully!\n");

  return 0;
}

#include "include/binarysearchtree.h"
#include "include/linkedlist.h"
#include "include/linkedlistnode.h"
#include "include/queue.h"
#include "include/stack.h"
#include "include/trie.h"
#include "include/trienode.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void test_bst() {
  BST *bst = createBST();

  int datum[] = {50, 30, 20, 40, 70, 60, 80};
  int fsize = sizeof(datum) / sizeof(datum[0]);

  for (int i = 0; i < fsize; i++) {
    insert(bst, datum[i]);
  }

  BSTTreeNode *result = search(bst, 20);

  assert(result->data == 20);

  removeNode(bst, 20);

  assert(search(bst, 20) == NULL);
  assert(search(bst, 50) != NULL);
  assert(search(bst, 90) == NULL);

  // Perform traversals
  printf("iot: ");
  inorderTraversal(bst->root);
  printf("\n");
  printf("peot: ");
  preorderTraversal(bst->root);
  printf("\n");
  printf("pot: ");
  postorderTraversal(bst->root);
  printf("\n");

  // Destroy the BST
  destroyBST(bst);
  bst = NULL;

  assert((int)!bst);

  bst = initializeBST(datum, fsize);

  assert(search(bst, 155) == NULL);
  assert(search(bst, 60) != NULL);
}

void test_queue() {
  int datum[] = {1, 2, 3, 4, 5};
  int dsize = sizeof(datum) / sizeof(datum[0]);
  struct Queue *q = (Queue *)malloc(sizeof(struct Queue));

  for (int i = 0; i < dsize; i++) {
    printf("%d\n", datum[i]);
    enqueue(q, datum[i]);
  }

  for (int i = 0; i < dsize; i++) {
    assert(datum[i] == dequeue(q));
  }

  assert(sizeof(*q) == 16);
}

void test_trie() {
  char *fixtures[] = {"cat", "cathedral", "bat", "billy"};

  struct Trie *t = Trie_init(fixtures, 4);

  print_trie(t->root);

  assert(1);
}

int main() {
  test_stack();
  test_linkedlist();
  test_bst();
  test_queue();
  test_trie();

  printf("All tests passed successfully!\n");

  return 0;
}

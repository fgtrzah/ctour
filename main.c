#include "include/linkedlist.h"
#include "include/linkedlistnode.h"
#include "include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // start: stack
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

  for (int i = 0; i < sizeof(stack->items) / sizeof(stack->items[0]); ++i) {
    printf("%d\n", stack->items[i]);
  }
  // end: stack
  // start: linked list
  int lcap = sizeof(struct LinkedList) + 2 * sizeof(struct LinkedListNode) +
             sizeof(int);
  struct LinkedList *l = calloc(5, lcap);
  LinkedList_init(l, 2);

  assert(l->head->data == 2);
  assert(LinkedList_search(l, 0).data == 2);

  LinkedList_append(l, 4);

  assert(l->head->next->data == 4);
  // end: linked list

  printf("All tests passed successfully!\n");

  return 0;
}

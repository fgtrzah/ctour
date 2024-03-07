#include "include/stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct Stack *stack = malloc(sizeof(struct Stack));
  init(stack);

  // Test pushing elements
  push(stack, 10);
  assert(peek(stack) == 10);
  push(stack, 20);
  assert(peek(stack) == 20);
  push(stack, 30);
  assert(peek(stack) == 30);

  push(stack, 40);           
  assert(peek(stack) == 40); 
  assert(pop(stack) == 40);
  assert(pop(stack) == 30);
  assert(pop(stack) == 20);
  assert(pop(stack) == 10); 
  assert(pop(stack) == -1); 

  for (int i = 0; i < sizeof(stack->items) / sizeof(stack->items[0]); ++i) {
    printf("%d\n", stack->items[i]);
  }

  printf("All tests passed successfully!\n");

  return 0;
}

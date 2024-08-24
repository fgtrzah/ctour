#include "../include/stack.h"
#include <stdio.h>

void Stack_init(struct Stack *s) { s->top = -1; }

void Stack_push(struct Stack *s, int x) {
  if (s->top < MAX) {
    s->items[++s->top] = x;
  } else {
    printf("overflow\n");
  }
}

int Stack_pop(struct Stack *s) {
  if (s->top > -1) {
    return s->items[s->top--];
  } else {
    printf("underflow\n");
    return -1;
  }
}

int Stack_peek(struct Stack *s) {
  if (s->top > -1) {
    return s->items[s->top];
  } else {
    printf("underflow\n");
    return -1;
  }
}

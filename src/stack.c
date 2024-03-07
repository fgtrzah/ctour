#include <stdio.h>
#include "../include/stack.h"

void init(struct Stack *s) {
  s->top = -1;
}

void push(struct Stack *s, int x) {
  if (s->top < MAX) {
    s->items[++s->top] = x;
  } else {
    printf("overflow\n");
  }
}

int pop(struct Stack *s) {
  if (s->top > -1) {
    return s->items[s->top--];
  } else {
    printf("underflow\n");
    return -1;
  }
}

int peek(struct Stack *s) {
  if (s->top > -1) {
    return s->items[s->top];
  } else {
    printf("underflow\n");
    return -1;
  }
}

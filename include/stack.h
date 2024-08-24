#ifndef STACK_H
#define STACK_H
#define MAX 100

struct Stack {
  int items[MAX];
  int top;
};

void Stack_init(struct Stack *s);
void Stack_push(struct Stack *s, int x);
int Stack_pop(struct Stack *s);
int Stack_peek(struct Stack *s);

#endif

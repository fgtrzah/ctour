#ifndef STACK_H
#define STACK_H
#define MAX 100

struct Stack {
  int items[MAX];
  int top;
};

void init(struct Stack *s);
void push(struct Stack *s, int x);
int pop(struct Stack *s);
int peek(struct Stack *s);

#endif

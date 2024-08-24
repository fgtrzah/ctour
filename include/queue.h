#ifndef QUEUE_H
#define QUEUE_H
#define MAX 100

#include "linkedlistnode.h"

typedef struct Queue {
  struct LinkedListNode *front;
  struct LinkedListNode *back;
} Queue;

void enqueue(Queue *q, int x);
int dequeue(Queue *q);

#endif

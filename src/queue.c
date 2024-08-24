#include "../include/queue.h"
#include <stdlib.h>

void enqueue(Queue *q, int x) {
  struct LinkedListNode *n = (LinkedListNode *)malloc(sizeof(LinkedListNode));
  n->data = x;

  if (!q->back) {
    q->front = n;
    q->back = n;
  } else {
    q->back->next = n;
    q->back = n;
  }
}

int dequeue(Queue *q) {
  if (!q->front)
    return -1;

  int v = q->front->data;
  q->front = q->front->next;

  if (!q->front) {
    q->back = NULL;
  }

  return v;
}

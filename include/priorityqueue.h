#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int element;
} PQElement;

typedef struct {
  int capacity;
  int size;
  PQElement *elements;
} PriorityQueue;

PriorityQueue *PriorityQueue_init(int capacity, int elements[],
                                  int numElements);
int PriorityQueue_full(PriorityQueue *pq);
int PriorityQueue_empty(PriorityQueue *pq);
void PriorityQueue_enqueue(PriorityQueue *pq, int element);
PQElement PriorityQueue_dequeue(PriorityQueue *pq);
PQElement PriorityQueue_peek(PriorityQueue *pq);
void PriorityQueue_flush(PriorityQueue *pq);

#endif // PRIORITY_QUEUE_H

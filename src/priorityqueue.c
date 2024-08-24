#include "../include/priorityqueue.h"

PriorityQueue *PriorityQueue_init(int capacity, int elements[],
                                  int numElements) {
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

  pq->capacity = capacity;
  pq->size = 0;
  pq->elements = (PQElement *)malloc(capacity * sizeof(PQElement));

  for (int i = 0; i < numElements; i++) {
    PriorityQueue_enqueue(pq, elements[i]);
  }
  return pq;
}

int PriorityQueue_full(PriorityQueue *pq) { return pq->size == pq->capacity; }
int PriorityQueue_empty(PriorityQueue *pq) { return pq->size == 0; }

void PriorityQueue_enqueue(PriorityQueue *pq, int element) {
  if (PriorityQueue_full(pq)) {
    printf("Priority Queue is full\n");
    return;
  }
  int i = pq->size - 1;
  while (i >= 0 && pq->elements[i].element > element) {
    pq->elements[i + 1] = pq->elements[i];
    i--;
  }
  pq->elements[i + 1].element = element;
  pq->size++;
}

PQElement PriorityQueue_dequeue(PriorityQueue *pq) {
  if (PriorityQueue_empty(pq)) {
    printf("Priority Queue is empty\n");
    PQElement empty = {-1};
    return empty;
  }
  PQElement highestPriorityElement = pq->elements[0];
  for (int i = 1; i < pq->size; i++) {
    pq->elements[i - 1] = pq->elements[i];
  }
  pq->size--;
  return highestPriorityElement;
}

PQElement PriorityQueue_peek(PriorityQueue *pq) {
  if (PriorityQueue_empty(pq)) {
    printf("Priority Queue is empty\n");
    PQElement empty = {-1};
    return empty;
  }
  return pq->elements[0];
}

void PriorityQueue_flush(PriorityQueue *pq) {
  free(pq->elements);
  free(pq);
}

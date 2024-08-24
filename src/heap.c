#include "../include/heap.h"

Heap *Heap_init(int capacity, int elements[], int numElements) {
  Heap *pq = (Heap *)malloc(sizeof(Heap));

  pq->capacity = capacity;
  pq->size = 0;
  pq->elements = (HeapElement *)malloc(capacity * sizeof(HeapElement));

  for (int i = 0; i < numElements; i++) {
    Heap_enqueue(pq, elements[i]);
  }
  return pq;
}

int Heap_full(Heap *pq) { return pq->size == pq->capacity; }
int Heap_empty(Heap *pq) { return pq->size == 0; }

void Heap_enqueue(Heap *pq, int element) {
  if (Heap_full(pq)) {
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

HeapElement Heap_dequeue(Heap *pq) {
  if (Heap_empty(pq)) {
    printf("Priority Queue is empty\n");
    HeapElement empty = {-1};
    return empty;
  }
  HeapElement highestPriorityElement = pq->elements[0];
  for (int i = 1; i < pq->size; i++) {
    pq->elements[i - 1] = pq->elements[i];
  }
  pq->size--;
  return highestPriorityElement;
}

HeapElement Heap_peek(Heap *pq) {
  if (Heap_empty(pq)) {
    printf("Priority Queue is empty\n");
    HeapElement empty = {-1};
    return empty;
  }
  return pq->elements[0];
}

void Heap_flush(Heap *pq) {
  free(pq->elements);
  free(pq);
}

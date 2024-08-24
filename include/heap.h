#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int element;
} HeapElement;

typedef struct {
  int capacity;
  int size;
  HeapElement *elements;
} Heap;

Heap *Heap_init(int capacity, int elements[], int numElements);
int Heap_full(Heap *pq);
int Heap_empty(Heap *pq);
void Heap_enqueue(Heap *pq, int element);
HeapElement Heap_dequeue(Heap *pq);
HeapElement Heap_peek(Heap *pq);
void Heap_flush(Heap *pq);

#endif // HEAP_H

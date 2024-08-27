#ifndef HEAP_H
#define HEAP_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int element;
} HeapElement;

typedef struct Heap {
  int capacity;
  int size;
  HeapElement *elements;
  int (*comparator)(HeapElement *, HeapElement *, int);
  int priority;
} Heap;

Heap *Heap_init(int capacity, int elements[], int numElements,
                int (*comparator)(HeapElement *, HeapElement *, int),
                int priority);
int Heap_full(Heap *pq);
int Heap_empty(Heap *pq);
void Heap_enqueue(Heap *pq, int element);
HeapElement Heap_dequeue(Heap *pq);
HeapElement Heap_peek(Heap *pq);
void Heap_flush(Heap *pq);
void test_heap(int (*comparator)(HeapElement *, HeapElement *, int),
               int priority);

#endif // HEAP_H

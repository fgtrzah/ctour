#ifndef HEAP_H
#define HEAP_H

#include "index.h"
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum HEType {
  INT,
  FLOAT,
  HEAPELEMENTSTRING,
  HEAPELEMENTVECTOR,
  HEAPELEMENTTUPLE
};

typedef struct {
  enum HEType type;
  union {
    int i;
    float f;
    char *s;
    int *il;
    float *fl;
  } element;
} HeapElement;

typedef struct Heap {
  int capacity;
  int size;
  HeapElement *elements;
  int (*comparator)(HeapElement *, HeapElement *, int);
  int priority;
} Heap;

char *HeapElement_stringify(HeapElement *datum);

Heap *Heap_init(int capacity, int elements[], int numElements,
                int (*comparator)(HeapElement *, HeapElement *, int),
                int priority);
int Heap_full(Heap *pq);
int Heap_empty(Heap *pq);
void Heap_enqueue(Heap *pq, void *element);
HeapElement Heap_dequeue(Heap *pq);
HeapElement Heap_peek(Heap *pq);
void Heap_flush(Heap *pq);
void test_heap();

#endif // HEAP_H

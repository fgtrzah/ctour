#ifndef PQUEUE_H
#define PQUEUE_H

#include "heap.h"

typedef struct Pqueue {
  struct Heap q;
} Pqueue;

bool Pqueue_is_empty(Pqueue *q);
int Pqueue_extract_top(Pqueue *q);
int Pqueue_peek_top(Pqueue *q);
int Pqueue_insert(int x);

#endif

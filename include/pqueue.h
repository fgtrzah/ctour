#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdbool.h>
#include "heap.h"

typedef struct Pqueue {
  int peek;
  int *heap;
} Pqueue;

struct Pqueue *Pqueue_init(int datum[]);
void *Pqueue_heapify(struct Pqueue* heap, int datum[]);
bool Pqueue_is_empty(struct Pqueue *heap);
int Pqueue_extract_top(struct Pqueue *heap);
int Pqueue_peek_top(struct Pqueue *heap);
int Pqueue_insert(int x);
static int Pqueue_left(struct Pqueue *heap);
static int Pqueue_right(struct Pqueue *heap);

#endif

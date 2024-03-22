#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>

struct Pqueue *Pqueue_init(int *datum) {
  struct Pqueue *heap = malloc(sizeof(struct Pqueue));

  return heap;
}


void *Pqueue_heapify(struct Pqueue* heap, int datum[]) {
  if (!datum || !sizeof(&datum))
    return NULL;

  if (!heap) {
    heap = malloc(sizeof(struct Pqueue));
    int h[] = {}; 
    heap->heap = h; 
  }

  size_t n = sizeof(&datum) / sizeof(datum[0]);

  for (size_t i = 0; i < n; i++) {
    printf("%zu\n", i); 
  }

  return NULL;
}

#include "../include/pqueue.h"
#include <stdio.h>
#include <stdlib.h>

struct Pqueue *Pqueue_init(int *datum) {
  struct Pqueue *heap = malloc(sizeof(struct Pqueue));

  return heap;
}


void *Pqueue_heapify(struct Pqueue* heap, int datum[]) {
  /*
   * - find size of heap
   * - for i in list
   *   - does i violate pri?
   *     - if so
   *       - sift up / down
   */
  return NULL;
}

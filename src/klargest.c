#include "../include/klargest.h"
#include "../include/priorityqueue.h"
#include <stdio.h>

int KLargest_getlargest(int datum[], int k, int n) {
  PriorityQueue *pq = PriorityQueue_init(2 * n, datum, n);
  int i = 0;

  while (!PriorityQueue_empty(pq) && i < k) {
    int e = PriorityQueue_dequeue(pq).element;
    printf("dequeue: %d\n", e);
    i++;
  }

  return PriorityQueue_dequeue(pq).element;
}

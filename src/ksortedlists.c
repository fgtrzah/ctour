#include "../include/ksortedlists.h"

#include <stdio.h>

int compare(Member *a, Member *b) { return a->datum - b->datum; }

DynamicPriorityQueue *KSortedLists_ingest(int m, int n, int datum[m][n]) {
  DynamicPriorityQueue *pq =
      DynamicPriorityQueue_create_priority_queue(m * n, MIN_HEAP);

  for (int i = 0; i < m; i++) {
    printf("enqueueing: ");

    for (int j = 0; j < n; j++) {
      printf("%d, ", datum[i][j]);

      DynamicPriorityQueue_insert(pq, datum[i][j]);
      printf("%d, ", DynamicPriorityQueue_peek(pq));
    }

    printf("\n");
  }

  return pq;
}

/*
 * TODO: swap to DynamicPriorityQueue
 */
int *KSortedLists_merge(int m, int n, int datum[m][n], int output[m * n]) {
  // initialize state + heapify
  DynamicPriorityQueue *pq = KSortedLists_ingest(m, n, datum);

  // walk the heap and ingest each dequeued item into res
  int i = 0;
  while (!DynamicPriorityQueue_is_empty(pq)) {
    int e = DynamicPriorityQueue_extract(pq);
    printf("dequeueing: %d\n", e);
    output[i] = e;
    i++;
  }

  return output;
}

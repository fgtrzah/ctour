#ifndef K_SORTED_LISTS_H
#define K_SORTED_LISTS_H

#include "genericdpq.h"
#include "priorityqueue.h"

typedef struct {
  int datum;
  int *current_list;
  int head;
} Member;

DynamicPriorityQueue *KSortedLists_ingest(int m, int n, int datum[m][n]);
int *KSortedLists_merge(int m, int n, int datum[m][n], int output[m * n]);

#endif // !K_SORTED_LISTS_H

#ifndef DYNAMIC_PRIORITY_QUEUE_H
#define DYNAMIC_PRIORITY_QUEUE_H

#include <stdbool.h>

typedef enum { MIN_HEAP, MAX_HEAP } HeapType;

typedef struct {
  int *data;
  int size;
  int capacity;
  HeapType type;
} DynamicPriorityQueue;

DynamicPriorityQueue *DynamicPriorityQueue_create_priority_queue(int capacity,
                                                                 HeapType type);
void DynamicPriorityQueue_destroy_priority_queue(DynamicPriorityQueue *pq);
bool DynamicPriorityQueue_is_empty(DynamicPriorityQueue *pq);
bool DynamicPriorityQueue_insert(DynamicPriorityQueue *pq, int value);
int DynamicPriorityQueue_extract(DynamicPriorityQueue *pq);
int DynamicPriorityQueue_peek(DynamicPriorityQueue *pq);

#endif // DYNAMIC_PRIORITY_QUEUE_H

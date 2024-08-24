#include "../include/dynamicpriorityqueue.h"
#include <stdlib.h>

#define PARENT(i) ((i - 1) / 2)
#define LEFT_CHILD(i) ((2 * i) + 1)
#define RIGHT_CHILD(i) ((2 * i) + 2)

static void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

static void heapify_up(DynamicPriorityQueue *pq, int index) {
  if (index &&
      ((pq->type == MIN_HEAP && pq->data[PARENT(index)] > pq->data[index]) ||
       (pq->type == MAX_HEAP && pq->data[PARENT(index)] < pq->data[index]))) {
    swap(&pq->data[index], &pq->data[PARENT(index)]);
    heapify_up(pq, PARENT(index));
  }
}

static void heapify_down(DynamicPriorityQueue *pq, int index) {
  int left = LEFT_CHILD(index);
  int right = RIGHT_CHILD(index);
  int smallest_or_largest = index;

  if (left < pq->size && ((pq->type == MIN_HEAP &&
                           pq->data[left] < pq->data[smallest_or_largest]) ||
                          (pq->type == MAX_HEAP &&
                           pq->data[left] > pq->data[smallest_or_largest]))) {
    smallest_or_largest = left;
  }

  if (right < pq->size && ((pq->type == MIN_HEAP &&
                            pq->data[right] < pq->data[smallest_or_largest]) ||
                           (pq->type == MAX_HEAP &&
                            pq->data[right] > pq->data[smallest_or_largest]))) {
    smallest_or_largest = right;
  }

  if (smallest_or_largest != index) {
    swap(&pq->data[index], &pq->data[smallest_or_largest]);
    heapify_down(pq, smallest_or_largest);
  }
}

DynamicPriorityQueue *
DynamicPriorityQueue_create_priority_queue(int capacity, HeapType type) {
  DynamicPriorityQueue *pq =
      (DynamicPriorityQueue *)malloc(sizeof(DynamicPriorityQueue));
  pq->data = (int *)malloc(capacity * sizeof(int));
  pq->size = 0;
  pq->capacity = capacity;
  pq->type = type;
  return pq;
}

void DynamicPriorityQueue_destroy_priority_queue(DynamicPriorityQueue *pq) {
  free(pq->data);
  free(pq);
}

bool DynamicPriorityQueue_is_empty(DynamicPriorityQueue *pq) {
  return pq->size == 0;
}

bool DynamicPriorityQueue_insert(DynamicPriorityQueue *pq, int value) {
  if (pq->size == pq->capacity) {
    return false; // Priority queue is full
  }

  pq->data[pq->size] = value;
  heapify_up(pq, pq->size);
  pq->size++;
  return true;
}

int DynamicPriorityQueue_extract(DynamicPriorityQueue *pq) {
  if (DynamicPriorityQueue_is_empty(pq)) {
    return -1; // Priority queue is empty
  }

  int root = pq->data[0];
  pq->data[0] = pq->data[--pq->size];
  heapify_down(pq, 0);

  return root;
}

int DynamicPriorityQueue_peek(DynamicPriorityQueue *pq) {
  if (DynamicPriorityQueue_is_empty(pq)) {
    return -1; // Priority queue is empty
  }
  return pq->data[0];
}

#include "../include/heap.h"

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

Heap *Heap_init(int capacity, int elements[], int numElements,
                int (*comparator)(HeapElement *, HeapElement *, int),
                int priority) {
  Heap *pq = (Heap *)malloc(sizeof(Heap));

  pq->capacity = capacity;
  pq->size = 0;
  pq->elements = (HeapElement *)malloc(capacity * sizeof(HeapElement));
  pq->comparator = comparator;
  pq->priority = priority;

  for (int i = 0; i < numElements; i++) {
    Heap_enqueue(pq, elements[i]);
  }

  printf("heap comparator: \n");

  int cres = pq->comparator(&pq->elements[0], &pq->elements[1], priority);

  printf("%d\n", cres);

  return pq;
}

int Heap_full(Heap *pq) { return pq->size == pq->capacity; }
int Heap_empty(Heap *pq) { return pq->size == 0; }

void Heap_enqueue(Heap *pq, int element) {
  if (Heap_full(pq)) {
    printf("Priority Queue is full\n");
    return;
  }
  int i = pq->size - 1;
  while (i >= 0 && pq->comparator(&pq->elements[i], &(HeapElement){element},
                                  pq->priority)) {
    pq->elements[i + 1] = pq->elements[i];
    i--;
  }
  pq->elements[i + 1].element = element;
  pq->size++;
}

HeapElement Heap_dequeue(Heap *pq) {
  if (Heap_empty(pq)) {
    printf("Priority Queue is empty\n");
    HeapElement empty = {-1};
    return empty;
  }

  HeapElement highest_priority_element = pq->elements[0];

  for (int i = 1; i < pq->size; i++) {
    pq->elements[i - 1] = pq->elements[i];
  }

  pq->size--;
  return highest_priority_element;
}
HeapElement Heap_peek(Heap *pq) {
  if (Heap_empty(pq)) {
    printf("Priority Queue is empty\n");
    HeapElement empty = {-1};
    return empty;
  }
  return pq->elements[0];
}

void Heap_flush(Heap *pq) {
  free(pq->elements);
  free(pq);
}

// Heap Comparator Function
int heap_comparator(HeapElement *a, HeapElement *b, int priority) {
  if (priority == 0) {
    return (a->element > b->element);
  } else {
    return (a->element < b->element);
  }
}

// Test Case 1: Heap Initialization with Ascending Order
void test_heap_initialization_ascending(int (*comparator)(HeapElement *,
                                                          HeapElement *, int),
                                        int priority) {
  int elements[] = {1, 2, 3, 4, 5};
  Heap *h = Heap_init(10, elements, 5, comparator, priority);
  assert(h->size == 5);
  assert(h->elements[0].element == 1);
  Heap_flush(h);
}

// Test Case 2: Heap Initialization with Descending Order
void test_heap_initialization_descending(int (*comparator)(HeapElement *,
                                                           HeapElement *, int),
                                         int priority) {
  int elements[] = {5, 4, 3, 2, 1};
  Heap *h = Heap_init(10, elements, 5, comparator, priority);
  assert(h->size == 5);
  assert(h->elements[0].element == 5);
  Heap_flush(h);
}

// Test Case 3: Enqueue Element into Heap
void test_heap_enqueue(int (*comparator)(HeapElement *, HeapElement *, int),
                       int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(10, elements, 2, comparator, priority);
  Heap_enqueue(h, 15);
  assert(h->size == 3);
  assert(h->elements[1].element == 15);
  Heap_flush(h);
}

// Test Case 4: Dequeue Element from Heap
void test_heap_dequeue(int (*comparator)(HeapElement *, HeapElement *, int),
                       int priority) {
  int elements[] = {10, 20, 30};
  Heap *h = Heap_init(10, elements, 3, comparator, priority);
  HeapElement e = Heap_dequeue(h);
  assert(e.element == 10);
  assert(h->size == 2);
  assert(h->elements[0].element == 20);
  Heap_flush(h);
}

// Test Case 5: Peek at Heap's Top Element
void test_heap_peek(int (*comparator)(HeapElement *, HeapElement *, int),
                    int priority) {
  int elements[] = {50, 30, 20};
  Heap *h = Heap_init(10, elements, 3, comparator, priority);
  HeapElement e = Heap_peek(h);
  assert(e.element == 20);
  assert(h->size == 3);
  Heap_flush(h);
}

// Test Case 6: Check If Heap is Full
void test_heap_full(int (*comparator)(HeapElement *, HeapElement *, int),
                    int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(2, elements, 2, comparator, priority);
  assert(Heap_full(h) == 1);
  Heap_flush(h);
}

// Test Case 7: Check If Heap is Empty
void test_heap_empty(int (*comparator)(HeapElement *, HeapElement *, int),
                     int priority) {
  int elements[] = {};
  Heap *h = Heap_init(10, elements, 0, comparator, priority);
  assert(Heap_empty(h) == 1);
  Heap_flush(h);
}

// Test Case 8: Enqueue to Full Heap
void test_heap_enqueue_full(int (*comparator)(HeapElement *, HeapElement *,
                                              int),
                            int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(2, elements, 2, comparator, priority);
  Heap_enqueue(h, 30);
  assert(h->size == 2); // Should not change
  Heap_flush(h);
}

// Test Case 9: Dequeue from Empty Heap
void test_heap_dequeue_empty(int (*comparator)(HeapElement *, HeapElement *,
                                               int),
                             int priority) {
  int elements[] = {};
  Heap *h = Heap_init(10, elements, 0, comparator, priority);
  HeapElement e = Heap_dequeue(h);
  assert(e.element == -1); // Should return an empty element
  Heap_flush(h);
}

// Test Case 10: Enqueue and Dequeue
void test_heap_enqueue_dequeue(int (*comparator)(HeapElement *, HeapElement *,
                                                 int),
                               int priority) {
  int elements[] = {5};
  Heap *h = Heap_init(10, elements, 1, comparator, priority);
  Heap_enqueue(h, 3);
  assert(h->size == 2);
  HeapElement e = Heap_dequeue(h);
  assert(e.element == 3);
  assert(h->size == 1);
  Heap_flush(h);
}

void test_heap_top3(int (*comparator)(HeapElement *, HeapElement *, int)) {
  int elements[] = {10, 20, 5, 30, 15};
  int n = sizeof(elements) / sizeof(elements[0]);
  Heap *h = Heap_init(2 * n, elements, n, heap_comparator, 0);
  int i = 0;
  int expected[] = {5, 10, 15};

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    printf("exp, acc: %d, %d\n", e.element, expected[i]);
    assert(e.element == expected[i]);
    i++;
  }

  int fixtures[] = {3, 1, 2, 10, 33, 100, 20};
  int exp_2[] = {1, 2, 3};
  i = 0;
  h = Heap_init(2 * 7, fixtures, 7, heap_comparator, 0);

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    printf("exp, acc: %d, %d\n", e.element, exp_2[i]);
    assert(e.element == exp_2[i]);
    i++;
  }

  i = 0;
  h = Heap_init(2 * 7, fixtures, 7, heap_comparator, 0);
  int exp3[] = {100, 33, 20};

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    printf("exp, acc: %d, %d\n", e.element, exp_2[i]);
    assert(e.element == exp_2[i]);
    i++;
  }
}

void test_heap(int (*comparator)(HeapElement *, HeapElement *, int),
               int priority) {
  test_heap_initialization_ascending(comparator, 0);
  test_heap_initialization_descending(comparator, 1);
  test_heap_enqueue(comparator, 0);
  test_heap_dequeue(comparator, 0);
  test_heap_peek(comparator, 0);
  test_heap_full(comparator, 0);
  test_heap_empty(comparator, 0);
  test_heap_enqueue_full(comparator, 0);
  test_heap_dequeue_empty(comparator, 0);
  test_heap_enqueue_dequeue(comparator, 0);
  test_heap_top3(comparator);
}

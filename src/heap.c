#include "../include/heap.h"

char *HeapElement_stringify(HeapElement *datum) {
  static char result[256];

  if (datum == NULL) {
    snprintf(result, sizeof(result), "HeapElement(NULL)");
    return result;
  }
  result[0] = '\0';
  STRINGIFY_HEAPELEMENT(result, sizeof(result), datum);

  return result;
}

Heap *Heap_init(int capacity, int elements[], int numElements,
                int (*comparator)(HeapElement *, HeapElement *, int),
                int priority) {
  Heap *pq = (Heap *)malloc(sizeof(Heap));
  if (pq == NULL) {
    perror("Failed to allocate memory for heap");
    exit(EXIT_FAILURE);
  }

  pq->capacity = capacity;
  pq->size = 0;
  pq->elements = (HeapElement *)malloc(capacity * sizeof(HeapElement));
  if (pq->elements == NULL) {
    perror("Failed to allocate memory for heap elements");
    free(pq);
    exit(EXIT_FAILURE);
  }

  pq->comparator = comparator;
  pq->priority = priority;

  for (int i = 0; i < numElements; i++) {
    HeapElement e;
    e.type = INT;
    e.element.i = elements[i];
    Heap_enqueue(pq, &e);
  }

  return pq;
}

int Heap_full(Heap *pq) { return pq->size >= pq->capacity; }
int Heap_empty(Heap *pq) { return pq->size == 0; }

void Heap_enqueue(Heap *pq, void *element) {
  if (pq == NULL || element == NULL) {
    printf("Invalid input to Heap_enqueue\n");
    return;
  }

  if (Heap_full(pq)) {
    // Double the capacity to make room for more elements
    pq->capacity *= 2;
    pq->elements = (HeapElement *)realloc(pq->elements,
                                          pq->capacity * sizeof(HeapElement));
    if (pq->elements == NULL) {
      perror("Failed to reallocate memory for heap elements");
      exit(EXIT_FAILURE);
    }
  }

  int i = pq->size - 1;
  while (i >= 0 && pq->comparator(&pq->elements[i], (HeapElement *)element,
                                  pq->priority)) {
    pq->elements[i + 1] = pq->elements[i];
    i--;
  }

  pq->elements[i + 1] = *(HeapElement *)element;
  pq->size += 1;
}

HeapElement Heap_dequeue(Heap *pq) {
  if (Heap_empty(pq)) {
    printf("Priority Queue is empty\n");
    HeapElement empty = {INT, .element.i = -1};
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
    HeapElement empty = {INT, .element.i = -1};
    return empty;
  }
  return pq->elements[0];
}

void Heap_flush(Heap *pq) {
  if (pq != NULL) {
    free(pq->elements);
    free(pq);
  }
}

int heap_comparator(HeapElement *a, HeapElement *b, int priority) {
  if (priority == 0) {
    return (a->element.i > b->element.i);
  } else {
    return (a->element.i < b->element.i);
  }
}

void test_heap_initialization_descending(int (*comparator)(HeapElement *,
                                                           HeapElement *, int),
                                         int priority) {
  int elements[] = {1, 2, 3, 4, 5};
  Heap *h = Heap_init(5, elements, 5, comparator, priority);
  assert(h->size == 5);
  assert(h->elements[0].element.i == 5);
  assert(h->elements[4].element.i == 1);
  Heap_flush(h);
}

void test_heap_initialization_ascending(int (*comparator)(HeapElement *,
                                                          HeapElement *, int),
                                        int priority) {
  int elements[] = {5, 4, 3, 2, 1};
  Heap *h = Heap_init(5, elements, 5, comparator, priority);
  assert(h->size == 5);
  assert(h->elements[0].element.i == 1);
  assert(h->elements[4].element.i == 5);
  Heap_flush(h);
}

void test_heap_enqueue(int (*comparator)(HeapElement *, HeapElement *, int),
                       int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(2, elements, 2, comparator, priority);
  int new_element = 15;
  Heap_enqueue(h, &new_element);
  assert(h->size == 3);
  assert(Heap_peek(h).element.i == 10);
  Heap_flush(h);
}

int Heap_base_comparator(HeapElement *a, HeapElement *b, int priority) {
  if (!a || !b) {
    printf("either a or b in comparator missing\n");
    return 0;
  }

  char *a_str = HeapElement_stringify(a);
  char *b_str = HeapElement_stringify(b);

  printf("Comparing A: %s with B: %s\n", a_str, b_str);

  if (priority == 0) {
    return (a->element.i > b->element.i);
  } else {
    return (a->element.i < b->element.i);
  }
}
void test_heap_dequeue(int (*comparator)(HeapElement *, HeapElement *, int),
                       int priority) {
  int elements[] = {10, 20, 30};
  Heap *h = Heap_init(3, elements, 3, comparator, priority);

  HeapElement e = Heap_dequeue(h);
  assert(e.element.i == 10);
  assert(h->size == 2);
  assert(h->elements[0].element.i == 20);

  e = Heap_dequeue(h);
  assert(e.element.i == 20);
  assert(h->size == 1);
  assert(h->elements[0].element.i == 30);

  e = Heap_dequeue(h);
  assert(e.element.i == 30);
  assert(h->size == 0);

  Heap_flush(h);
}

void test_heap_peek(int (*comparator)(HeapElement *, HeapElement *, int),
                    int priority) {
  int elements[] = {50, 30, 20};
  Heap *h = Heap_init(3, elements, 3, comparator, priority);

  HeapElement e = Heap_peek(h);
  assert(e.element.i == 20); // Since it should be a min-heap
  assert(h->size == 3);      // Size shouldn't change

  Heap_flush(h);
}

void test_heap_full(int (*comparator)(HeapElement *, HeapElement *, int),
                    int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(2, elements, 2, comparator, priority);
  assert(Heap_full(h) == 1);

  // Enqueue should expand the heap
  int new_element = 30;
  Heap_enqueue(h, &new_element);
  assert(h->size == 3);
  assert(h->capacity == 4);  // Ensure capacity was doubled
  assert(Heap_full(h) == 0); // Heap should no longer be full after expansion

  Heap_flush(h);
}

void test_heap_empty(int (*comparator)(HeapElement *, HeapElement *, int),
                     int priority) {
  int elements[] = {};
  Heap *h = Heap_init(10, elements, 0, comparator, priority);
  assert(Heap_empty(h) == 1);

  int new_element = 10;
  Heap_enqueue(h, &new_element);
  assert(Heap_empty(h) == 0); // Now the heap should not be empty

  Heap_flush(h);
}

void test_heap_enqueue_full(int (*comparator)(HeapElement *, HeapElement *,
                                              int),
                            int priority) {
  int elements[] = {10, 20};
  Heap *h = Heap_init(2, elements, 2, comparator, priority);

  int new_element = 30;
  Heap_enqueue(h, &new_element);
  assert(h->size == 3);
  assert(h->capacity >= 3); // Ensure capacity was increased

  // Verify the order after expansion
  assert(Heap_peek(h).element.i == 10);
  assert(Heap_dequeue(h).element.i == 10);
  assert(Heap_dequeue(h).element.i == 20);

  Heap_flush(h);
}

void test_heap_dequeue_empty(int (*comparator)(HeapElement *, HeapElement *,
                                               int),
                             int priority) {
  int elements[] = {};
  Heap *h = Heap_init(10, elements, 0, comparator, priority);

  HeapElement e = Heap_dequeue(h);
  assert(e.element.i == -1); // Should return an empty element
  assert(Heap_empty(h) == 1);

  Heap_flush(h);
}

void test_heap_enqueue_dequeue(int (*comparator)(HeapElement *, HeapElement *,
                                                 int),
                               int priority) {
  int elements[] = {5};
  Heap *h = Heap_init(1, elements, 1, comparator, priority);

  int new_element = 3;
  Heap_enqueue(h, &new_element);
  assert(h->size == 2);
  assert(Heap_peek(h).element.i == 3); // 3 should be at the root

  HeapElement e = Heap_dequeue(h);
  assert(e.element.i == 3);
  assert(h->size == 1);
  assert(h->elements[0].element.i == 5); // 5 should be the only element left

  Heap_flush(h);
}

void test_heap_top3(int (*comparator)(HeapElement *, HeapElement *, int)) {
  int elements[] = {10, 20, 5, 30, 15};
  int n = sizeof(elements) / sizeof(elements[0]);
  Heap *h = Heap_init(2 * n, elements, n, comparator, 0);
  int i = 0;
  int expected[] = {5, 10, 15};

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    assert(e.element.i == expected[i]);
    i++;
  }

  int fixtures[] = {3, 1, 2, 10, 33, 100, 20};
  int exp_2[] = {1, 2, 3};
  i = 0;
  h = Heap_init(2 * 7, fixtures, 7, comparator, 0);

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    assert(e.element.i == exp_2[i]);
    i++;
  }

  i = 0;
  h = Heap_init(2 * 7, fixtures, 7, comparator, 0);
  int exp3[] = {100, 33, 20};

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    assert(e.element.i == exp3[i]);
    i++;
  }

  Heap_flush(h);
}

void test_heap() {
  test_heap_initialization_ascending(Heap_base_comparator, 0);
  test_heap_initialization_descending(Heap_base_comparator, 1);
  test_heap_enqueue(Heap_base_comparator, 0);
  test_heap_dequeue(Heap_base_comparator, 0);
  test_heap_peek(Heap_base_comparator, 0);
  test_heap_full(Heap_base_comparator, 0);
  test_heap_empty(Heap_base_comparator, 0);
  test_heap_enqueue_full(Heap_base_comparator, 0);
  test_heap_dequeue_empty(Heap_base_comparator, 0);
  // test_heap_enqueue_dequeue(Heap_base_comparator, 1);
  // test_heap_top3(Heap_base_comparator);
}

#ifndef HEAP_H
#define HEAP_H

#include "index.h"
#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum HEType {
  INT,
  FLOAT,
  HEAPELEMENTSTRING,
  HEAPELEMENTVECTOR,
  HEAPELEMENTTUPLE
};

typedef struct {
  enum HEType type;
  union {
    int i;
    float f;
    char *s;
    int *il;
    float *fl;
  } element;
} HeapElement;

typedef struct Heap {
  int capacity;
  int size;
  HeapElement *elements;
  int (*comparator)(HeapElement *, HeapElement *, int);
  int priority;
} Heap;
// Helper macros for stringifying different types
#define STRINGIFY_INT(buffer, size, value) snprintf(buffer, size, "%d", value)
#define STRINGIFY_FLOAT(buffer, size, value)                                   \
  snprintf(buffer, size, "%.2f", value)
#define STRINGIFY_STRING(buffer, size, value)                                  \
  snprintf(buffer, size, "%s", value ? value : "(null)")
#define STRINGIFY_VECTOR(buffer, size, value, length)                          \
  do {                                                                         \
    int offset = 0;                                                            \
    offset += snprintf(buffer + offset, size - offset, "[");                   \
    for (int i = 0; i < length; i++) {                                         \
      offset += snprintf(buffer + offset, size - offset, "%d%s", value[i],     \
                         (i < length - 1) ? ", " : "");                        \
    }                                                                          \
    snprintf(buffer + offset, size - offset, "]");                             \
  } while (0)
#define STRINGIFY_TUPLE(buffer, size, value, length)                           \
  do {                                                                         \
    int offset = 0;                                                            \
    offset += snprintf(buffer + offset, size - offset, "(");                   \
    for (int i = 0; i < length; i++) {                                         \
      offset += snprintf(buffer + offset, size - offset, "%.2f%s", value[i],   \
                         (i < length - 1) ? ", " : "");                        \
    }                                                                          \
    snprintf(buffer + offset, size - offset, ")");                             \
  } while (0)

// General-purpose macro to stringify a field based on its type

// Macro to handle the stringification of the entire structure
#define STRINGIFY_HEAPELEMENT(result, size, element)                           \
  do {                                                                         \
    char temp[256];                                                            \
    int offset = 0;                                                            \
    STRINGIFY_FIELD(temp, sizeof(temp), element.type, element.element,         \
                    3); /* Adjust length as needed */                          \
    offset += snprintf(result + offset, size - offset, "%s", temp);            \
  } while (0)

// Function prototypes
char *HeapElement_stringify(HeapElement *datum);

Heap *Heap_init(int capacity, int elements[], int numElements,
                int (*comparator)(HeapElement *, HeapElement *, int),
                int priority);
int Heap_full(Heap *pq);
int Heap_empty(Heap *pq);
void Heap_enqueue(Heap *pq, void *element);
HeapElement Heap_dequeue(Heap *pq);
HeapElement Heap_peek(Heap *pq);
void Heap_flush(Heap *pq);
void test_heap();

#endif // HEAP_H

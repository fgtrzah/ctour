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

// Example of how you might define the other macros (provided earlier in the
// header)
#define STRINGIFY_FIELD(buffer, size, type, element, length)                   \
  do {                                                                         \
    switch (type) {                                                            \
    case INT:                                                                  \
      STRINGIFY_INT(buffer, size, element.i);                                  \
      break;                                                                   \
    case FLOAT:                                                                \
      STRINGIFY_FLOAT(buffer, size, element.f);                                \
      break;                                                                   \
    case HEAPELEMENTSTRING:                                                    \
      if (element.s) {                                                         \
        STRINGIFY_STRING(buffer, size, element.s);                             \
      } else {                                                                 \
        snprintf(buffer, size, "empty string");                                \
      }                                                                        \
      break;                                                                   \
    case HEAPELEMENTVECTOR:                                                    \
      if (element.il) {                                                        \
        STRINGIFY_VECTOR(buffer, size, element.il, length);                    \
      } else {                                                                 \
        snprintf(buffer, size, "empty vector");                                \
      }                                                                        \
      break;                                                                   \
    case HEAPELEMENTTUPLE:                                                     \
      if (element.fl) {                                                        \
        STRINGIFY_TUPLE(buffer, size, element.fl, length);                     \
      } else {                                                                 \
        snprintf(buffer, size, "empty tuple");                                 \
      }                                                                        \
      break;                                                                   \
    default:                                                                   \
      snprintf(buffer, size, "empty element - nothing to stringify");          \
      break;                                                                   \
    }                                                                          \
  } while (0)

#define STRINGIFY_HEAPELEMENT(result, size, datum)                             \
  do {                                                                         \
    if (datum == NULL) {                                                       \
      snprintf(result, size, "HeapElement(NULL)");                             \
    } else {                                                                   \
      char temp[size];                                                         \
      STRINGIFY_FIELD(temp, size, datum->type, datum->element, 3);             \
      snprintf(result, size, "HeapElement(%s)", temp);                         \
    }                                                                          \
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

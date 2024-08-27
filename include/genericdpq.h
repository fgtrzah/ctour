#ifndef GENERIC_DPQ_H
#define GENERIC_DPQ_H

#include <stddef.h> // For size_t

#include "dynamicpriorityqueue.h"

typedef int (*GDPQComparator)(void *,
                              void *); // Function pointer for comparison

typedef struct {
  void **data;            // Array of generic data pointers
  size_t size;            // Current number of elements in the queue
  size_t capacity;        // Maximum capacity of the queue
  GDPQComparator compare; // Function pointer to compare elements
  HeapType type;          // Type of heap (MIN_HEAP or MAX_HEAP)
} GenericDPQ;

// Function prototypes
GenericDPQ *GenericDPQ_pq_create(size_t capacity, GDPQComparator compare,
                                 HeapType type);
void GenericDPQ_pq_destroy(GenericDPQ *pq);
void GenericDPQ_pq_insert(GenericDPQ *pq, void *item);
int *GenericDPQ_pq_extract(GenericDPQ *pq);
int GenericDPQ_pq_is_empty(GenericDPQ *pq);
size_t GenericDPQ_pq_size(GenericDPQ *pq);

#endif // !GENERIC_DPQ_H

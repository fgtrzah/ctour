#include "../include/genericdpq.h"

GenericDPQ *GenericDPQ_pq_create(size_t capacity, GDPQComparator compare,
                                 HeapType type) {
  GenericDPQ *pq;
  return pq;
}
void GenericDPQ_pq_destroy(GenericDPQ *pq) {}
void GenericDPQ_pq_insert(GenericDPQ *pq, void *item) {}
int *GenericDPQ_pq_extract(GenericDPQ *pq) { return 0; }
int GenericDPQ_pq_is_empty(GenericDPQ *pq) { return 0; }
size_t GenericDPQ_pq_size(GenericDPQ *pq) { return pq->size; }

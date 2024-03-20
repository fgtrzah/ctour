#ifndef HEAP_H 
#define HEAP_H
#define SEED 20

typedef struct Heap {
  int *q[SEED];  
  int max;
  int mix;
  int order;
} Heap;

int get_max(Heap *h);
int get_min(Heap *h);

#endif

#include "../include/dynamicvector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const int StartSize = 1;      /* initial vector size */
static const float GrowthRate = 1.5; /* geometric growth of vector capacity */
static int *datum = NULL;            /* pointer to vector elements */
static int vectorsize = 0;           /* current size of vector */
static int capacity = 0;             /* current reserved memory for vector */

DynamicVector *DynamicVector_init() {
  DynamicVector *v = (DynamicVector *)malloc(sizeof(DynamicVector));
  v->start_size = StartSize;
  v->growth_rate = GrowthRate;
  v->datum = datum;
  v->size = 0;
  v->capacity = 0;
  return v;
}

int DynamicVector_push_back(DynamicVector *v, int datum) {
  int newsize;
  int *p = (int *)malloc(sizeof(int));

  if (v->size == v->capacity) {
    newsize = (v->capacity == 0) ? v->start_size
                                 : (int)(v->capacity * v->growth_rate + 1.0);
    p = (int *)realloc(v->datum, newsize * sizeof(int));

    if (p == NULL)
      return -1;
  }

  v->capacity = newsize;
  v->datum = p;
  v->datum[v->size] = datum;

  return v->size++;
}
int DynamicVector_pop_back(DynamicVector *v) {
  assert(v->size > 0);
  return v->datum[--v->size];
}

int *DynamicVector_get_element(DynamicVector *v, int index) {
  assert(index >= 0 && v->size > index);
  return v->datum + index;
}

int DynamicVector_get_size(DynamicVector *v) { return v->size; }

int DynamicVector_set_size(DynamicVector *v, int size) {
  if (size > v->capacity) {
    int *p = (int *)realloc(v->datum, size * sizeof(int));

    if (p == NULL)
      return -1;

    v->capacity = size;
    v->datum = p;
  }

  v->size = size;
  return 0;
}

int DynamicVector_get_capacity(DynamicVector *v) { return v->capacity; }

int DynamicVector_set_capacity(DynamicVector *v, int capacity) {
  if (capacity != v->capacity) {
    int *p = (int *)realloc(v->datum, capacity * sizeof(int));

    if (p == NULL && capacity > 0)
      return -1;

    v->capacity = capacity;
    v->datum = p;
  }

  if (capacity < v->size)
    v->size = capacity;

  return 0;
}

#ifndef DYNAMICVECTOR_H
#define DYNAMICVECTOR_H

typedef struct {
  int start_size;
  float growth_rate;
  int *datum;
  int size;
  int capacity;
} DynamicVector;

DynamicVector *DynamicVector_init();
int DynamicVector_push_back(DynamicVector *v, int datum);
int DynamicVector_pop_back(DynamicVector *v);
int *DynamicVector_get_element(DynamicVector *v, int index);
int DynamicVector_get_size(DynamicVector *v);
int DynamicVector_set_size(DynamicVector *v, int size);
int DynamicVector_get_capacity(DynamicVector *v);
int DynamicVector_set_capacity(DynamicVector *v, int capacity);

#endif // !DYNAMICVECTOR_H

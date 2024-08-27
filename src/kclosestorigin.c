#include "../include/kclosestorigin.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

CoordList *KClosestOrigin_pluckClosest(CoordList *datum, int n, int k) {
  CoordList *closest = (CoordList *)malloc(sizeof(CoordList));
  return closest;
}

double KClosestOrigin_distance(Coordinate o) {
  return sqrt(o.x * o.x + o.y * o.y);
}

CoordList *KClosestOrigin_init(int capacity) {
  CoordList *datum = (CoordList *)malloc(sizeof(CoordList));
  datum->points = (Coordinate *)malloc(capacity * sizeof(Coordinate));
  datum->size = 0;
  datum->capacity = capacity;
  return datum;
}

void KClosestOrigin_swapCoords(Coordinate a, Coordinate b) {
  Coordinate temp = a;
  a = b;
  b = temp;
}

void KClosestOrigin_siftUp(CoordList *datum, int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;

    if (KClosestOrigin_distance(datum->points[index]) <
        KClosestOrigin_distance(datum->points[parent])) {
      KClosestOrigin_swapCoords(datum->points[index], datum->points[parent]);
      index = parent;
    } else {
      break;
    }
  }
}

void KClosestOrigin_siftDown(CoordList *datum, int i) {
  int l, r, min;

  while (1) {
    l = 2 * i + 1;
    r = 2 * i + 2;
    min = i;

    if (l < datum->size && KClosestOrigin_distance(datum->points[l]) <
                               KClosestOrigin_distance(datum->points[min])) {
      min = l;
    }
    if (r < datum->size && KClosestOrigin_distance(datum->points[r]) <
                               KClosestOrigin_distance(datum->points[min])) {
      min = r;
    }
    if (min == i)
      break;

    KClosestOrigin_swapCoords(datum->points[i], datum->points[min]);
    i = min;
  }
}

void KClosestOrigin_enqueue(CoordList *datum, Coordinate o) {
  if (datum->size == datum->capacity) {
    printf("datum is full.\n");
    return;
  }
  datum->points[datum->size] = o;
  datum->size++;
  KClosestOrigin_siftUp(datum, datum->size - 1);
}

Coordinate KClosestOrigin_dequeue(CoordList *datum) {
  if (!datum->size) {
    printf("heap is empty \n");
    exit(EXIT_FAILURE);
  }

  Coordinate min = datum->points[0];
  datum->points[0] = datum->points[datum->size - 1];
  datum->size--;
  KClosestOrigin_siftDown(datum, 0);
  return min;
}

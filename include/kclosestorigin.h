#ifndef K_CLOSEST_ORIGIN_H
#define K_CLOSEST_ORIGIN_H

typedef struct {
  int x;
  int y;
} Coordinate;

typedef struct {
  Coordinate *points;
  int size;
  int capacity;
} CoordList;

CoordList *KClosestOrigin_pluckClosest(CoordList *datum, int n, int k);
double KClosestOrigin_distance(Coordinate o);
CoordList *KClosestOrigin_init(int capacity);
void KClosestOrigin_swapCoords(Coordinate a, Coordinate b);
void KClosestOrigin_siftUp(CoordList *datum, int i);
void KClosestOrigin_siftDown(CoordList *datum, int i);
void KClosestOrigin_enqueue(CoordList *datum, Coordinate o);
Coordinate KClosestOrigin_dequeue(CoordList *datum);
#endif // !K_CLOSEST_ORIGIN_H

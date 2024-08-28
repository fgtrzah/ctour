/*
 * TODO: refactor to utilize https://en.wikipedia.org/wiki/Pairing_function
 * instead of full rewrite and extranous typedefs/inheritence-ish structure
 */
#include "../include/meetingrooms.h"
#include "../include/index.h"

int comparator(HeapElement *a, HeapElement *b, int priority) { return 0; }

Scheduler *MeetingRooms_orchestrate(int **datum, size_t n) {
  n = !n ? size_datum(datum, n) : n;

  Scheduler *scheduler = (void *)malloc(sizeof(void));
  Heap *h = Heap_init(2 * n, *datum, 5, comparator, 0);
  scheduler->orchestration = h;
  return scheduler;
}

int MeetingRooms_min_rooms(int **datum, size_t n) { return 0; }

/*
 * TODO: refactor to utilize https://en.wikipedia.org/wiki/Pairing_function
 * instead of full rewrite and extranous typedefs/inheritence-ish structure
 */
#include "../include/meetingrooms.h"
#include "../include/index.h"
#include <stdio.h>

int comparator(HeapElement *a, HeapElement *b, int priority) { return 0; }

Scheduler *MeetingRooms_orchestrate(int **datum, size_t n) {
  n = !n ? size_datum(datum, n) : n;

  Scheduler *scheduler = (void *)malloc(sizeof(void));
  Heap *h = Heap_init(2 * n, *datum, 5, comparator, 0);

  if (!h) {
    fprintf(stderr, "Unable to allocate heap memory for scheduler\n");
    assert(!1);
  } else {
    printf("Allocated %zu bytes for scheduler\n", sizeof(*h));
  }

  scheduler->orchestration = h;
  return scheduler;
}

int MeetingRooms_min_rooms(int **datum, size_t n) { return 0; }

void test_meetingrooms() { assert(1); }

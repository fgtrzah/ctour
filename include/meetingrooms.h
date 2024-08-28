#ifndef MEETINGROOMS_H
#define MEETINGROOMS_H

#include "assert.h"
#include "heap.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
  int **rooms;
  Heap *orchestration;
} Scheduler;

Scheduler *MeetingRooms_orchestrate(int **datum, size_t n);
int MeetingRooms_min_rooms(int **datum, size_t n);

#endif // !MEETINGROOMS_H

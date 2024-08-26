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

Scheduler *MeetingRooms_orchestrate(int **datum);
int MeetingRooms_min_rooms(int **datum);

#endif // !MEETINGROOMS_H

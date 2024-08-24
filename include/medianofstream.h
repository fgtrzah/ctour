#ifndef MEDIAN_OF_STREAM_H
#define MEDIAN_OF_STREAM_H

#include <math.h>
#include <stdlib.h>

typedef struct {
  double *datum;
  size_t size;
  size_t capacity;
  double aggregate;
  double median;
} StreamMetaData;

StreamMetaData *MedianOfStream_init(size_t capacity);

double MedianOfStream_compute_med(StreamMetaData *s);

void MedianOfStream_add(StreamMetaData *s, double datum);

double_t MedianOfStream_median(StreamMetaData *s);

#endif // !MEDIAN_OF_STREAM_H

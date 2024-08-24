#include "../include/medianofstream.h"
#include "../include/colorize.h"
#include <stdio.h>
#include <stdlib.h>

StreamMetaData *MedianOfStream_init(size_t capacity) {
  StreamMetaData *s = (StreamMetaData *)malloc(sizeof(StreamMetaData));
  s->datum = (double *)malloc(sizeof(double) * capacity);
  s->size = 0;
  s->capacity = capacity;
  s->aggregate = 0;
  s->median = 0;
  return s;
}

double MedianOfStream_compute_med(StreamMetaData *s) {
  return (s->aggregate / s->size) * 10 / 10.0;
}

void MedianOfStream_add(StreamMetaData *s, double datum) {
  if (s->capacity <= s->size) {
    s->capacity *= 2;
    double *ndatum = (double *)realloc(s->datum, s->capacity * sizeof(double));

    if (ndatum == NULL) {
      colorize("failed to expand stream capacity\n", COLOR_RED);
    }

    s->datum = ndatum;
  }

  s->datum[s->size++] = datum;
  s->aggregate += datum;
  s->median = MedianOfStream_compute_med(s);
}

double MedianOfStream_median(StreamMetaData *s) { return s->median; }

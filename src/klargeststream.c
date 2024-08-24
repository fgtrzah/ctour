#include "../include/klargeststream.h"
#include <stdlib.h>

KthLargest *KthLargest_create(int k, int *datum, int size) {
  KthLargest *stream = (KthLargest *)malloc(sizeof(KthLargest));
  stream->datum = (int *)malloc(sizeof(int) * size);
  stream->k = k;
  stream->size = 0;

  for (int i = 0; i < size; i++) {
    KthLargest_add(stream, datum[i]);
  }

  return stream;
}

void KthLargest_enqueue(int *datum, int size, int o) {
  int i = size - 1;
  while (i >= 0 && datum[i] < o) {
    datum[i + 1] = datum[i];
    i--;
  }
  datum[i + 1] = o;
}

int KthLargest_add(KthLargest *stream, int datum) {
  if (stream->size < stream->k) {
    KthLargest_enqueue(stream->datum, stream->size, datum);
  } else if (datum > stream->datum[stream->size - 1]) {
    KthLargest_enqueue(stream->datum, stream->size - 1, datum);
  }

  stream->size++;
  return stream->datum[stream->size - 1];
}

void KthLargest_flush(KthLargest *stream) {
  free(stream->datum);
  free(stream);
}

#ifndef K_LARGEST_STREAM_H
#define K_LARGEST_STREAM_H

typedef struct {
  int largest;
  int size;
  int k;
  int *datum;
} KthLargest;

KthLargest *KthLargest_create(int k, int *datum, int size);
void KthLargest_enqueue(int *datum, int size, int o);
int KthLargest_add(KthLargest *stream, int datum);
void KthLargest_flush(KthLargest *stream);

#endif // !K_LARGEST_STREAM_H

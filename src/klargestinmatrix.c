#include "../include/klargestinmatrix.h"
#include <stdio.h>
#include <stdlib.h>

void swap(HeapNode *a, HeapNode *b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

int KLargestInMatrix_ingest(int n, int **datum) { return -1; }

int KLargestInMatrix_get_k(int k, int **datum) {
  int n = 0;

  while (datum[0][n] != '\0') {
    n++;
  }

  int heapSize = 0;
  HeapNode *heap = (HeapNode *)malloc(k * sizeof(HeapNode));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      printf("r: %d\n", datum[i][j]);
      if (heapSize < k) {
        heap[heapSize++] = (HeapNode){datum[i][j], i, j};
      } else if (datum[i][j] > heap[0].value) {
        heap[0] = (HeapNode){datum[i][j], i, j};
        KLargestInMatrix_min_heapify(heap, k, 0);
      }
    }
  }

  for (int i = k / 2 - 1; i >= 0; --i)
    KLargestInMatrix_min_heapify(heap, k, i);

  int result = heap[0].value;
  free(heap);

  return result;
}

void KLargestInMatrix_min_heapify(HeapNode heap[], int n, int i) {
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && heap[left].value < heap[smallest].value)
    smallest = left;

  if (right < n && heap[right].value < heap[smallest].value)
    smallest = right;

  if (smallest != i) {
    swap(&heap[i], &heap[smallest]);
    KLargestInMatrix_min_heapify(heap, n, smallest);
  }
}

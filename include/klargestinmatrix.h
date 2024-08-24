#ifndef K_LARGEST_IN_MATRIX_H
#define K_LARGEST_IN_MATRIX_H

typedef struct {
  int value;
  int row;
  int col;
} HeapNode;

int KLargestInMatrix_ingest(int n, int **datum);

int KLargestInMatrix_get_k(int k, int **datum);

void KLargestInMatrix_min_heapify(HeapNode heap[], int n, int i);

#endif // !K_LARGEST_IN_MATRIX_H

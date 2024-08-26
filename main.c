#include "include/binarysearchtree.h"
#include "include/c1.lsip.h"
#include "include/c2.sockinit.h"
#include "include/c2.timeserver.h"
#include "include/c3.tcpclient.h"
#include "include/c3.toupperref.h"
#include "include/c4.udprecvfrom.h"
#include "include/c4.udpservermd5.h"
#include "include/c5.dnsutils.h"
#include "include/c5.lookup.h"
#include "include/c6.webget.h"
#include "include/c7.webserver.h"
#include "include/c9.dynamicmem.h"
#include "include/colorize.h"
#include "include/computemd5.h"
#include "include/datumarray.h"
#include "include/dynamicpriorityqueue.h"
#include "include/heap.h"
#include "include/kclosestorigin.h"
#include "include/klargest.h"
#include "include/klargestinmatrix.h"
#include "include/klargeststream.h"
#include "include/ksortedlists.h"
#include "include/linkedlist.h"
#include "include/linkedlistnode.h"
#include "include/medianofstream.h"
#include "include/queue.h"
#include "include/reprompt.h"
#include "include/search.h"
#include "include/stack.h"
#include "include/trie.h"
#include <assert.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_stack() {
  struct Stack *stack = malloc(sizeof(struct Stack));

  Stack_init(stack);
  Stack_push(stack, 10);

  assert(Stack_peek(stack) == 10);
  Stack_push(stack, 20);
  assert(Stack_peek(stack) == 20);
  Stack_push(stack, 30);
  assert(Stack_peek(stack) == 30);

  Stack_push(stack, 40);

  assert(Stack_peek(stack) == 40);
  assert(Stack_pop(stack) == 40);
  assert(Stack_pop(stack) == 30);
  assert(Stack_pop(stack) == 20);
  assert(Stack_pop(stack) == 10);
  assert(Stack_pop(stack) == -1);
}

void test_linkedlist() {
  int lcap = sizeof(struct LinkedList) + 2 * sizeof(struct LinkedListNode) +
             sizeof(int);
  int llncap = sizeof(int) + 2 * sizeof(struct LinkedListNode);
  struct LinkedList *l = calloc(5, lcap);
  LinkedList_init(l, 2);

  assert(l->head->data == 2);
  assert(LinkedList_search(l, 0).data == 2);
  LinkedList_append(l, 4);
  assert(l->head->next->data == 4);
  struct LinkedListNode *nnr1 = malloc(llncap);
  *nnr1 = LinkedList_insert(l, 1, 3);

  assert(l->head->next->data == 3);
  assert(l->head->next->next->data == 4);

  struct LinkedList *m = malloc(2 * lcap + (2 * llncap));

  assert(LinkedList_delete(m, 0) == -1);
  assert(LinkedList_delete(NULL, 0) == -1);

  LinkedList_init(m, 1);
  LinkedList_append(m, 5);
  LinkedList_append(m, 6);
  LinkedList_append(m, 7);

  assert(LinkedList_delete(m, 3) == 7);
  assert(LinkedList_delete(m, 2) == 6);
  assert(LinkedList_delete(m, 1) == 5);
  assert(LinkedList_delete(m, 0) == 1);
}

void test_bst() {
  BST *bst = createBST();

  int datum[] = {50, 30, 20, 40, 70, 60, 80};
  int fsize = sizeof(datum) / sizeof(datum[0]);

  for (int i = 0; i < fsize; i++) {
    insert(bst, datum[i]);
  }

  BSTTreeNode *result = search(bst, 20);

  assert(result->data == 20);

  removeNode(bst, 20);

  assert(search(bst, 20) == NULL);
  assert(search(bst, 50) != NULL);
  assert(search(bst, 90) == NULL);

  // Perform traversals
  printf("iot: ");
  inorderTraversal(bst->root);
  printf("\n");
  printf("peot: ");
  preorderTraversal(bst->root);
  printf("\n");
  printf("pot: ");
  postorderTraversal(bst->root);
  printf("\n");

  // Destroy the BST
  destroyBST(bst);
  bst = NULL;

  assert((int)!bst);

  bst = initializeBST(datum, fsize);

  assert(search(bst, 155) == NULL);
  assert(search(bst, 60) != NULL);
}

void test_queue() {
  int datum[] = {1, 2, 3, 4, 5};
  int dsize = sizeof(datum) / sizeof(datum[0]);
  struct Queue *q = (Queue *)malloc(sizeof(struct Queue));

  printf(">>>> %d\n", dsize);
  for (int i = 0; i < dsize; i++) {
    printf("%d\n", datum[i]);
    enqueue(q, datum[i]);
  }

  for (int i = 0; i < dsize; i++) {
    assert(datum[i] == dequeue(q));
  }

  assert(sizeof(*q) == 16);
}

void test_c1_lsip() { assert(!lsip()); }

void test_heap_top3() {
  int elements[] = {10, 20, 5, 30, 15};
  int n = sizeof(elements) / sizeof(elements[0]);
  Heap *h = Heap_init(2 * n, elements, n);
  int i = 0;
  int expected[] = {5, 10, 15};

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    printf("exp, acc: %d, %d\n", e.element, expected[i]);
    assert(e.element == expected[i]);
    i++;
  }

  int fixtures[] = {3, 1, 2, 10, 33, 100, 20};
  int exp_2[] = {1, 2, 3};
  i = 0;
  h = Heap_init(2 * 7, fixtures, 7);

  while (i < 3) {
    HeapElement e = Heap_dequeue(h);
    printf("exp, acc: %d, %d\n", e.element, exp_2[i]);
    assert(e.element == exp_2[i]);
    i++;
  }
}

void test_heap() {
  int elements[] = {10, 20, 5, 30, 15};
  int n = sizeof(elements) / sizeof(elements[0]);
  Heap *pq = Heap_init(10, elements, n);
  HeapElement elem = Heap_peek(pq);
  printf("Peek: Element = %d\n", elem.element);
  int expected[] = {5, 10, 15, 20, 30};
  int i = 0;

  while (!Heap_empty(pq) && i < n) {
    elem = Heap_dequeue(pq);
    assert(elem.element == expected[i]);
    printf("exp, acc: %d, %d\n", elem.element, expected[i]);
    i++;
  }

  int fixtures[] = {5, 7, 3};
  Heap *h = Heap_init(3, fixtures, 3);

  while (!Heap_empty(h) && i < 3) {
    HeapElement e = Heap_dequeue(h);

    assert(e.element == fixtures[i]);
    printf("exp, acc: %d, %d\n", e.element, expected[i]);
  }

  Heap_flush(pq);
}

void test_nclosestorigin() {
  CoordList *heap = KClosestOrigin_init(10);
  int k = 3;

  KClosestOrigin_enqueue(heap, (Coordinate){3, 4});
  KClosestOrigin_enqueue(heap, (Coordinate){1, 1});
  KClosestOrigin_enqueue(heap, (Coordinate){0, 2});
  KClosestOrigin_enqueue(heap, (Coordinate){2, 2});
  KClosestOrigin_enqueue(heap, (Coordinate){5, 4});
  KClosestOrigin_enqueue(heap, (Coordinate){1, 2});
  KClosestOrigin_enqueue(heap, (Coordinate){8, 2});
  KClosestOrigin_enqueue(heap, (Coordinate){2, -1});

  while (k < heap->size) {
    Coordinate p = KClosestOrigin_dequeue(heap);
    printf("Coordinate: (%d, %d), Distance: (%f)\n", p.x, p.y,
           KClosestOrigin_distance(p));
  }

  while (k > 0) {
    Coordinate p = KClosestOrigin_dequeue(heap);

    printf("Coordinate: (%d, %d), Distance: (%f)\n", p.x, p.y,
           KClosestOrigin_distance(p));
    k--;
  }
}

void test_klargest() {
  int fixtures1[] = {3, 2, 1, 5, 6, 4};
  int n = sizeof(fixtures1) / sizeof(fixtures1[0]);
  int res = KLargest_getlargest(fixtures1, 2, n);
  printf("res: %d\n", res);
  assert(res == 3);

  int fixtures2[] = {3, 2, 1, 2, 4, 5, 6};
  n = sizeof(fixtures2) / sizeof(fixtures2[0]);
  res = KLargest_getlargest(fixtures2, 4, n);
  printf("res: %d\n", res);
  assert(res == 4);
}

void test_klargeststream() {
  int fixtures[] = {4, 5, 8, 2};
  int n = sizeof(fixtures) / sizeof(fixtures[0]);
  int k = 3;
  KthLargest *stream = KthLargest_create(k, fixtures, n);

  printf("largest in stream: %d\n", KthLargest_add(stream, 3));
  assert(5 != KthLargest_add(stream, 5));
  assert(5 != KthLargest_add(stream, 10));
  assert(8 != KthLargest_add(stream, 9));
  assert(8 != KthLargest_add(stream, 4));
}

void test_c2_sockinit() {
  assert(!sockinit());
  printf("\n");
}
void test_min_heap() {
  DynamicPriorityQueue *pq =
      DynamicPriorityQueue_create_priority_queue(10, MIN_HEAP);
  assert(DynamicPriorityQueue_insert(pq, 5));
  assert(DynamicPriorityQueue_insert(pq, 5));
  assert(DynamicPriorityQueue_insert(pq, 3));
  assert(DynamicPriorityQueue_insert(pq, 8));
  assert(DynamicPriorityQueue_insert(pq, 1));

  assert(DynamicPriorityQueue_peek(pq) == 1);
  assert(DynamicPriorityQueue_extract(pq) == 1);
  assert(DynamicPriorityQueue_peek(pq) == 3);

  assert(DynamicPriorityQueue_extract(pq) == 3);
  assert(DynamicPriorityQueue_extract(pq) == 5);
  assert(DynamicPriorityQueue_extract(pq) == 5);
  assert(DynamicPriorityQueue_extract(pq) == 8);

  assert(DynamicPriorityQueue_is_empty(pq) == true);

  DynamicPriorityQueue_destroy_priority_queue(pq);
}

void test_max_heap() {
  DynamicPriorityQueue *pq =
      DynamicPriorityQueue_create_priority_queue(10, MAX_HEAP);

  assert(DynamicPriorityQueue_insert(pq, 5) == true);
  assert(DynamicPriorityQueue_insert(pq, 3) == true);
  assert(DynamicPriorityQueue_insert(pq, 8) == true);
  assert(DynamicPriorityQueue_insert(pq, 1) == true);

  assert(DynamicPriorityQueue_peek(pq) == 8);
  printf("%d\n", DynamicPriorityQueue_peek(pq));
  int t = DynamicPriorityQueue_extract(pq);
  printf("%d\n", t);
  assert(t == 8);
  assert(DynamicPriorityQueue_peek(pq) == 5);

  assert(DynamicPriorityQueue_extract(pq) == 5);
  assert(DynamicPriorityQueue_extract(pq) == 3);
  assert(DynamicPriorityQueue_extract(pq) == 1);

  assert(DynamicPriorityQueue_is_empty(pq) == true);

  DynamicPriorityQueue_destroy_priority_queue(pq);
}

void test_insert_and_extract() {
  DynamicPriorityQueue *pq =
      DynamicPriorityQueue_create_priority_queue(5, MIN_HEAP);

  assert(DynamicPriorityQueue_insert(pq, 10) == true);
  assert(DynamicPriorityQueue_insert(pq, 20) == true);
  assert(DynamicPriorityQueue_insert(pq, 5) == true);
  assert(DynamicPriorityQueue_insert(pq, 15) == true);
  assert(DynamicPriorityQueue_insert(pq, 25) == true);
  assert(DynamicPriorityQueue_insert(pq, 30) == false); // Exceeds capacity

  assert(DynamicPriorityQueue_extract(pq) == 5);
  assert(DynamicPriorityQueue_extract(pq) == 10);
  assert(DynamicPriorityQueue_extract(pq) == 15);
  assert(DynamicPriorityQueue_extract(pq) == 20);
  assert(DynamicPriorityQueue_extract(pq) == 25);

  assert(DynamicPriorityQueue_is_empty(pq) == true);

  DynamicPriorityQueue_destroy_priority_queue(pq);
}

// TODO: implement
void test_ksortedlists() {
  int f1[][3] = {{1, 4, 5}, {1, 3, 4}, {2, 6, 10}};
  int f1_expected[] = {1, 1, 2, 3, 4, 4, 5, 6, 10};
  int n = 9;
  int i = 0;
  int r1o[n];
  int *r1 = (int *)malloc(sizeof(f1_expected));

  r1 = KSortedLists_merge(3, 3, f1, r1o);
  printf("r1\n");

  while (i < n) {
    printf("%d, ", r1[i]);
    i++;
  }

  assert(1);
}

void test_c2_timeserver() { assert(!timeserver()); }

void test_c3_tcpclient(int argc, char *argv[]) {
  assert(!tcpclient_init(argc, argv));
}

void test_md5() {
  const char *test_str = "Hello, world!";
  unsigned char digest[16];
  char hex_string[33];

  MD5(test_str, digest);
  to_hex_string(digest, hex_string);

  printf("MD5(\"%s\") = %s\n", test_str, hex_string);
}

void test_case(int **matrix, int k, int expected) {
  int result = KLargestInMatrix_get_k(k, matrix);
  printf("expected: %d, Got: %d\n", expected, result);
  assert(expected == result);
}

void test_klargestinmatrix() {
  // Test Case 1
  int *matrix1[] = {(int[]){1, 2, '\0'}, (int[]){3, 4, '\0'}};
  int k1 = 2;
  test_case(matrix1, k1, 3);

  // Test Case 2
  int *matrix2[] = {(int[]){1, 2, 3, '\0'}, (int[]){4, 5, 6, '\0'},
                    (int[]){7, 8, 9, '\0'}};
  int k2 = 5;
  test_case(matrix2, k2, 5);

  // Test Case 3
  int *matrix3[] = {(int[]){-10, -9, -8, '\0'}, (int[]){-7, -6, -5, '\0'},
                    (int[]){-4, -3, -2, '\0'}};
  int k3 = 4;
  test_case(matrix3, k3, -5);

  // Test Case 4
  int *matrix4[] = {
      (int[]){10, 20, 30, 40, 50, '\0'}, (int[]){15, 25, 35, 45, 55, '\0'},
      (int[]){24, 29, 37, 48, 60, '\0'}, (int[]){32, 33, 39, 50, 70, '\0'},
      (int[]){40, 41, 42, 43, 80, '\0'}};
  int k4 = 7;
  test_case(matrix4, k4, 48);

  // // Test Case 5
  int *matrix6[] = {(int[]){1, 2, 3, '\0'}, (int[]){4, 5, 6, '\0'},
                    (int[]){7, 8, 9, '\0'}};
  int k6 = 9;
  test_case(matrix6, k6, 1);

  // // Test Case 6
  int *matrix7[] = {(int[]){42, '\0'}};
  int k7 = 1;
  test_case(matrix7, k7, 42);

  // Test Case 7
  int *matrix8[] = {(int[]){5, 10, 15, '\0'}, (int[]){20, 25, 30, '\0'},
                    (int[]){35, 40, 45, '\0'}};
  int k8 = 4;
  test_case(matrix8, k8, 30);
}

// Helper function to print the call stack
void print_call_stack() {
  void *array[50];
  size_t size;

  size = backtrace(array, 50);
  char **symbols = backtrace_symbols(array, size);

  if (symbols != NULL) {
    colorize("call stack:\t", COLOR_YELLOW);
    for (size_t i = 0; i < size; i++) {
      printf("%s\n", symbols[i]);
    }
    free(symbols);
  } else {
    colorize("Unable to retrieve call stack.\n", COLOR_RED);
  }
}

void test_medianofstream() {
  StreamMetaData *s1 = MedianOfStream_init(4);
  MedianOfStream_add(s1, 1);
  MedianOfStream_add(s1, 2);
  MedianOfStream_add(s1, 3);
  printf("%f\n", MedianOfStream_median(s1));
  assert(MedianOfStream_median(s1) == 2.000000);
  MedianOfStream_add(s1, 4);
  printf("%f\n", MedianOfStream_median(s1));
  assert(MedianOfStream_median(s1) == 2.500000);
}

int main(int argc, char *argv[]) {
  test_da();
  test_stack();
  test_linkedlist();
  test_bst();
  test_queue();
  test_trie();
  test_c1_lsip();
  test_heap();
  test_heap_top3();
  test_nclosestorigin();
  test_klargest();
  test_klargeststream();
  test_c2_sockinit();
  test_min_heap();
  test_max_heap();
  test_insert_and_extract();
  test_ksortedlists();
  test_c2_timeserver();
  test_c3_tcpclient(argc, argv);
  test_toupperref();
  test_md5();
  test_klargestinmatrix();
  test_medianofstream();
  test_c4_udprecvfrom(argc, argv);
  test_c4_udpservermd5();
  reprompt(&argc, argv);
  test_c5_lookup(argc, argv);
  reprompt(&argc, argv);
  test_c5_dnsutils(argc, argv);
  reprompt(&argc, argv);
  test_c6_webget_init(argc, argv);
  test_c7_webserver_init(argc, argv);
  test_c9_dynamicmem();
  test_search();
  print_call_stack();

  printf("\nall tests passed successfully!\n");

  return 0;
}

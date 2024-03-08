#include "../include/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void LinkedList_init(struct LinkedList *h, int x) {
  struct LinkedListNode *nh = malloc(sizeof(struct LinkedListNode));
  nh->data = x;
  nh->next = NULL;
  h->head = nh;
}

LinkedListNode LinkedList_search(struct LinkedList *h, int i) {
  struct LinkedListNode *c = h->head;
  int ci = 0;

  while (ci < i && c) {
    c = c->next;
    ci++;
  }

  return *c;
}

void LinkedList_append(struct LinkedList *h, int x) {
  struct LinkedListNode *c = h->head;
  int ci = 0;

  while (c->next) {
    c = c->next;
  }

  struct LinkedListNode *nn =
      malloc(sizeof(int) + 2 * sizeof(struct LinkedListNode));
  nn->data = x;
  nn->next = NULL;
  c->next = nn;
}

LinkedListNode LinkedList_insert(struct LinkedList *h, int i, int x) {
  int nnsize = sizeof(int) + 2 * sizeof(struct LinkedListNode);

  if (i == 0) {
    struct LinkedListNode *nn = malloc(nnsize);
    
    nn->data = x;
    nn->next = h->head;
    
    return *nn;
  }

  struct LinkedListNode *prev = malloc(nnsize);
  struct LinkedListNode *curr = h->head;
  int count = 0;

  while (count < i && curr) {
    prev = curr;
    curr = curr->next;
    count++;
  }

  // gaurd off-by-one
  if (count < i) {
    printf("invalid index");
    return *h->head;
  }

  struct LinkedListNode *nn = malloc(nnsize);
  
  nn->data = x;
  nn->next = prev->next;
  prev->next = nn;

  return *h->head;
}

void LinkedList_delete(struct LinkedList *h, int i) {}

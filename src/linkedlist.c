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
  if (!h || !h->head || !x) {
    return;
  } 

  int nnsize = sizeof(int) + 2 * sizeof(struct LinkedListNode);
  struct LinkedListNode *c = h->head;

  while (c->next) {
    c = c->next;
  }

  struct LinkedListNode *nn = malloc(nnsize); 
  nn->data = x;
  nn->next = NULL;
  c->next = nn;
}

// TODO: rename h to l
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

int LinkedList_delete(struct LinkedList *l, int i) {
  if (!l || !l->head) {
    return -1;
  }
  
  int ret;
  int nnsize = sizeof(int) + 2 * sizeof(struct LinkedListNode);

  if (!i) {
    ret = l->head->data; 
    l->head = l->head->next;
    return ret;
  }

  struct LinkedListNode *curr = l->head;
  struct LinkedListNode *prev = malloc(nnsize);
  int count = 0;

  while (count < i && curr) {
    prev = curr;
    curr = curr->next;
    count++;
  }

  if (curr) {
    ret = curr->data;
    prev->next = curr->next;
    curr->next = NULL; 
  } else {
    printf("invalid index");
    return -1;
  }

  return ret; 
}

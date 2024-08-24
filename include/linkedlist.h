#ifndef LL
#define LL

#include "linkedlistnode.h"

struct LinkedList {
  struct LinkedListNode *head;
};
typedef struct LinkedList LinkedList;

void LinkedList_init(struct LinkedList *h, int x);
LinkedListNode LinkedList_search(struct LinkedList *h, int x);
void LinkedList_append(struct LinkedList *h, int x);
LinkedListNode LinkedList_insert(struct LinkedList *h, int i, int x);
int LinkedList_delete(struct LinkedList *h, int i);

#endif

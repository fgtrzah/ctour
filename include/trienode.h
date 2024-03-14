#ifndef TRIENODE_H
#define TRIENODE_H
#define N 26

#include <stdbool.h>

typedef struct TrieNode {
  bool is_entry;
  // TODO: convert to enum type of which the members are 
  // lex-sorted alphanum characters 
  char id;
  struct TrieNode *children[N];
} TrieNode;

#endif

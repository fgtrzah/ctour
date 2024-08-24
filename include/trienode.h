#ifndef TRIENODE_H
#define TRIENODE_H
#define N 256

typedef struct TrieNode {
  struct TrieNode *children[N];
  int terminal;
} TrieNode;

#endif

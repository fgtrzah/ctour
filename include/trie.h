#ifndef TRIE_H
#define TRIE_H

#include "./trienode.h"

typedef struct Trie {
  struct TrieNode* root;
} Trie;

Trie *Trie_init(char *w);
struct TrieNode *Trie_search(struct Trie *t, char s[]);
struct TrieNode *Trie_search_node(struct TrieNode *c, char s[], int i);
void Trie_insert(struct Trie *t, char s[]);
void Trie_insert_node(struct TrieNode *c, char s[], int i);
void *Trie_delete_trie(struct Trie *t, char s[]);
void *Trie_delete_trie_node(struct TrieNode *c, char s[], int i);

#endif

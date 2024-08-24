#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct TrieNode {
  struct TrieNode *children[26];
  int is_end;
} TrieNode;

// Function prototypes
TrieNode *Trie_create();
void Trie_insert(TrieNode *root, char *word);
int Trie_search(TrieNode *root, char *word);
void Trie_delete(TrieNode* root, char* word);
void test_trie();

#endif // TRIE_H

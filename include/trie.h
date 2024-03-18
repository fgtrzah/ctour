/*
 * Ref: https://youtu.be/3CbFFVHQrk4?feature=shared&t=1123
 */

#ifndef TRIE_H
#define TRIE_H

#include "../include/trienode.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Trie {
  struct TrieNode *root;
} Trie;

TrieNode *Trie_create_node();
Trie *Trie_init(char *w[], size_t i);

bool Trie_insert(TrieNode **root, char *pre);
bool Trie_search(TrieNode *root, char *pre);
void Trie_completions(TrieNode *root, char *pre);
bool Trie_delete(TrieNode **root, char *pre);
TrieNode *Trie_delete_r(TrieNode *node, unsigned char *text, bool *result);
bool node_has_children(TrieNode *node);

void print_trie(TrieNode *root);
void print_trie_r(TrieNode *n, unsigned char *pre, int l);
char concatenate_string(char *s, char *s1);

#endif

/*
 * Ref: https://youtu.be/3CbFFVHQrk4?feature=shared&t=1123
 */

#ifndef TRIE_H
#define TRIE_H

#include "../include/trienode.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Trie {
  struct TrieNode *root;
} Trie;

// struct TrieNode *Trie_search(struct Trie *t, char s[]);
// struct TrieNode *Trie_search_node(struct TrieNode *c, char s[], int i);
// // unsigned int Trie_insert(struct TrieNode *root, char *word);
// struct TrieNode *make_trienode(char data);
// void Trie_insert_node(struct TrieNode *c, char s[], int i);
// void Trie_delete_trie(struct Trie *t, char s[]);
// void Trie_delete_trie_node(struct TrieNode *c, char s[], int i);

TrieNode *Trie_create_node();
Trie *Trie_init(char *w[], size_t i);
bool Trie_insert(TrieNode **root, char *pre);
void print_trie(TrieNode *root);
void print_trie_r(TrieNode * n, unsigned char *pre, int l);

#endif

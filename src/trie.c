#include "../include/trie.h"
#include "../include/trienode.h"
#include <stdio.h>
#include <stdlib.h>

Trie *Trie_init(char *w) { return NULL; }

struct TrieNode *Trie_search(struct Trie *t, char s[]) {
  return Trie_search_node(t->root, s, 0);
}

struct TrieNode *Trie_search_node(struct TrieNode *c, char s[], int i) {
  size_t sl = sizeof(s) / sizeof(char);

  if (i == sl) {
    return c->is_entry ? c : NULL;
  }

  char nl = s[i];
  int ni = (int)nl;
  struct TrieNode *nc = c->children[ni];

  if (!nc) {
    return Trie_search_node(nc, s, i + 1);
  } else {

    return NULL;
  }
}

void Trie_insert(struct Trie *t, char *s) {
  Trie_insert_node(t->root, s, 0);
}

void Trie_insert_node(struct TrieNode *c, char *s, int i) {
  size_t sl = sizeof(s) / sizeof(char);

  if (i == sl) {
    c->is_entry = true;
  } else {
    char nl = s[i];
    int ni = (int)nl;
    struct TrieNode *nc = c->children[ni];

    if (!nc) {
      c->children[ni] = &(TrieNode){};
      Trie_insert_node(c->children[ni], s, i + 1);
    } else {
      return Trie_insert_node(nc, s, i + 1);
    }
  }
}

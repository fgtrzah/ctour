#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

typedef struct {
  char **datum;
  size_t volume;
  TrieNode *root;
} Corpus;

Corpus *Search_init(int n, char *corpus[]);
char **Search_get_suggestions(Corpus *datum, char *query);
void test_search();

#endif // !SEARCH_H

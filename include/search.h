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

Corpus *Search_init(char **terms);
char **Search_get_suggestions(Corpus *datum, char *query);

#endif // !SEARCH_H

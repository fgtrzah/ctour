#include "../include/search.h"

Corpus *Search_init(char **terms) {
  int n = (int)sizeof(terms) / sizeof(terms[0]);
  Corpus *datum = (Corpus *)malloc(sizeof(Corpus) + n);
  return datum;
}

char **Search_get_suggestions(Corpus *datum, char *query) {
  char **results;
  return results;
}

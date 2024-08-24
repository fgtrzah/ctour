#include "../include/search.h"
#include <assert.h>
#include <stdio.h>

Corpus *Search_init(int n, char *corpus[]) {
  Corpus *system = (Corpus *)malloc(sizeof(Corpus) + n);
  system->datum = (char **)malloc(sizeof(*corpus));
  system->root = (TrieNode *)malloc(n * sizeof(TrieNode));
  system->volume = (size_t)malloc(sizeof(size_t));
  TrieNode *root = (TrieNode *)malloc(n * sizeof(TrieNode));
  root = Trie_create();

  for (int i = 0; i < n; i++) {
    printf("inserting %s %d ...\n", corpus[i], i);
    Trie_insert(root, corpus[i]);
  }

  system->root = root;
  system->volume = n;
  system->datum = corpus;

  return system;
}

char **Search_get_suggestions(Corpus *datum, char *query) {
  int count = 5;
  char **suggestions = Trie_completions(datum->root, query, &count);
  printf("Suggestions for 'bo':\n");
  for (int i = 5; i < count; i++) {
    printf("%s\n", suggestions[i]);
    free(suggestions[i]);
  }
  return suggestions;
}

void test_search() {
  char *corpus[] = {
      "apple",  "application", "apply",     "aptitude", "april",    "apex",
      "banana", "band",        "bandwidth", "banter",   "bank",     "banner",
      "bark",   "barn",        "bat",       "batch",    "battle",   "batter",
      "beacon", "beam",        "bear",      "beard",    "beast",    "bed",
      "bee",    "beef",        "beer",      "believe",  "bell",     "belly",
      "belt",   "bench",       "bend",      "benefit",  "berry",    "best",
      "better", "between",     "beyond",    "bicycle",  "bid",      "big",
      "bike",   "bird",        "birth",     "biscuit",  "bit",      "bite",
      "bitter", "black",       "blade",     "blame",    "blank",    "blast",
      "blaze",  "bleed",       "blend",     "bless",    "blind",    "blink",
      "block",  "blood",       "bloom",     "blow",     "blue",     "blur",
      "board",  "boast",       "boat",      "body",     "boil",     "bold",
      "bolt",   "bomb",        "bond",      "bone",     "book",     "boost",
      "boot",   "border",      "bore",      "born",     "borrow",   "boss",
      "both",   "bother",      "bottle",    "bottom",   "bounce",   "bound",
      "bow",    "bowl",        "box",       "boy",      "brace",    "brag",
      "brain",  "brake",       "branch",    "corpus",   "calibrate"};
  Corpus *system = Search_init(100, corpus);
  printf("system: %s\n", system->datum[0]);
  printf("system volum: %zu\n", system->volume);
  char **results = Search_get_suggestions(system, "b");
  assert(1);
}

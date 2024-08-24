#include "../include/trie.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode *Trie_create() {
  TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  for (int i = 0; i < 26; i++) {
    node->children[i] = NULL;
  }
  node->is_end = 0;
  return node;
}

void Trie_insert(TrieNode *root, char *word) {
  TrieNode *current_node = root;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (current_node->children[index] == NULL) {
      current_node->children[index] = Trie_create();
    }
    current_node = current_node->children[index];
  }
  current_node->is_end = 1;
}

int Trie_search(TrieNode *root, char *word) {
  TrieNode *current_node = root;
  for (int i = 0; word[i] != '\0'; i++) {
    int index = word[i] - 'a';
    if (current_node->children[index] == NULL) {
      return 0;
    }
    current_node = current_node->children[index];
  }
  return current_node->is_end;
}

void Trie_delete(TrieNode *root, char *word) {
  if (root == NULL) {
    return;
  }

  if (word[0] == '\0') {
    root->is_end = 0;
    return;
  }

  int index = word[0] - 'a';
  Trie_delete(root->children[index], word + 1);

  if (root->children[index] == NULL && !root->is_end) {
    free(root);
    root = NULL;
  }
}

void collect_words(TrieNode *node, char *prefix, char **suggestions,
                   int *count) {
  if (node == NULL || *count >= MAX_SUGGESTIONS) {
    return;
  }

  if (node->is_end) {
    suggestions[*count] = strdup(prefix);
    (*count)++;
  }

  for (int i = 0; i < 26; i++) {
    if (node->children[i] != NULL) {
      size_t len = strlen(prefix);
      char *new_prefix =
          (char *)malloc(len + 2); // +1 for the new char and +1 for '\0'
      strcpy(new_prefix, prefix);
      new_prefix[len] = i + 'a';
      new_prefix[len + 1] = '\0';

      collect_words(node->children[i], new_prefix, suggestions, count);
      free(new_prefix);
    }
  }
}

char **Trie_completions(TrieNode *root, char *prefix, int *count) {
  TrieNode *current_node = root;
  *count = 0;

  for (int i = 0; prefix[i] != '\0'; i++) {
    int index = prefix[i] - 'a';
    if (current_node->children[index] == NULL) {
      return NULL;
    }
    current_node = current_node->children[index];
  }

  char **suggestions = (char **)malloc(MAX_SUGGESTIONS * sizeof(char *));
  collect_words(current_node, prefix, suggestions, count);

  return suggestions;
}

void test_trie() {
  TrieNode *root = Trie_create();
  Trie_insert(root, "hello");
  Trie_insert(root, "hell");
  Trie_insert(root, "helicopter");
  Trie_insert(root, "help");
  Trie_insert(root, "world");
  Trie_insert(root, "word");

  printf("Is 'hello' present? \n");
  int x = Trie_search(root, "hello");
  if (x == 1)
    printf("Yes\n");
  else
    printf("No\n");

  assert(x);

  printf("Is 'world' present? \n");
  int y = Trie_search(root, "world");
  if (y == 1)
    printf("Yes\n");
  else
    printf("No\n");
  assert(y);

  Trie_delete(root, "hello");
  printf("Is 'hello' present? \n");
  int z = Trie_search(root, "hello");
  if (z == 1)
    printf("Yes\n");
  else
    printf("No\n");
  assert(!z);

  int count = 0;
  char **suggestions = Trie_completions(root, "hel", &count);
  printf("Suggestions for 'hel':\n");
  for (int i = 0; i < count; i++) {
    printf("%s\n", suggestions[i]);
    free(suggestions[i]);
  }
  free(suggestions);

  // Clean up the Trie
  Trie_delete(root, "hell");
  Trie_delete(root, "helicopter");
  Trie_delete(root, "help");
  Trie_delete(root, "world");
  Trie_delete(root, "word");
  free(root);
}

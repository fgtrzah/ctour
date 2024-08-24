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

void test_trie() {
  TrieNode *root = Trie_create();
  Trie_insert(root, "hello");
  Trie_insert(root, "world");
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
}

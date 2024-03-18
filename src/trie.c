#include "../include/trie.h"
#include "../include/trienode.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode *Trie_create_node() {
  TrieNode *n = malloc(sizeof(struct TrieNode));

  for (int i = 0; i < N; i++) {
    n->children[i] = NULL;
  }

  n->terminal = 0;

  return n;
}

Trie *Trie_init(char *w[], size_t i) {
  struct Trie *t = malloc(sizeof(struct Trie));
  struct TrieNode *c = t->root;

  while (w[0] != "\0" && i) {
    char *word = *w++;
    printf("%s\n", word);

    TrieNode *n = Trie_create_node();
    Trie_insert(&t->root, word);

    i--;
  }

  return t;
}

bool Trie_insert(TrieNode **root, char *pre) {
  if (*root == NULL) {
    *root = Trie_create_node();
  }

  unsigned char *pre_text = (unsigned char *)pre;
  TrieNode *cn = *root;
  int pre_text_l = strlen(pre);

  for (size_t i = 0; i < pre_text_l; i++) {
    if (!cn->children[pre_text[i]]) {
      cn->children[pre_text[i]] = Trie_create_node();
    }
    cn = cn->children[pre_text[i]];
  }

  if (cn->terminal) {
    return false;
  } else {
    cn->terminal = true;
    return true;
  }
}

bool Trie_search(TrieNode *root, char *pre) {
  TrieNode *cn = root;
  unsigned char *pre_text = (unsigned char *)pre;
  int lp = strlen(pre);

  for (int i = 0; i < lp; i++) {
    if (!cn->children[pre_text[i]]) {
      return false;
    }

    cn = cn->children[pre_text[i]];
  }

  return cn->terminal;
}

void Trie_completions(TrieNode *root, char *pre) {
  TrieNode *cn = root;
  unsigned char *pre_text = (unsigned char *)pre;
  int lp = strlen(pre);

  for (int i = 0; i < lp; i++) {
    if (cn->children[pre_text[i]]) {
      printf("%p\n", cn->children);
    }

    cn = cn->children[pre_text[i]];
  }

  for (int i = 0; i < N; i++) {
    if (cn->children[i]) {
      print_trie(cn->children[i]);
    }
  }
}

bool Trie_delete(TrieNode **root, char *pre) {
  unsigned char *pre_text = (unsigned char *)pre;
  bool result = false;

  if (*root == NULL)
    return false;

  *root = Trie_delete_r(*root, pre_text, &result);
  return result;
}

TrieNode *Trie_delete_r(TrieNode *node, unsigned char *text, bool *deleted) {
  if (!node)
    return node;

  if (*text == '\0') {
    if (node->terminal) {
      node->terminal = false;
      *deleted = true;

      if (!node_has_children(node)) {
        free(node);
        node = NULL;
      }
    }
    return node;
  }

  node->children[text[0]] =
      Trie_delete_r(node->children[text[0]], text + 1, deleted);

  if (*deleted && !node_has_children(node) && !node->terminal) {
    free(node);
    node = NULL;
  }

  return node;
}

bool node_has_children(TrieNode *node) {
  if (!node) {
    return false;
  }

  for (int i = 0; i < N; i++) {
    if (node->children[i]) {
      return true;
    }
  }

  return false;
}

void print_trie(TrieNode *root) {
  if (!root) {
    printf("empty");
  } else {
    print_trie_r(root, NULL, 0);
  }
}

void print_trie_r(TrieNode *n, unsigned char *p, int l) {
  unsigned char new_p[l + 2];
  memcpy(new_p, p, l);
  new_p[l + 1] = 0;

  if (n->terminal) {
    printf("terminal: %s\n", p);
  }

  for (int i = 0; i < N; i++) {
    if (n->children[i]) {
      new_p[l] = i;
      print_trie_r(n->children[i], new_p, l + 1);
    }
  }
}

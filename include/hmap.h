#ifndef HMAP_H
#define HMAP_H

#include <stddef.h>

#define HASHMAP_SIZE 1024

typedef struct {
  char *key;
  void *value;
} HashMapEntry;

typedef struct {
  HashMapEntry *entries[HASHMAP_SIZE];
} HashMap;

// Function prototypes
HashMap *create_hashmap();
void add_entry(HashMap *map, const char *key, void *value);
void *get_entry(HashMap *map, const char *key);
void free_hashmap(HashMap *map);

#endif // HASHMAP_H

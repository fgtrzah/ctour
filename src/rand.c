#include "../include/rand.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char rand_char(int i) {
  char charset[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  return charset[i];
}

char *gen_rand(int argc, char *argv[]) {
  (time(NULL));
  char *str = malloc(sizeof(char) * 32);

  return str;
}

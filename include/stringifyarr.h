#ifndef STRINGIFY_H
#define STRINGIFY_H

#include <stdio.h>

// Macros for different types
#define STRINGIFY_INT(value) printf("%d", value)

#define STRINGIFY_FLOAT(value) printf("%.2f", value)

#define STRINGIFY_CHAR(value) printf("%c", value)

#define STRINGIFY_STRING(value) printf("\"%s\"", value)

// Macro to stringify arrays of integers
#define STRINGIFY_INT_ARRAY(arr, length)                                       \
  do {                                                                         \
    printf("[");                                                               \
    for (size_t i = 0; i < length; ++i) {                                      \
      if (i > 0)                                                               \
        printf(", ");                                                          \
      STRINGIFY_INT(arr[i]);                                                   \
    }                                                                          \
    printf("]");                                                               \
  } while (0)

// Macro to stringify arrays of floats
#define STRINGIFY_FLOAT_ARRAY(arr, length)                                     \
  do {                                                                         \
    printf("[");                                                               \
    for (size_t i = 0; i < length; ++i) {                                      \
      if (i > 0)                                                               \
        printf(", ");                                                          \
      STRINGIFY_FLOAT(arr[i]);                                                 \
    }                                                                          \
    printf("]");                                                               \
  } while (0)

// Macro to stringify arrays of chars
#define STRINGIFY_CHAR_ARRAY(arr, length)                                      \
  do {                                                                         \
    printf("[");                                                               \
    for (size_t i = 0; i < length; ++i) {                                      \
      if (i > 0)                                                               \
        printf(", ");                                                          \
      STRINGIFY_CHAR(arr[i]);                                                  \
    }                                                                          \
    printf("]");                                                               \
  } while (0)

// Macro to stringify arrays of strings
#define STRINGIFY_STRING_ARRAY(arr, length)                                    \
  do {                                                                         \
    printf("[");                                                               \
    for (size_t i = 0; i < length; ++i) {                                      \
      if (i > 0)                                                               \
        printf(", ");                                                          \
      STRINGIFY_STRING(arr[i]);                                                \
    }                                                                          \
    printf("]");                                                               \
  } while (0)

#endif // STRINGIFY_H

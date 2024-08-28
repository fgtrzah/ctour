/* all globally required header related
 * content */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STRINGIFY_FIELD(field, format) #field ": " format

#define STRINGIFY_STRUCT(datum, buffer, size, ...)                             \
  do {                                                                         \
    snprintf(buffer, size, __VA_ARGS__);                                       \
  } while (0)

size_t size_datum(void *array, size_t dim);
void test_size_datum();

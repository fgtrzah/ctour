#include "../include/c9.dynamicmem.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../include/colorize.h"
#include "../include/dynamicvector.h"
#include "../include/stringifyarr.h"

/* static-extent data area */
static int global_datum = 100;
static int global_counter = 0;

int c9_dynamicmem_tour_mem_areas() {
  /* static-extent area */
  printf("--static-extent area--\n");
  printf("global_datum, global_counter: %d %d\n", global_datum, global_counter);

  /* constant data area */
  const char *msg =
      "hello world - awkejfhawjehf2342342hfawfeh2139879238472984==";
  const int days_in_week = 7;
  printf("--constant data area--\n");
  printf("msg, days_in_week: %s %d\n", msg, days_in_week);

  /* stack data area */
  int local_datum = 42;
  char local_buffer[local_datum];
  printf("--stack data area--\n");
  printf("local_datum, local_buffer: %d %s\n", local_datum, local_buffer);

  /* heap data area */
  int *dynamic_array = (int *)malloc(10 * sizeof(int));

  dynamic_array[1] = 1;
  dynamic_array[2] = 2;
  dynamic_array[3] = 3;

  if (dynamic_array == NULL) {
    colorize("memory allocation for heap data area failed", COLOR_RED);
    return 1;
  }

  printf("--heap data area--\n");
  printf("dynamic_array\n");
  STRINGIFY_INT_ARRAY(dynamic_array, 10);
  printf("\n");

  free(dynamic_array);

  return 0;
}

int c9_dynamicmem_tour_mem_alloc() {
  // 1. malloc() example
  int *array_malloc =
      (int *)malloc(10 * sizeof(int)); // allocate memory for 10 integers
  if (array_malloc == NULL) {
    printf("malloc() failed!\n");
    return 1;
  }

  // Initialize and print the array (uninitialized values)
  for (int i = 0; i < 10; i++) {
    array_malloc[i] = i + 1;
    printf("array_malloc[%d] = %d\n", i, array_malloc[i]);
  }

  // 2. calloc() example
  int *array_calloc = (int *)calloc(
      10, sizeof(int)); // allocate memory for 10 integers, initialized to 0
  if (array_calloc == NULL) {
    printf("calloc() failed!\n");
    free(array_malloc); // Free previously allocated memory
    return 1;
  }

  // Print the array (initialized to zero)
  printf("\ncalloc() initialized values:\n");
  for (int i = 0; i < 10; i++) {
    printf("array_calloc[%d] = %d\n", i, array_calloc[i]);
  }

  // 3. realloc() example
  int *array_realloc = (int *)realloc(
      array_malloc, 20 * sizeof(int)); // resize array to hold 20 integers
  if (array_realloc == NULL) {
    printf("realloc() failed!\n");
    free(array_calloc); // Free previously allocated memory
    free(array_malloc); // Free the original malloc block if realloc fails
    return 1;
  }

  // Initialize the new part and print the entire array
  printf("\nrealloc() resized and initialized values:\n");
  for (int i = 10; i < 20; i++) {
    array_realloc[i] = i + 1;
  }
  for (int i = 0; i < 20; i++) {
    printf("array_realloc[%d] = %d\n", i, array_realloc[i]);
  }

  // 4. Free allocated memory
  free(array_calloc);
  free(array_realloc);
  return 0;
}

int c9_dynamicmem_tour_dynamic_mgmt() {
  char *s;
  s = "kjfhakwjhfawkejf312312313wddd123123-213123-12313"; // String literal

  printf("dynamic allocation of a copy of a string\n");

  char *p;
  p = (char *)malloc(strlen(s) +
                     1); // Allocate memory for the copy of the string

  if (p != NULL) {
    strcpy(p, s); // Copy the string into dynamically allocated memory
  } else {
    return 1; // Memory allocation failed
  }

  printf("dynamically allocated string: %s\n", p);

  // Free the dynamically allocated memory
  free(p);
  p = NULL;

  return 0;
}

int c9_dynamicmem_tour_matrices() {
  int m = 80, n = 40;
  double **p;
  int i;
  p = (double **)malloc(m * sizeof(double *));

  for (i = 0; i < m; ++i) {
    p[i] = (double *)malloc(n * sizeof(double));
  }

  for (int j = 0; j < m; j++) {
    for (int k = 0; k < n; k++) {
      printf("%f\t", p[j][k]);
    }
    printf("\n");
  }
  free(p);

  return 0;
}

int c9_dynamicmem_tour_dynamic_arr() {
  DynamicVector *v = DynamicVector_init();

  STRINGIFY_INT_ARRAY(v->datum, v->size);

  for (int i = 0; i < 10; i++) {
    int newsize = DynamicVector_push_back(v, i);
    printf("newsize: %d\n", newsize);
  }

  STRINGIFY_INT_ARRAY(v->datum, 10);

  for (int i = 9; i < 20; i++) {
    DynamicVector_push_back(v, i);
  }

  STRINGIFY_INT_ARRAY(v->datum, 10);

  for (int i = 0; i < 20; i++) {
    int b = DynamicVector_pop_back(v);
    printf("b: %d\n", b);
  }
  printf("\n");

  return 0;
}

void test_c9_dynamicmem() {
  assert(!c9_dynamicmem_tour_mem_areas());
  assert(!c9_dynamicmem_tour_mem_alloc());
  assert(!c9_dynamicmem_tour_dynamic_mgmt());
  assert(!c9_dynamicmem_tour_matrices());
  assert(!c9_dynamicmem_tour_dynamic_arr());
}

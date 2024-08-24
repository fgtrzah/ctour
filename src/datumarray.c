#include "../include/datumarray.h"
#include "../include/stringifyarr.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int count_days(int days[], int len) {
  int total = 0;
  while (len--)
    total += days[len];
  return total;
}

void print_base_b(unsigned x, unsigned b) {
  char buf[50];
  int q = x, i = 0;
  assert(b >= 2);

  do {
    assert(i < 50);
    x = q;
    q = x / b;
    buf[i++] = "0123456789abcdefghijklmnopqrstuvwxyz"[x - q * b];
  } while (q > 0);

  for (--i; i >= 0; --i) {
    printf("%c", buf[i]);
  }

  printf("\n");
}

int da_initialization() {
  int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int localarray[40] = {0};
  int daysshort[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int daysshort_s = sizeof(daysshort);
  int days_s = sizeof(days);
  int computed_s_days = sizeof(days) / sizeof(days[0]);

  for (int i = 0; i < computed_s_days; ++i)
    printf("Month %d has %d days.\n", i + 1, days[i]);

  int *pdays = days;
  int size1 = sizeof(days);  /* size1 equals 12 * sizeof(int) */
  int size3 = sizeof(pdays); /* size3 equals sizeof(int *) */

  count_days(days, 12);

  printf("\ndays: \t");
  STRINGIFY_INT_ARRAY(days, 12);

  printf("\nlocalarray: \t");
  STRINGIFY_INT_ARRAY(localarray, 40);

  printf("\ndaysshort: \t");
  STRINGIFY_INT_ARRAY(daysshort, 12);

  printf("\ndaysshort_s: %d\n", daysshort_s);
  printf("\ndays_s: %d\n", days_s);
  printf("\ncomputed_s_days: %d\n", computed_s_days);
  printf("sizeof(days): %d\n", size1);
  printf("sizeof(pdays): %d\n", size3);

  return 0;
}

int da_chararrays_strings() {
  char letters[] = {'a', 'b', 'c', 'd', 'e'};
  char letters_alt[] = {'a', 'b', 'c', 'd', 'e', '\0'};
  char letters_bs[5] = "abcde";

  printf("\nletters: %s\t", letters);
  printf("\nletters_alt: %s\t", letters_alt);
  printf("\nletters_bs: %s\t", letters_bs);

  // double *pval = 9.6;           /* Invalid. Won’t compile. */
  // int *parray = {1, 2, 3};      /* Invalid. Won’t compile. */

  char *str = "\nHello World!\n"; /* Correct. But array is read-only. */
  printf("\nstr %s\n\t", str);

  printf("print base of 19.23: \n\t");
  print_base_b(19, 11);

  return 0;
}

int da_strings_stdlib() {
  // Example for size_t strlen(const char *s)
  const char *str1 = "Hello, World!";
  size_t length = strlen(str1);
  printf("Length of '%s': %zu\n", str1, length);

  // Example for char *strcpy(char *s, const char *t)
  char buffer[50];
  const char *source = "Copy this string";
  strcpy(buffer, source);
  printf("Copied string: '%s'\n", buffer);

  // Example for int strcmp(const char *s, const char *t)
  const char *str2 = "apple";
  const char *str3 = "banana";
  int result = strcmp(str2, str3);
  if (result < 0) {
    printf("'%s' is less than '%s'\n", str2, str3);
  } else if (result > 0) {
    printf("'%s' is greater than '%s'\n", str2, str3);
  } else {
    printf("'%s' is equal to '%s'\n", str2, str3);
  }

  // Example for char *strcat(char *s, const char *t)
  char str4[50] = "Hello";
  const char *suffix = " World!";
  strcat(str4, suffix);
  printf("Concatenated string: '%s'\n", str4);

  // Example for char *strchr(const char *s, int c)
  const char *str5 = "Find the first occurrence of 'o'";
  char ch = 'o';
  char *first_occurrence = strchr(str5, ch);
  if (first_occurrence) {
    printf("First occurrence of '%c': %s\n", ch, first_occurrence);
  } else {
    printf("Character '%c' not found\n", ch);
  }

  // Example for char *strrchr(const char *s, int c)
  const char *str6 = "Find the last occurrence of 'o'";
  char *last_occurrence = strrchr(str6, ch);
  if (last_occurrence) {
    printf("Last occurrence of '%c': %s\n", ch, last_occurrence);
  } else {
    printf("Character '%c' not found\n", ch);
  }

  // Example for char *strstr(const char *s, const char *t)
  const char *str7 = "Look for the substring 'sub'";
  const char *substr = "sub";
  char *substring_location = strstr(str7, substr);
  if (substring_location) {
    printf("Substring '%s' found at: %s\n", substr, substring_location);
  } else {
    printf("Substring '%s' not found\n", substr);
  }

  return 0;
}

int da_pointerarray() {
  int N = 10;
  int parray[N];
  STRINGIFY_INT_ARRAY(parray, N);
  double v = 9.7;
  double array[] = {3.2, 4.3, 5.4};
  double *pa_a[] = {&v, array + 1, NULL};
  for (int i = 0; i < 2; i++) {
    printf("pa item: %f", *pa_a[i]);
    printf("array item: %f", array[i]);
  }
  int a1[] = {1, 2, 3, 4};
  int a2[] = {5, 6, 7};
  int *pa[] = {a1, a2}; /* pa stores pointers to beginning of each array. */
  int **pp = pa;  /* Pointer-to-a-pointer holds address of beginning of pa. */
  int *p = pa[1]; /* Pointer to the second array in pa. */
  int val;
  val = pa[1][1]; /* equivalent operations: val = 6 */
  printf("val: %d\n", val);
  val = pp[1][1];
  printf("val: %d\n", val);
  val = *(pa[1] + 1);
  printf("val: %d\n", val);
  val = *(pp[1] + 1);
  printf("val: %d\n", val);
  val = *(*(pp + 1) + 1);
  printf("val: %d\n", val);
  val = p[1];
  printf("val: %d\n", val);
  return 0;
}

#define SIZE 3

void prod(int (*r)[SIZE], const int a[][SIZE], const int b[SIZE][SIZE]) {
  int i, j, k;
  for (int i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j)
      for (k = 0; k < SIZE; ++k)
        r[i][j] += a[i][k] * b[k][j];
  }
}

int da_multidim() {

  float m1[3][4] = {
      {2.4, 8.7, 9.5, 2.3}, {6.2, 4.8, 5.1, 8.9}, {7.2, 1.6, 4.4, 3.6}};
  float oneD[] = {2.4, 8.7, 9.5, 2.3, 6.2, 4.8, 5.1, 8.9, 7.2, 1.6, 4.4, 3.6};
  float m2[][4] = {/* The 4 must be specified. */
                   {2.4, 8.7, 9.5, 2.3},
                   {6.2, 4.8, 5.1, 8.9}};

  short array3d[4][2][3] = {{{0, 1, 2}, {3, 4, 5}},
                            {{6, 7, 8}, {9, 10, 11}},
                            {{12, 13, 14}, {15, 16, 17}},
                            {{18, 19, 20}, {21, 22, 23}}};

  int m[][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int n[SIZE][SIZE] = {0};
  int i, j;
  prod(n, m, m);

  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      printf("%3d ", n[i][j]);
    }
    printf("\n");
  }

  return 0;
}

void test_da() {
  assert(!da_initialization());
  assert(!da_chararrays_strings());
  assert(!da_strings_stdlib());
  assert(!da_pointerarray());
  assert(!da_multidim());
}

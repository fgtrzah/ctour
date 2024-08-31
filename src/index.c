#include "../include/index.h"

size_t size_datum(void *array, size_t dim) {
  size_t count = 0;

  if (dim == 0 || array == NULL) {
    return 0;
  }

  if (dim == 1) {
    int *array_xo = (int *)array;
    while (array_xo[count] != 0) {
      count++;
    }
  } else if (dim > 1) {
    int **array_xo = (int **)array;

    while (*array_xo != NULL) {
      if (*array_xo == (int *)0x1 || *array_xo == (int *)0x2) {
        fprintf(stderr, "Invalid memory access detected.\n");
        break;
      }

      count += size_datum(*array_xo, dim - 1);
      array_xo++;
    }
  }

  return count;
}

void test_size_datum() {
  int **dyn_array2D = malloc(4 * sizeof(int *));

  dyn_array2D[0] = (int[]){1, 2, 3, 0};
  dyn_array2D[1] = (int[]){4, 5, 6, 0};
  dyn_array2D[2] = (int[]){7, 8, 9, 0};
  dyn_array2D[3] = NULL;

  printf("Total elements in dynamic 2D array: %zu\n",
         size_datum(dyn_array2D, 2));

  // Dynamically allocated 3D array
  int ***dyn_array3D = malloc(3 * sizeof(int **));

  dyn_array3D[0] = malloc(3 * sizeof(int *));
  dyn_array3D[1] = malloc(3 * sizeof(int *));
  dyn_array3D[0][0] = (int[]){1, 2, 0};
  dyn_array3D[0][1] = (int[]){3, 4, 0};
  dyn_array3D[1][0] = (int[]){5, 6, 0};
  dyn_array3D[1][1] = (int[]){7, 8, 0};
  dyn_array3D[2] = NULL;

  printf("Total elements in dynamic 3D array: %zu\n",
         size_datum(dyn_array3D, 3));

  // Free dynamically allocated memory for 3D array
  for (size_t i = 0; i < 2; i++) {
    free(dyn_array3D[i]);
  }
  free(dyn_array3D);
}

#include "../include/reprompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_ARG_LEN 100

void reprompt(int *argc, char *argv[], char *msg) {
  char input[256];
  int new_argc = 1;
  char *token;
  printf("%s", input);
  // Ask for user input
  printf("%s...\n", msg);
  printf("Enter new command-line arguments: ");
  if (fgets(input, sizeof(input), stdin) == NULL) {
    perror("fgets failed");
    exit(EXIT_FAILURE);
  }

  // Remove the trailing newline character
  input[strcspn(input, "\n")] = '\0';

  // Count the number of arguments
  token = strtok(input, " ");
  while (token) {
    new_argc++;
    token = strtok(NULL, " ");
  }

  // Reset the tokenization
  token = strtok(input, " ");

  // Repopulate argv
  int i = 1;
  while (token) {
    argv[i] = strdup(token);
    if (argv[i] == NULL) {
      perror("strdup failed");
      exit(EXIT_FAILURE);
    }
    token = strtok(NULL, " ");
    i++;
  }

  // Set the last element to NULL as per convention
  argv[i] = NULL;

  // Update argc
  *argc = new_argc;
}

#ifndef REPROMPT_H
#define REPROMPT_H

typedef struct {
  int argc;
  void *argv;
} Args;

void reprompt(int *argc, char *argv[], char *msg);

#endif // !REPROMPT_H

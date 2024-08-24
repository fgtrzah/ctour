#ifndef COLORIZE_H
#define COLORIZE_H

#include <stdio.h>

typedef enum {
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_RESET
} Color;

const char *Colorize_get_color_code(Color c);

int colorize(char *s, Color c);

#endif // !COLORIZE_H

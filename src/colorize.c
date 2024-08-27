#include "../include/colorize.h"

#include <stdio.h>

const char *Colorize_get_color_code(Color color) {
  switch (color) {
  case COLOR_RED:
    return "\033[0;31m";
  case COLOR_GREEN:
    return "\033[0;32m";
  case COLOR_YELLOW:
    return "\033[0;33m";
  case COLOR_BLUE:
    return "\033[0;34m";
  case COLOR_MAGENTA:
    return "\033[0;35m";
  case COLOR_CYAN:
    return "\033[0;36m";
  case COLOR_RESET:
    return "\033[0m";
  default:
    return "\033[0m"; // Default to reset
  }
}

int colorize(char *s, Color c) {
  if (!s) {
    printf("COLORIZE ERROR: no message provided");
    return 1;
  }

  printf("\n%s%s%s\n", Colorize_get_color_code(c), s,
         Colorize_get_color_code(COLOR_RESET));

  return 0;
}

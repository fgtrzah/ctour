#include "../include/openurl.h"
#include "../include/colorize.h"

void open_url(const char *url) {
  if (!url || !sizeof(url)) {
    colorize("OPEN URL ERROR: no url provided.\n", COLOR_RED);
  }

#ifdef _WIN32
  // Windows
  char command[256];
  sprintf(command, "start %s", url);
  system(command);
#elif __APPLE__
  // macOS
  char command[256];
  sprintf(command, "open %s", url);
  system(command);
#elif __linux__
  // Linux
  char command[256];
  sprintf(command, "xdg-open %s", url);
  system(command);
#else
  fprintf(stderr, "Unsupported platform.\n");
#endif
}

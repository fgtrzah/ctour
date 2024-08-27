#include "../include/extracturlfromrecv.h"

#include <stdlib.h>

char *extract_url(const char *request) {
  char *url = (char *)malloc(sizeof(char));
  const char *method_end = strchr(request, ' ');
  if (method_end == NULL) {
    return "";
  }

  const char *url_start = method_end + 1;
  const char *url_end = strchr(url_start, ' ');
  if (url_end == NULL) {
    return "";
  }

  size_t url_length = url_end - url_start;
  strncpy(url, url_start, url_length);
  url[url_length] = '\0'; // Null-terminate the string
  return url;
}

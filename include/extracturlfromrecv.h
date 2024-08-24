#ifndef EXTRACT_URL_FROM_RECV_H
#define EXTRACT_URL_FROM_RECV_H

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

char *extract_url(const char *request);

#endif // !EXTRACT_URL_FROM_RECV_H

#ifndef C6_WEBGET_H
#define C6_WEBGET_H

#include "c3.tcpintro.h"

void parse_url(char *url, char **hostname, char **port, char **path);
void send_request(SOCKET s, char *hostname, char *port, char *path);
SOCKET connect_to_host(char *hostname, char *port);
int c6_webget_init(int args, char *argv[]);
void test_c6_webget_init(int args, char *argv[]);

#endif // !C6_WEBGET_H

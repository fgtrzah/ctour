#ifndef C7_WEBSERVER_H
#define C7_WEBSERVER_H

#include "c3.tcpintro.h"

#define MAX_REQUEST_SIZE 2047
struct client_info {
  socklen_t address_length;
  struct sockaddr_storage address;
  SOCKET socket;
  char request[MAX_REQUEST_SIZE + 1];
  int received;
  struct client_info *next;
};
static struct client_info *clients = 0;

const char *get_content_type(const char *path);

SOCKET create_socket(const char *host, const char *port);

struct client_info *get_client(SOCKET s);

void drop_client(struct client_info *client);

const char *get_client_address(struct client_info *ci);

fd_set wait_on_clients(SOCKET server);

void send_400(struct client_info *client);

void send_404(struct client_info *client);

void serve_resource(struct client_info *client, const char *path);

int c7_webserver_init(int argc, char *argv[]);

void test_c7_webserver_init(int argc, char *argv[]);

#endif // !C7_WEBSERVER_H

#include "../include/c4.udprecvfrom.h"
#include "../include/colorize.h"
#include "../include/computemd5.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_ARG_LEN 100

int c4_udprecvfrom(int argc, char *argv[]) {
#if defined(_WIN32)
  WSADATA d;
  if (WSAStartup(MAKEWORD(2, 2), &d)) {
    fprintf(stderr, "Failed to initialize.\n");
    return 1;
  }
#endif

  // configure local address
  colorize("configuring local address...\n", COLOR_GREEN);
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = AI_PASSIVE;
  struct addrinfo *bind_address;
  int addrinfo = getaddrinfo(0, "8080", &hints, &bind_address);
  printf("addrinfo: (%d)\n", addrinfo);

  if (addrinfo < 0) {
    fprintf(stderr, "misconfigured options for getaddrinfo %d\n",
            GETSOCKETERRNO());
    return 1;
  }

  // create socket
  colorize("creating socket...\n", COLOR_GREEN);
  SOCKET socket_listen;
  socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                         bind_address->ai_protocol);
  if (!ISVALIDSOCKET(socket_listen)) {
    fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
  }

  // bind newly created socket
  colorize("binding socket to local address...\n", COLOR_GREEN);
  if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
    fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
  }

  freeaddrinfo(bind_address);

  // configure udp client data receiver (separate from tcp listen / accept)
  struct sockaddr_storage client_address;
  socklen_t client_len = sizeof(client_address);
  char read[1024];
  int bytes_received =
      recvfrom(socket_listen, read, 1024, 0, (struct sockaddr *)&client_address,
               &client_len);
  printf("received (%d bytes): %.*s\n", bytes_received, bytes_received, read);
  printf("remote address is: ");
  char address_buffer[100];
  char service_buffer[100];
  getnameinfo(((struct sockaddr *)&client_address), client_len, address_buffer,
              sizeof(address_buffer), service_buffer, sizeof(service_buffer),
              NI_NUMERICHOST | NI_NUMERICSERV);
  char report_buffer[100];
  sprintf(report_buffer, "%s %s\n", address_buffer, service_buffer);
  colorize(report_buffer, COLOR_MAGENTA);

  CLOSESOCKET(socket_listen);

#if defined(_WIN32)
  WSACleanup();
#endif

  printf("finished\n");

  return 0;
}

void test_c4_udprecvfrom(
    int argc, char *argv[]) { // Spawn a separate thread for the server
#if defined(_WIN32)
  WSADATA d;
  if (WSAStartup(MAKEWORD(2, 2), &d)) {
    fprintf(stderr, "Failed to initialize.\n");
    return 1;
  }
#endif

  printf("configuring remote address...\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  struct addrinfo *peer_address;
  if (getaddrinfo("127.0.0.1", "8080", &hints, &peer_address)) {
    fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
    assert(!1);
    return;
  }

  printf("remote address is: ");
  char address_buffer[100];
  char service_buffer[100];
  getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen, address_buffer,
              sizeof(address_buffer), service_buffer, sizeof(service_buffer),
              NI_NUMERICHOST | NI_NUMERICSERV);
  printf("%s %s\n", address_buffer, service_buffer);

  printf("Creating socket...\n");
  SOCKET socket_peer;
  socket_peer = socket(peer_address->ai_family, peer_address->ai_socktype,
                       peer_address->ai_protocol);
  if (!ISVALIDSOCKET(socket_peer)) {
    fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
    assert(!1);
    return;
  }
  char input[MAX_ARGS * (MAX_ARG_LEN + 1)];
  argv[1] = fgets(input, sizeof(input), stdin);
  if (argv[1] == NULL) {
    fprintf(stderr, "Error reading input.\n");
    exit(1);
  }
  char *message = argv[1];
  unsigned char digest[16];
  char hex_string[33];

  MD5(message, digest);
  to_hex_string(digest, hex_string);
  strcat(message, (const char *)hex_string);
  printf("Sending: %s\n", hex_string);
  int bytes_sent = sendto(socket_peer, message, strlen(message), 0,
                          peer_address->ai_addr, peer_address->ai_addrlen);
  printf("Sent %d bytes.\n", bytes_sent);
  freeaddrinfo(peer_address);
  CLOSESOCKET(socket_peer);
#if defined(_WIN32)
  WSACleanup();
#endif
  printf("Finished.\n");
  assert(bytes_sent);
}

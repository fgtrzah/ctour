#include "../include/c3.tcpclient.h"
#include "../include/colorize.h"
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

TCPCRemoteAddress *TCPCRemoteAddress_configure_remote_address() {
  colorize("configuring remote address\n", COLOR_MAGENTA);

  TCPCRemoteAddress *address =
      (TCPCRemoteAddress *)malloc(sizeof(TCPCRemoteAddress));
  address->hints = *(struct addrinfo *)malloc(sizeof(struct addrinfo));
  address->peer_address = (struct addrinfo *)malloc(sizeof(struct addrinfo));
  memset(&address->hints, 0, sizeof(address->hints));
  address->hints.ai_socktype = SOCK_STREAM;
  return address;
}

int tcpclient_init(int argc, char *argv[]) {
#if defined(_WIN32)
  WSADATA d;
  if (WSAStartup(MAKEWORD(2, 2), &d)) {
    fprintf(stderr, "Failed to initialize.\n");
    return 1;
  }
#endif
  if (argc < 2) {
    fprintf(stderr, "usage: tcp_client hostname port\n");
    return 1;
  } else {
    printf("address, port: %s, %s", argv[1], argv[2]);
  }

  TCPCRemoteAddress *a = TCPCRemoteAddress_configure_remote_address();

  // remote address config validation + logging
  if (getaddrinfo(argv[1], argv[2], &a->hints, &a->peer_address)) {
    char b[100];
    sprintf(b, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
    colorize(b, COLOR_RED);
    return 1;
  }

  char address_buffer[100];
  char service_buffer[100];
  getnameinfo(a->peer_address->ai_addr, a->peer_address->ai_addrlen,
              address_buffer, sizeof(address_buffer), service_buffer,
              sizeof(service_buffer), NI_NUMERICHOST);

  printf("remote address metadata: %s, %s\n", address_buffer, service_buffer);

  // socket creation + validation
  printf("creating socket...\n");
  SOCKET socket_peer;
  socket_peer = socket(a->peer_address->ai_family, a->peer_address->ai_socktype,
                       a->peer_address->ai_protocol);

  if (!ISVALIDSOCKET(socket_peer)) {
    char e_buffer[100];
    sprintf(e_buffer, "socket creation (i.e. socket()) failed %d\n",
            GETSOCKETERRNO());
    colorize(e_buffer, COLOR_RED);
  }

  // socket connection
  printf("connecting...\n");
  if (connect(socket_peer, a->peer_address->ai_addr,
              a->peer_address->ai_addrlen)) {
    char e_buffer[100];
    sprintf(e_buffer, "connect() failed %d\n", GETSOCKETERRNO());
    colorize(e_buffer, COLOR_RED);
    return 1;
  }

  freeaddrinfo(a->peer_address);

  colorize("connected!", COLOR_GREEN);
  printf("to send data, enter message followed by return key\n");

  while (1) {

    fd_set reads;
    FD_ZERO(&reads);
    FD_SET(socket_peer, &reads);
#if !defined(_WIN32)
    FD_SET(0, &reads);
#endif

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;

    if (select(socket_peer + 1, &reads, 0, 0, &timeout) < 0) {
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
    }

    if (FD_ISSET(socket_peer, &reads)) {
      char read[4096];
      int bytes_received = recv(socket_peer, read, 4096, 0);
      if (bytes_received < 1) {
        printf("Connection closed by peer.\n");
        break;
      }

      printf("Received (%d bytes): %.*s", bytes_received, bytes_received, read);
    }

#if defined(_WIN32)
    if (_kbhit()) {
#else
    if (FD_ISSET(0, &reads)) {
#endif
      char read[4096];
      if (!fgets(read, 4096, stdin))
        break;
      printf("Sending: %s", read);
      int bytes_sent = send(socket_peer, read, strlen(read), 0);
      printf("Sent %d bytes.\n", bytes_sent);
    }
  } // end while(1)

  printf("Closing socket...\n");
  CLOSESOCKET(socket_peer);

#if defined(_WIN32)
  WSACleanup();
#endif

  printf("Finished.\n");
  return 0;
}

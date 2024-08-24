#include "../include/c3.tcpintro.h"
#include "../include/computemd5.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int toupperref() {

#if defined(_WIN32)
  WSADATA d;
  if (WSAStartup(MAKEWORD(2, 2), &d)) {
    fprintf(stderr, "Failed to initialize.\n");
    return 1;
  }
#endif

  printf("Configuring local address...\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;
  int addrinfo = getaddrinfo(0, "8081", &hints, &bind_address);
  printf("%d\n", addrinfo);

  printf("Creating socket...\n");
  SOCKET socket_listen;
  socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
                         bind_address->ai_protocol);
  if (!ISVALIDSOCKET(socket_listen)) {
    fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
  }

  printf("Binding socket to local address...\n");
  if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
    fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
  }
  freeaddrinfo(bind_address);

  printf("Listening...\n");
  if (listen(socket_listen, 10) < 0) {
    fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
    return 1;
  }

  fd_set master;
  FD_ZERO(&master);
  FD_SET(socket_listen, &master);
  SOCKET max_socket = socket_listen;

  printf("Waiting for connections...\n");
  int convocap = 4;

  while (1) {
    if (convocap > 4) {
      break;
    }
    fd_set reads;
    reads = master;
    if (select(max_socket + 1, &reads, 0, 0, 0) < 0) {
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
      return 1;
    }

    SOCKET i;
    for (i = 1; i <= max_socket; ++i) {
      if (FD_ISSET(i, &reads)) {

        if (i == socket_listen) {
          struct sockaddr_storage client_address;
          socklen_t client_len = sizeof(client_address);
          SOCKET socket_client = accept(
              socket_listen, (struct sockaddr *)&client_address, &client_len);
          if (!ISVALIDSOCKET(socket_client)) {
            fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
          }

          FD_SET(socket_client, &master);
          if (socket_client > max_socket)
            max_socket = socket_client;

          char address_buffer[100];
          getnameinfo((struct sockaddr *)&client_address, client_len,
                      address_buffer, sizeof(address_buffer), 0, 0,
                      NI_NUMERICHOST);
          printf("New connection from %s\n", address_buffer);
        } else {
          if (convocap > 4) {
            FD_CLR(i, &master);
            CLOSESOCKET(i);
            CLOSESOCKET(socket_listen);
            exit(0);
            break;
          }
          char read[1024];
          int bytes_received = recv(i, read, 1024, 0);
          if (bytes_received < 1) {
            FD_CLR(i, &master);
            CLOSESOCKET(i);
            continue;
          }

          int j;
          for (j = 0; j < bytes_received; ++j)
            read[j] = toupper(read[j]);
          unsigned char digest[16];
          char hex_string[33];

          MD5(read, digest);
          to_hex_string(digest, hex_string);
          printf("%s\n", hex_string);

          send(i, hex_string, bytes_received, 0);
          convocap += 1;
        }

      } // if FD_ISSET
    } // for i to max_socket
  } // while(1)

  printf("Closing listening socket...\n");
  CLOSESOCKET(socket_listen);

#if defined(_WIN32)
  WSACleanup();
#endif

  printf("Finished.\n");

  return 0;
}

void test_toupperref() { assert(!toupperref()); }

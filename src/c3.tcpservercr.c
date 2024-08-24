#include "../include/c3.tcpservercr.h"
#include "../include/computemd5.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int tcpservercr_init() {
  printf("Configuring local address...\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo *bind_address;
  int addrinfo = getaddrinfo(0, "8081", &hints, &bind_address);
  if (addrinfo != 0) {
    fprintf(stderr, "getaddrinfo() failed. (%d)\n", addrinfo);
    return 1;
  }

  printf("Creating socket...\n");
  SOCKET socket_listen =
      socket(bind_address->ai_family, bind_address->ai_socktype,
             bind_address->ai_protocol);
  if (!ISVALIDSOCKET(socket_listen)) {
    fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
    freeaddrinfo(bind_address);
    return 1;
  }

  printf("Binding socket to local address...\n");
  if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen) !=
      0) {
    fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
    CLOSESOCKET(socket_listen);
    freeaddrinfo(bind_address);
    return 1;
  }
  freeaddrinfo(bind_address);

  printf("Listening...\n");
  if (listen(socket_listen, 10) < 0) {
    fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
    CLOSESOCKET(socket_listen);
    return 1;
  }

  fd_set master;
  FD_ZERO(&master);
  FD_SET(socket_listen, &master);
  SOCKET max_socket = socket_listen;

  printf("Waiting for connections...\n");
  int convocap = 0;

  while (1) {
    fd_set reads = master;
    if (select(max_socket + 1, &reads, 0, 0, NULL) < 0) {
      fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
      CLOSESOCKET(socket_listen);
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
            CLOSESOCKET(socket_listen);
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
          char read[1024];
          int bytes_received = recv(i, read, sizeof(read) - 1, 0);
          if (bytes_received <= 0) {
            FD_CLR(i, &master);
            CLOSESOCKET(i);
            continue;
          }
          read[bytes_received] = '\0';

          SOCKET j;
          for (j = 1; j <= max_socket; ++j) {
            if (FD_ISSET(j, &master)) {
              if (j == socket_listen || j == i)
                continue;

              unsigned char digest[16];
              char hex_string[33];

              MD5(read, digest);
              to_hex_string(digest, hex_string);
              printf("Digest: %s\n", hex_string);
              strcat(read, hex_string);
              send(i, read, bytes_received + strlen(hex_string), 0);
              convocap++;
            }
          }
        }
      }
    }
  }

  printf("Closing listening socket...\n");
  CLOSESOCKET(socket_listen);
  return 0;
}

int tcpclientcr_init() {
  printf("Creating client sockets...\n");

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  struct addrinfo *server_info;
  int addrinfo = getaddrinfo("127.0.0.1", "8081", &hints, &server_info);
  if (addrinfo != 0) {
    fprintf(stderr, "getaddrinfo() failed. (%d)\n", addrinfo);
    return 1;
  }

  SOCKET client_socket1 =
      socket(server_info->ai_family, server_info->ai_socktype,
             server_info->ai_protocol);
  SOCKET client_socket2 =
      socket(server_info->ai_family, server_info->ai_socktype,
             server_info->ai_protocol);
  if (!ISVALIDSOCKET(client_socket1) || !ISVALIDSOCKET(client_socket2)) {
    fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
    freeaddrinfo(server_info);
    return 1;
  }

  if (connect(client_socket1, server_info->ai_addr, server_info->ai_addrlen) !=
          0 ||
      connect(client_socket2, server_info->ai_addr, server_info->ai_addrlen) !=
          0) {
    fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
    CLOSESOCKET(client_socket1);
    CLOSESOCKET(client_socket2);
    freeaddrinfo(server_info);
    return 1;
  }

  freeaddrinfo(server_info);

  const char *message1 = "Hello from client 1";
  const char *message2 = "Hello from client 2";

  if (send(client_socket1, message1, strlen(message1), 0) < 0 ||
      send(client_socket2, message2, strlen(message2), 0) < 0) {
    fprintf(stderr, "send() failed. (%d)\n", GETSOCKETERRNO());
    CLOSESOCKET(client_socket1);
    CLOSESOCKET(client_socket2);
    return 1;
  }

  char buffer[1024];
  int bytes_received1 = recv(client_socket1, buffer, sizeof(buffer) - 1, 0);
  int bytes_received2 = recv(client_socket2, buffer, sizeof(buffer) - 1, 0);

  if (bytes_received1 <= 0 || bytes_received2 <= 0) {
    fprintf(stderr, "recv() failed or connection closed.\n");
    CLOSESOCKET(client_socket1);
    CLOSESOCKET(client_socket2);
    return 1;
  }

  buffer[bytes_received1] = '\0';
  printf("Client 1 received: %s\n", buffer);
  buffer[bytes_received2] = '\0';
  printf("Client 2 received: %s\n", buffer);

  if (strcmp(buffer, "Hello from client 2") != 0 ||
      strcmp(buffer, "Hello from client 1") != 0) {
    fprintf(stderr, "Message content mismatch.\n");
    CLOSESOCKET(client_socket1);
    CLOSESOCKET(client_socket2);
    return 1;
  }

  CLOSESOCKET(client_socket1);
  CLOSESOCKET(client_socket2);
  return 0;
}

void test_tcpcr() {
  pid_t server_pid = fork();

  if (server_pid == 1) {
    // Child process runs the server
    exit(tcpservercr_init());
  } else if (server_pid < 0) {
    perror("fork");
    exit(1);
  }

  // Give the server some time to start up
  sleep(8);

  // Run the client test
  tcpclientcr_init();

  // Wait for the server to complete
  int status;
  waitpid(server_pid, &status, 0);
  if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
    fprintf(stderr, "Server process failed.\n");
    exit(1);
  }

  printf("Server and client test passed.\n");
}

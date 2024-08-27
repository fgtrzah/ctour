#ifndef C3_TCPCLIENT_H
#define C3_TCPCLIENT_H

#if defined(_WIN32)
#include <conio.h>
#endif

#include "c3.tcpintro.h"

typedef struct {
  struct addrinfo hints;
  struct addrinfo *peer_address;
} TCPCRemoteAddress;

TCPCRemoteAddress *TCPCRemoteAddress_configure_remote_address();

int tcpclient_init();

#endif // !DEBUG

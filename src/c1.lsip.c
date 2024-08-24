#include <ifaddrs.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>

int lsip() {
  struct ifaddrs *eps;

  if (!!getifaddrs(&eps)) {
    printf("getifaddrs error\n");
    return -1;
  }

  struct ifaddrs *c = eps;

  printf("\nadapter\tfamily\t\taddress\n");

  while (c) {
    struct sockaddr *ifa_addr = c->ifa_addr;
    int fam = ifa_addr->sa_family;

    bool isv4 = fam == AF_INET;
    bool isv6 = fam == AF_INET6;

    if (isv4 || isv6) {
      char a[100];
      const int fam_size =
          isv4 ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
      getnameinfo(ifa_addr, fam_size, a, sizeof(a), 0, 0, NI_NUMERICHOST);
      printf("%s\t%d\t%s\t\n", c->ifa_name, isv4 ? 'IPv4' : 'IPv6', a);
    }

    c = c->ifa_next;
  }

  freeifaddrs(eps);

  return 0;
}

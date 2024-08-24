#ifndef C5_DNSUTILS_H
#define C5_DNSUTILS_H

#include "c3.tcpintro.h"

const unsigned char *c5_report_name(const unsigned char *msg,
                                    const unsigned char *p,
                                    const unsigned char *end);

void c5_print_dns_message(const char *message, int msg_length);

int c5_dnsutils_init(int argc, char *argv[]);

void test_c5_dnsutils(int argc, char *argv[]);

#endif // !C5_DNSUTILS_H

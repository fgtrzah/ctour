#ifndef COMPUTE_MD5_H
#define COMPUTE_MD5_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Define MD5 constants
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

// Basic MD5 functions
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// Rounds
#define FF(a, b, c, d, x, s, ac)                                               \
  {                                                                            \
    (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac);                            \
    (a) = ROTATE_LEFT((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define GG(a, b, c, d, x, s, ac)                                               \
  {                                                                            \
    (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac);                            \
    (a) = ROTATE_LEFT((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define HH(a, b, c, d, x, s, ac)                                               \
  {                                                                            \
    (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac);                            \
    (a) = ROTATE_LEFT((a), (s));                                               \
    (a) += (b);                                                                \
  }
#define II(a, b, c, d, x, s, ac)                                               \
  {                                                                            \
    (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac);                            \
    (a) = ROTATE_LEFT((a), (s));                                               \
    (a) += (b);                                                                \
  }

// MD5 context structure
typedef struct {
  uint32_t state[4];
  uint32_t count[2];
  unsigned char buffer[64];
} MD5_CTX;

void Encode(unsigned char *output, const uint32_t *input, size_t len);
void Decode(uint32_t *output, const unsigned char *input, size_t len);
void MD5Transform(uint32_t state[4], const unsigned char block[64]);
void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, const unsigned char *input, size_t inputLen);
void MD5Final(unsigned char digest[16], MD5_CTX *context);
void MD5(const char *str, unsigned char digest[16]);
void to_hex_string(unsigned char digest[16], char hex_string[33]);

#endif // !DEBUG

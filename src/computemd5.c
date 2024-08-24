#include "../include/computemd5.h"
#include <stdio.h>
#include <string.h>

static const unsigned char PADDING[64] = {0x80};

static const uint32_t S[64] = {S11, S12, S13, S14, S21, S22, S23, S24,
                               S31, S32, S33, S34, S41, S42, S43, S44};

static const uint32_t K[100] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf75f37d4, 0x1d0f6000, 0x4d2d12e7, 0x07a34b1e, 0x0e134240, 0x0349b480,
    0x01e09e1e, 0x0b62b012};

void Encode(unsigned char *output, const uint32_t *input, size_t len) {
  size_t i, j;
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

void Decode(uint32_t *output, const unsigned char *input, size_t len) {
  size_t i, j;
  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
                (((uint32_t)input[j + 2]) << 16) |
                (((uint32_t)input[j + 3]) << 24);
  }
}

void MD5Transform(uint32_t state[4], const unsigned char block[64]) {
  uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
  uint32_t x[16];
  Decode(x, block, 64);

  // Round 1
  FF(a, b, c, d, x[0], S11, K[0]);
  FF(d, a, b, c, x[1], S12, K[1]);
  FF(c, d, a, b, x[2], S13, K[2]);
  FF(b, c, d, a, x[3], S14, K[3]);
  FF(a, b, c, d, x[4], S11, K[4]);
  FF(d, a, b, c, x[5], S12, K[5]);
  FF(c, d, a, b, x[6], S13, K[6]);
  FF(b, c, d, a, x[7], S14, K[7]);
  FF(a, b, c, d, x[8], S11, K[8]);
  FF(d, a, b, c, x[9], S12, K[9]);
  FF(c, d, a, b, x[10], S13, K[10]);
  FF(b, c, d, a, x[11], S14, K[11]);
  FF(a, b, c, d, x[12], S11, K[12]);
  FF(d, a, b, c, x[13], S12, K[13]);
  FF(c, d, a, b, x[14], S13, K[14]);
  FF(b, c, d, a, x[15], S14, K[15]);

  // Round 2
  GG(a, b, c, d, x[1], S21, K[16]);
  GG(d, a, b, c, x[6], S22, K[17]);
  GG(c, d, a, b, x[11], S23, K[18]);
  GG(b, c, d, a, x[0], S24, K[19]);
  GG(a, b, c, d, x[5], S21, K[20]);
  GG(d, a, b, c, x[10], S22, K[21]);
  GG(c, d, a, b, x[15], S23, K[22]);
  GG(b, c, d, a, x[4], S24, K[23]);
  GG(a, b, c, d, x[9], S21, K[24]);
  GG(d, a, b, c, x[14], S22, K[25]);
  GG(c, d, a, b, x[3], S23, K[26]);
  GG(b, c, d, a, x[8], S24, K[27]);
  GG(a, b, c, d, x[13], S21, K[28]);
  GG(d, a, b, c, x[2], S22, K[29]);
  GG(c, d, a, b, x[7], S23, K[30]);
  GG(b, c, d, a, x[12], S24, K[31]);

  // Round 3
  HH(a, b, c, d, x[5], S31, K[32]);
  HH(d, a, b, c, x[8], S32, K[33]);
  HH(c, d, a, b, x[11], S33, K[34]);
  HH(b, c, d, a, x[14], S34, K[35]);
  HH(a, b, c, d, x[1], S31, K[36]);
  HH(d, a, b, c, x[4], S32, K[37]);
  HH(c, d, a, b, x[7], S33, K[38]);
  HH(b, c, d, a, x[10], S34, K[39]);
  HH(a, b, c, d, x[13], S31, K[40]);
  HH(d, a, b, c, x[0], S32, K[41]);
  HH(c, d, a, b, x[3], S33, K[42]);
  HH(b, c, d, a, x[6], S34, K[43]);
  HH(a, b, c, d, x[9], S31, K[44]);
  HH(d, a, b, c, x[12], S32, K[45]);
  HH(c, d, a, b, x[15], S33, K[46]);
  HH(b, c, d, a, x[2], S34, K[47]);

  // Round 4
  II(a, b, c, d, x[0], S41, K[48]);
  II(d, a, b, c, x[7], S42, K[49]);
  II(c, d, a, b, x[14], S43, K[50]);
  II(b, c, d, a, x[5], S44, K[51]);
  II(a, b, c, d, x[12], S41, K[52]);
  II(d, a, b, c, x[3], S42, K[53]);
  II(c, d, a, b, x[10], S43, K[54]);
  II(b, c, d, a, x[1], S44, K[55]);
  II(a, b, c, d, x[8], S41, K[56]);
  II(d, a, b, c, x[15], S42, K[57]);
  II(c, d, a, b, x[6], S43, K[58]);
  II(b, c, d, a, x[13], S44, K[59]);
  II(a, b, c, d, x[4], S41, K[60]);
  II(d, a, b, c, x[11], S42, K[61]);
  II(c, d, a, b, x[2], S43, K[62]);
  II(b, c, d, a, x[9], S44, K[63]);

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
}

void MD5Init(MD5_CTX *context) {
  context->count[0] = context->count[1] = 0;
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

void MD5Update(MD5_CTX *context, const unsigned char *input, size_t inputLen) {
  size_t i, index, partLen;

  index = (size_t)((context->count[0] >> 3) & 0x3F);
  partLen = 64 - index;

  context->count[0] += (uint32_t)(inputLen << 3);
  if (context->count[0] < (inputLen << 3)) {
    context->count[1]++;
  }
  context->count[1] += (uint32_t)(inputLen >> 29);

  if (inputLen >= partLen) {
    memcpy(&context->buffer[index], input, partLen);
    MD5Transform(context->state, context->buffer);

    for (i = partLen; i + 63 < inputLen; i += 64) {
      MD5Transform(context->state, &input[i]);
    }

    index = 0;
  } else {
    i = 0;
  }

  memcpy(&context->buffer[index], &input[i], inputLen - i);
}

void MD5Final(unsigned char digest[16], MD5_CTX *context) {
  unsigned char bits[8];
  uint32_t index, padLen;

  Encode(bits, context->count, 8);

  index = (size_t)((context->count[0] >> 3) & 0x3F);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  MD5Update(context, PADDING, padLen);

  MD5Update(context, bits, 8);

  Encode(digest, context->state, 16);
}

void MD5(const char *str, unsigned char digest[16]) {
  MD5_CTX context;
  MD5Init(&context);
  MD5Update(&context, (const unsigned char *)str, strlen(str));
  MD5Final(digest, &context);
}

// Helper function to convert the MD5 result to a hexadecimal string
void to_hex_string(unsigned char digest[16], char hex_string[33]) {
  for (int i = 0; i < 16; ++i) {
    sprintf(&hex_string[i * 2], "%02x", digest[i]);
  }
  hex_string[32] = '\0';
}

void digest_to_string(unsigned char digest[16], char *output) {
  for (int i = 0; i < 16; i++) {
    sprintf(&output[i * 2], "%02x", digest[i]);
  }
  output[32] = '\0';
}

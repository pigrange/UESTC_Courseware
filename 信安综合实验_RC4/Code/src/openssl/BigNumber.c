#include <openssl/bn.h>
#include <stdio.h>
#include <string.h>

int bn2bin(BIGNUM* bn);
BIGNUM* bin2bn(unsigned char* s);
void intToBits(int value);

int main() {
  BIGNUM* dynamic_bn = BN_new();
  int num = 123;
  printf("%d to bits is ", num);
  intToBits(num);
  printf("\n");
  BN_set_word(dynamic_bn, num);
  bn2bin(dynamic_bn);
  return 0;
}

int bn2bin(BIGNUM* bn) {
  printf("\n");
  int len = BN_num_bytes(bn);
  unsigned char* s = (unsigned char*)malloc(sizeof(unsigned char) * (len + 1));
  len = BN_bn2bin(bn, s);
  for (int i = 0; i < len; i++) {
    intToBits(s[i]);
  }
}

BIGNUM* bin2bn(unsigned char* s) {
  BIGNUM* bn = BN_new();
  int len = strlen((char*)s);
  BN_bin2bn(s, len, bn);
  BN_print_fp(stdout, bn);
  return bn;
}

void intToBits(int value) {
  unsigned char* results = (unsigned char*)malloc(sizeof(unsigned char) * 32);
  int i = 0;
  while (value > 0) {
    int bit = value & 1;
    value = value >> 1;
    unsigned char t = bit == 1 ? '1' : '0';
    results[31 - i] = t;
    i++;
  }
  for (int pos = 32 - i; pos < 32; pos++) {
    printf("%c", results[pos]);
  }
}

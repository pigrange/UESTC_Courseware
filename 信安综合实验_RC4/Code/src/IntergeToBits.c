#include <stdio.h>
#include <stdlib.h>

unsigned char *integerToBits(int value, int *length) {
  unsigned char *results = (unsigned char *)malloc(sizeof(unsigned char) * 32);
  int i = 0;
  while (value > 0) {
    int bit = value & 1;
    value = value >> 1;
    unsigned char t = bit == 1 ? '1' : '0';
    results[31 - i] = t;
    i++;
  }
  *length = i;
  return &results[32 - i];
}

int bitsToInteger(unsigned char *bitStr, int length) {
  int i = length;
  int result = 0;
  int base = 1;
  //注意这里的i的取值,先就会跑一次i--,所以实际上是从len-1开始的
  while (i-- > 0) {
    result += (bitStr[i] - '0') * base;
    base *= 2;
  }
  printf("\n %d", result);
}

int main(int argc, char const *argv[]) {
  int *len = (int *)malloc(sizeof(int));
  unsigned char *results = integerToBits(43, len);
  for (int i = 0; i < *len; i++) {
    printf("%c", results[i]);
  }
  bitsToInteger(results, *len);
  return 0;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MOD_LSB 0
#define MOD_OPB 1
#define MOD_EPB 2

int BBS_MOD = MOD_LSB;

int RAND_COUNT = 1;
long RandLCG(long x0, long m, long a, long c) {
  long i = 0;
  long result = x0;
  while (i++ < RAND_COUNT) {
    result = (result * a + c) % m;
  }
  RAND_COUNT++;
  return result;
}

long *RandLCGS(long x0, long m, long a, long c, long n) {
  long i = 0;
  long *results = (long *)malloc(sizeof(long) * n);
  long temp = x0;
  while (i++ < n) {
    temp = (temp * a + c) % m;
    results[i] = temp;
  }
  return results;
}

long RandBBS(long s, long p, long q, int n) {
  long m = p * q;
  int i = 0, temp, bit, result = 0, x = s;
  while (i++ < n) {
    temp = (x * x) % m;
    x = temp;
    switch (BBS_MOD) {
      case MOD_LSB:
        bit = temp & 1;
        break;
      case MOD_EPB:
        bit = 0;
        for (; temp != 0; temp /= 2) bit = bit ^ (temp & 1);
        break;
      case MOD_OPB:
        bit = 1;
        for (; temp != 0; temp /= 2) bit = bit ^ (temp & 1);
        break;
      default:
        break;
    }
    result = result << 1 + bit;
  }
  return result;
}

int main() {
  printf("%ld", RandBBS(3, 11, 19, 5));
  return 0;
}

#include <stdio.h>

int euclid(int num, int mod) {
  int big = mod;
  int small = num;
  int x1 = 1, y1 = 0, x2 = 0, y2 = 1, x, y, temp;
  while (big % small != 0) {
    x = x2, y = y2;
    x2 = x1 - big / small * x2;
    y2 = y1 - big / small * y2;
    x1 = x;
    y1 = y;
    temp = big % small;
    big = small;
    small = temp;
  }
  printf("%d * %d + %d * %d = %d \n", x2, mod, y2, num, small);
  return y2;
}

int main() {
  int result = euclid(7, 96);
  printf("%d", result);
  return 0;
}
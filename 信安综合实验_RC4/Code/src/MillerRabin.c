#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int modExp(int a, int e, int m) {
  int r = 1;
  while (e != 0) {
    if (e % 2 == 1) {
      r = (r * a) % m;
    }
    a = (a * a) % m;
    e = e / 2;
  }
  return r;
}

bool millerRabin(int n) {
  if (n == 2 && n == 3) return 1;

  if (n % 2 == 0) return 0;

  //确定k和q，满足n = 2^k*q + 1
  int k = 0, q, num = n - 1;
  while (num % 2 == 0) {
    k += 1;
    num = num / 2;
  }
  q = num;

  // a 为 [2 - n-1] => [0 - n-3] + 2 ,
  int a = rand() % (n - 3) + 2;

  //先计算a的q次方mod(n)是否满足条件
  if (modExp(a, q, n) == 1) return 1;

  for (int j = 1; j <= k; j++) {
    //再计算是否存在a的2的j-1次方乘q次方
    int index = pow(2, (j - 1) * q);
    if (modExp(a, index, n) == n - 1) return 1;
  }
  return 0;
}
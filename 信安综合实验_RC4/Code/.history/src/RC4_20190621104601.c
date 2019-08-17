#include <stdio.h>
#include <stdlib.h>

int* KSA(int* K, int s) {
  int* S = (int*)malloc(sizeof(int) * s);
  //初始化S
  for (int i = 0; i < s; S[i++] = i - 1)
    ;

  int i = -1, j = 0, temp;
  int klen = sizeof(K) / 4;
  while (i++ < s) {
    j = (j + S[i] + K[i % klen]) % s;
    temp = S[i];
    S[i] = S[j];
    S[j] = temp;
  }
  return S;
}

int* PRNG(int* M, int mlen, int* S, int slen) {
  int* T = (int*)malloc(sizeof(int) * mlen);
  int i = 0, j = 0;
  int k = 0;
  while (k++ < mlen) {
    //生成i和j
    i = (i + 1) % slen;
    j = (j + S[i]) % slen;
    //交换S[i] 和 S[j]的值
    int temp = S[i];
    S[i] = S[j];
    S[j] = temp;
    //生成T[k],
    T[k] = S[(S[i] + S[j]) % slen];
    M[k] = M[k] ^ T[k];
  }
  return M;
}

int main(int argc, char const* argv[]) {
  int K[3];
  K[0] = 5;
  K[1] = 6;
  K[2] = 7;
  int* results = KSA(K, 8);
  for (int i = 0; i < 8; printf("%d \n", results[i++]))
    ;
  return 0;
}

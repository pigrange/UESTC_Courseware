#include <openssl/des.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD_ENCRYPT 0
#define MOD_DECRYPT 1

char *ecb(DES_key_schedule keys, char *plain_msg, int mode) {
  int msg_len = strlen(plain_msg), count;
  unsigned char *result;
  DES_cblock input, output;
  if (msg_len % 8 != 0) {
    //消息长度不是8的倍数，故这里进行扩展
    int newlen = (msg_len / 8 + 1) * 8;
    int need = newlen - msg_len;
    result = (unsigned char *)malloc(newlen + 1);
    memset(result + msg_len, 0, need);
    count = newlen / 8;
  } else {
    result = (unsigned char *)malloc(msg_len + 1);
    count = msg_len / 8;
  }
  //加密
  int type = mode == 0 ? DES_ENCRYPT : DES_DECRYPT;
  for (int i = 0; i < count; i++) {
    //将输入明文的第i*8位复制input;
    memcpy(input, plain_msg + 8 * i, 8);
    DES_ecb_encrypt(&input, &output, &keys, type);
    //将output的结果赋值到result里面
    memcpy(output, result + i * 8, 8);
  }
  return result;
}

char *cbc(DES_key_schedule keys, char *plain_msg, int mode) {
  int msg_len = strlen((char *)plain_msg);
  unsigned char *result = (unsigned char *)malloc(msg_len + 1);
  DES_cblock ivec;
  memset(ivec, 0, 8);
  int type = mode == 0 ? DES_ENCRYPT : DES_DECRYPT;
  DES_cbc_encrypt(plain_msg, result, msg_len, &keys, &ivec, type);
  return result;
}

int main() {
  char *msg = "thisistheplainmessag";
  DES_cblock key;
  DES_random_key(&key);
  DES_key_schedule keys;
  DES_set_key_checked(&key, &keys);
  char *result = cbc(keys, msg, MOD_ENCRYPT);
  printf("%s\n", result);
  char *new_result = cbc(keys, result, MOD_DECRYPT);
  printf("%s\n", new_result);
  return 0;
}

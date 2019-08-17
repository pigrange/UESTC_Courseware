#include <openssl/rsa.h>
#include <stdio.h>
#include <string.h>

unsigned char *encrypt(RSA *rsa, char *msg) {
  int rsa_len = RSA_size(rsa);
  int len = strlen((char *)msg);
  unsigned char *result = (unsigned char *)malloc(rsa_len + 1);
  int result_len =
      RSA_public_encrypt(len, msg, result, rsa, RSA_PKCS1_OAEP_PADDING);
  printf("%s", result);
  printf("\n");
  return result;
}
char *decrypt(RSA *rsa, unsigned char *cipher) {
  int rsa_len = RSA_size(rsa);
  int len = strlen((unsigned char *)cipher);
  char *result = (char *)malloc(rsa_len + 1);
  int result_len =
      RSA_private_decrypt(len, cipher, result, rsa, RSA_PKCS1_OAEP_PADDING);
  printf("%s", result);
  printf("\n");
  return result;
}
int main() {
  RSA *rsa = RSA_generate_key(1024, 3, NULL, NULL);
  //获取密钥
  char *msg = "this is the plain message";

  unsigned char *cipher = encrypt(rsa, msg);
  char *result = decrypt(rsa, cipher);
  return 0;
}

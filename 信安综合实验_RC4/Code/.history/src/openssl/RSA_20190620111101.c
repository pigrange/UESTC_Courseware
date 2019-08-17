#include <stdio.h>
#include <openssl/rsa.h>
#include <string.h>

unsigned char *encrypt(RSA *rsa, char *msg)
{
	int rsa_len = RSA_size(rsa);
	int len = strlen((char *)msg);
	unsigned char *result = (unsigned char *)malloc(rsa_len + 1);
	int result_len = RSA_public_encrypt(len, msg, result, rsa, RSA_PKCS1_OAEP_PADDING);
	for (int i = 0; i < result_len; i++)
	{
		printf("%x", result[i]);
	}
	printf("\n");
	return result;
}
char *decrypt(RSA *rsa, char *msg, int mode)
{
	result_len = RSA_public_decrypt(len, msg, result, rsa, RSA_PKCS1_OAEP_PADDING);
}
int main()
{
	RSA *rsa = RSA_generate_key(1024, 3, NULL, NULL);
	//获取密钥
	char *msg = "this is the plain message";

	unsigned char *cipher = encrypt(rsa, msg, MOD_ENCRYPT);
	char *result = decrypt(rsa, cipher, MOD_DECRYPT);
	return 0;
}

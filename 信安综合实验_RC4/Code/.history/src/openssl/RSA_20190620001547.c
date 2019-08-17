#include <stdio.h>
#include <openssl/rsa.h>
#include <string.h>

#define MOD_ENCRYPT 0
#define MOD_DECRYPT 1

unsigned char *encrypt(RSA *rsa, char *msg, int mode)
{
	int rsa_len = RSA_size(rsa);
	int len = strlen((char *)msg);
	unsigned char *result = (unsigned char *)malloc(rsa_len + 1);
	int result_len;
	switch (mode)
	{
	case MOD_ENCRYPT:
		result_len = RSA_public_encrypt(len, msg, result, rsa, RSA_PKCS1_OAEP_PADDING);
		break;
	case MOD_DECRYPT:
		result_len = RSA_public_decrypt(len, msg, result, rsa, RSA_PKCS1_OAEP_PADDING);
		break;
	default:
		break;
	}
	for (int i = 0; i < result_len; i++)
	{
		printf("%x", result[i]);
	}
	printf("\n");
	return result;
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

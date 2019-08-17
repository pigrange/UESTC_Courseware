#include<stdio.h>
#include<string.h>
#include<openssl/sha.h>
#include<stdlib.h>

unsigned char* hash(char* msg){
	unsigned char hash[20];
	int len = strlen((char*)msg);
	SHA1(msg,len,hash);
	printf("%s",hash);
	return hash;
}

unsigned char* hashLongMsg(char* msg){
	unsigned char hash[20];
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	SHA1_Update(&ctx,msg,strlen(msg));
	SHA1_Final(hash,&ctx);
	printf("%s",hash);
	return hash;
}

int main(){
	char * msg = "this is the message";
	hash(msg);
	printf("\n");
	hashLongMsg(msg);	
	return 0;
}

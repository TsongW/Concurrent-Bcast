#ifndef _SECURE_ALLGATHER_
#define _SECURE_ALLGATHER_


#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/aead.h>
unsigned char ciphertext_sendbuf[1024*1024*16+284];
unsigned char ciphertext_recvbuf[268435456+4000]; // 268435456 = 4MB * 64


unsigned char ciphertext[4194304+18];
//EVP_AEAD_CTX *ctx = NULL;
//unsigned char key [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
//unsigned char nonce[12] = {'1','2','3','4','5','6','7','8','9','0','1','2'};  
int nonceCounter; 




#endif

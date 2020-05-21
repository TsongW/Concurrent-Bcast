#ifndef _SECURE_ALLGATHER_
#define _SECURE_ALLGATHER_


#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/aead.h>
unsigned char ciphertext_sendbuf[4194304*2+20];
unsigned char ciphertext_recvbuf[268435456+4000]; // 268435456 = 4MB * 64


unsigned char ciphertext[4194304+18];

int nonceCounter; 




#endif
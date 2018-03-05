#include <cstring>
#include <iostream>
#include <openssl/blowfish.h>
#include "fscrypt.h"

using namespace std;

void my_encrypt(unsigned char * plain_const, unsigned char * cypher, BF_KEY * key, int length)
{
	unsigned char plain_temp[length];

	//copy the array that is supposed to stay the same into a temp array we can tamper with.
	for(int i = 0 ; i < length ; i++)
		plain_temp[i] = plain_const[i];

	BF_ecb_encrypt(plain_temp, cypher, key, BF_ENCRYPT);
	for(int i = 8; i < length ; i++)
	{
		plain_temp[i] = plain_temp[i] ^ cypher[i-8];
		if(( (i+1) % 8 == 0) && i != 8)
			BF_ecb_encrypt(plain_temp + i-7, cypher + i-7, key, BF_ENCRYPT);
	}
	cout << "DONE ENCRYPTING, RESULTING CYPHERTEXT IS BELOW:" << endl << cypher << endl << endl;
}

void *fs_encrypt(void * plaintext, int bufsize, char *keystr, int *resultlen)
{
	int cypherSize;
	if(bufsize % 8 != 0)
		cypherSize = bufsize + (8 - (bufsize % 8));
	else
		cypherSize = bufsize;

	unsigned char * cypher = new unsigned char[cypherSize];
	BF_KEY key;
	BF_set_key(&key, strlen((char*)keystr), (unsigned char *)keystr);

	my_encrypt(((unsigned char*)plaintext), cypher, &key, cypherSize);
	*resultlen = cypherSize;

	return (void *) cypher;
}

void my_decrypt(unsigned char * cypher, BF_KEY * key, int length, unsigned char * plain_to_return)
{
	unsigned char plain[length];
	BF_ecb_encrypt(cypher, plain, key, BF_DECRYPT);

	for(int i = 0; i < length-8 ; i+=8)
	{
		if( i % 8 == 0)
		{
			BF_ecb_encrypt(cypher + i+8, plain + i+8, key, BF_DECRYPT);
			for(int j = 0; j < 8; j++)
				plain[i+8+j] = plain[i+8+j] ^ cypher[i + j];
		}
	}

	for(int i = 0; i < strlen((char*)plain) ; i++)
		plain_to_return[i] = plain[i];
	cout << "DONE DECRYPTING, RESULTING PLAINTEXT IS BELOW:" << endl << plain << endl << endl;
}

void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen)
{
	int size;
	if(bufsize % 8 != 0)
		size = bufsize + (8 - (bufsize % 8));
	else
		size = bufsize;

	unsigned char cypher[size];
	unsigned char plain[size];
	unsigned char * keystring = new unsigned char[strlen(keystr)];
	for(int i = 0; i < bufsize; i++)
		cypher[i] = ((unsigned char*)ciphertext)[i];
	for(int i = 0; i < strlen(keystr); i++)
		keystring[i] = keystr[i];

	BF_KEY key;
	BF_set_key(&key, strlen((char*)keystring), keystring);
	my_decrypt(cypher, &key, bufsize,  plain);

	*resultlen = strlen((char*)plain)+1;

	return (void*)plain;
}

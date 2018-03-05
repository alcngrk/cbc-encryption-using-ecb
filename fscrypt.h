#include <openssl/blowfish.h>


//
//Helper function of fs_encrypt. Does the main encryption.
//
void my_encrypt(unsigned char * plain, unsigned char * cypher, BF_KEY * key, int length);


//
//Helper function of fs_decrypt. Does the main decryption.
//
void my_decrypt(unsigned char * cypher, BF_KEY * key, int length, unsigned char * plain_to_return);


//
//This exists to set the key before calling my_encrypt also to solve some variable type mismatch problems.
//
void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen);



//
//This exists to set th ekey before calling my_decrypt also to solve some variable type mismatch problems
//
void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen);

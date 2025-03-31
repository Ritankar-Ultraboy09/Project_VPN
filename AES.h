#ifndef AES_H
#define AES_H

#include <openssl/aes.h>

#define AES_KEY_SIZE 256 // AES key size in bits
#define AES_BLOCK_SIZE 16 // AES block size in bytes

// Function declarations
void initialize_aes(const unsigned char *key_data);
int aes_encrypt(const unsigned char *plaintext, unsigned char *ciphertext);
int aes_decrypt(const unsigned char *ciphertext, unsigned char *plaintext);
void generate_aes_key();

#endif // AES_H

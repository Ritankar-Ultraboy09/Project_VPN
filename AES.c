#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>

#define AES_KEY_SIZE 256 // AES key size in bits
#define AES_BLOCK_SIZE 16 // AES block size in bytes

AES_KEY aes_encrypt_key, aes_decrypt_key;
unsigned char aes_key[AES_KEY_SIZE / 8];

// Initialize AES Key
void initialize_aes(const unsigned char *key_data) {
    memcpy(aes_key, key_data, AES_KEY_SIZE / 8);
    AES_set_encrypt_key(aes_key, AES_KEY_SIZE, &aes_encrypt_key);
    AES_set_decrypt_key(aes_key, AES_KEY_SIZE, &aes_decrypt_key);
}

// AES Encryption
int aes_encrypt(const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_ecb_encrypt(plaintext, ciphertext, &aes_encrypt_key, AES_ENCRYPT);
    return 0;
}

// AES Decryption
int aes_decrypt(const unsigned char *ciphertext, unsigned char *plaintext) {
    AES_ecb_encrypt(ciphertext, plaintext, &aes_decrypt_key, AES_DECRYPT);
    return 0;
}

// Generate random AES key
void generate_aes_key() {
    if (!RAND_bytes(aes_key, sizeof(aes_key))) {
        fprintf(stderr, "Error generating random AES key\n");
    }
}


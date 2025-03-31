#include "AES.h"
#include <stdio.h>
#include <string.h>

int main() {
    unsigned char key_data[AES_KEY_SIZE / 8] = "thisisaverysecretkey!"; // Must be 256 bits
    initialize_aes(key_data);

    unsigned char plaintext[AES_BLOCK_SIZE] = "Hello, World123"; // 16 bytes for AES block size
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decryptedtext[AES_BLOCK_SIZE];

    // Encrypt
    aes_encrypt(plaintext, ciphertext);

    // Decrypt
    aes_decrypt(ciphertext, decryptedtext);

    // Display results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < AES_BLOCK_SIZE; i++) printf("%02X", ciphertext[i]);
    printf("\nDecrypted text: %s\n", decryptedtext);

    return 0;
}

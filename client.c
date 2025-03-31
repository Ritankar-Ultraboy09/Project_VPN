#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/aes.h>

#define PORT 1194
#define BUFFER_SIZE 1024

void decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    AES_KEY decrypt_key;
    AES_set_decrypt
    int opt = 1;
    int addrlen = sizeof(address);

    unsigned char key[32] = {0};  // Use a secure key in production
    unsigned char buffer[BUFFER_SIZE] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("Server listening on port %d\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    read(client_fd, buffer, BUFFER_SIZE);

    unsigned char decrypted_text[BUFFER_SIZE];
    decrypt(buffer, key, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text

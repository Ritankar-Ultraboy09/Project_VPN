#include "AES.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "10.0.0.1" // Server IP address
#define PORT 5000            // Port for the client to connect to

int main() {
    int sock;
    struct sockaddr_in server;
    unsigned char key_data[AES_KEY_SIZE / 8] = "thisisaverysecretkey!"; // AES key (256 bits)

    // Initialize AES with the key
    initialize_aes(key_data);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Define server properties
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }
    printf("Connected to server at %s:%d\n", SERVER_IP, PORT);

    // Prepare a message to send
    unsigned char plaintext[AES_BLOCK_SIZE] = "HelloServer123!";
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decrypted_response[AES_BLOCK_SIZE];

    // Encrypt the message
    aes_encrypt(plaintext, ciphertext);

    // Send encrypted message to server
    if (send(sock, ciphertext, sizeof(ciphertext), 0) < 0) {
        perror("Send failed");
        close(sock);
        return 1;
    }
    printf("Encrypted message sent to server\n");

    // Receive encrypted response from server
    unsigned char encrypted_response[AES_BLOCK_SIZE];
    if (recv(sock, encrypted_response, sizeof(encrypted_response), 0) < 0) {
        perror("Receive failed");
        close(sock);
        return 1;
    }

    // Decrypt the response from the server
    aes_decrypt(encrypted_response, decrypted_response);
    printf("Decrypted response from server: %s\n", decrypted_response);

    // Close the socket
    close(sock);
    return 0;
}

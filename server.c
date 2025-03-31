#include "AES.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "10.0.0.1" // Server IP address
#define PORT 5000            // Port for server to bind to

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    unsigned char key_data[AES_KEY_SIZE / 8] = "thisisaverysecretkey!"; // AES key (256 bits)

    // Initialize AES with the key
    initialize_aes(key_data);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }
    printf("Server bound to %s:%d\n", SERVER_IP, PORT);

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }
    printf("Server listening on %s:%d\n", SERVER_IP, PORT);

    // Accept a connection
    client_sock = accept(server_fd, (struct sockaddr *)&client, &client_len);
    if (client_sock < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }
    printf("Connection accepted from client\n");

    // Receive encrypted message from client
    unsigned char encrypted_message[AES_BLOCK_SIZE];
    unsigned char decrypted_message[AES_BLOCK_SIZE];
    if (recv(client_sock, encrypted_message, sizeof(encrypted_message), 0) < 0) {
        perror("Receive failed");
        close(client_sock);
        close(server_fd);
        return 1;
    }

    // Decrypt the received message
    aes_decrypt(encrypted_message, decrypted_message);
    printf("Decrypted message from client: %s\n", decrypted_message);

    // Prepare a response to the client
    unsigned char response[AES_BLOCK_SIZE] = "HelloClient123!";
    unsigned char encrypted_response[AES_BLOCK_SIZE];

    // Encrypt the response message
    aes_encrypt(response, encrypted_response);

    // Send encrypted response back to client
    if (send(client_sock, encrypted_response, sizeof(encrypted_response), 0) < 0) {
        perror("Send failed");
        close(client_sock);
        close(server_fd);
        return 1;
    }
    printf("Encrypted response sent to client\n");

    // Close the sockets
    close(client_sock);
    close(server_fd);
    return 0;
}

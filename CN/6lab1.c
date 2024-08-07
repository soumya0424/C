// server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/aes.h>

#define BUFFER_SIZE 1024
#define KEY_SIZE 16  // AES-128

void handle_errors(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void encrypt(const unsigned char *key, unsigned char *input, unsigned char *output) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, KEY_SIZE * 8, &enc_key);
    AES_encrypt(input, output, &enc_key);
}

void decrypt(const unsigned char *key, unsigned char *input, unsigned char *output) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, KEY_SIZE * 8, &dec_key);
    AES_decrypt(input, output, &dec_key);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    unsigned char buffer[BUFFER_SIZE];
    unsigned char encrypted_buffer[BUFFER_SIZE];
    unsigned char decrypted_buffer[BUFFER_SIZE];
    unsigned char key[KEY_SIZE] = "0123456789abcdef";  // Example key

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handle_errors("Socket creation failed");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_errors("Bind failed");
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        handle_errors("Listen failed");
    }

    printf("Server is listening on port %s...\n", argv[1]);

    // Accept an incoming connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
        handle_errors("Accept failed");
    }

    printf("Connected to client\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        memset(encrypted_buffer, 0, BUFFER_SIZE);
        memset(decrypted_buffer, 0, BUFFER_SIZE);

        // Receive message from client
        int bytes_received = recv(client_fd, encrypted_buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            handle_errors("Receive failed");
        }

        decrypt(key, encrypted_buffer, decrypted_buffer);
        printf("Client: %s\n", decrypted_buffer);

        // Check for close condition
        if (strcmp((char *)decrypted_buffer, "close") == 0) {
            break;
        }

        // Send message back to client
        printf("Server: ");
        fgets((char *)buffer, BUFFER_SIZE, stdin);
        buffer[strcspn((char *)buffer, "\n")] = '\0';  // Remove newline character

        encrypt(key, buffer, encrypted_buffer);
        send(client_fd, encrypted_buffer, BUFFER_SIZE, 0);

        // Check for close condition
        if (strcmp((char *)buffer, "close") == 0) {
            break;
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

// client program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/aes.h>

#define BUFFER_SIZE 1024
#define KEY_SIZE 16  // AES-128

void handle_errors(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void encrypt(const unsigned char *key, unsigned char *input, unsigned char *output) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, KEY_SIZE * 8, &enc_key);
    AES_encrypt(input, output, &enc_key);
}

void decrypt(const unsigned char *key, unsigned char *input, unsigned char *output) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, KEY_SIZE * 8, &dec_key);
    AES_decrypt(input, output, &dec_key);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    unsigned char buffer[BUFFER_SIZE];
    unsigned char encrypted_buffer[BUFFER_SIZE];
    unsigned char decrypted_buffer[BUFFER_SIZE];
    unsigned char key[KEY_SIZE] = "0123456789abcdef";  // Example key

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handle_errors("Socket creation failed");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        handle_errors("Connection failed");
    }

    printf("Connected to server: %s:%s\n", argv[1], argv[2]);

    while (1) {
        printf("Client: ");
        fgets((char *)buffer, BUFFER_SIZE, stdin);
        buffer[strcspn((char *)buffer, "\n")] = '\0';  // Remove newline character

        // Send encrypted message to server
        encrypt(key, buffer, encrypted_buffer);
        send(sockfd, encrypted_buffer, BUFFER_SIZE, 0);

        // Check for close condition
        if (strcmp((char *)buffer, "close") == 0) {
            break;
        }

        // Receive encrypted message from server
        int bytes_received = recv(sockfd, encrypted_buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            handle_errors("Receive failed");
        }

        decrypt(key, encrypted_buffer, decrypted_buffer);
        printf("Server: %s\n", decrypted_buffer);

        // Check for close condition
        if (strcmp((char *)decrypted_buffer, "close") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

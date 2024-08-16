// sender program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Receiver IP> <Receiver Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in receiver_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(atoi(argv[2]));
    receiver_addr.sin_addr.s_addr = inet_addr(argv[1]);

    while (1) {
        printf("Sender: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        // Send message to receiver
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

        // Check for exit condition
        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

// receiver program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Sender IP> <Receiver Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(atoi(argv[2]));
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the receiver address
    if (bind(sockfd, (const struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    addr_len = sizeof(sender_addr);

    while (1) {
        // Receive message from sender
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender_addr, &addr_len);
        buffer[n] = '\0';

        printf("Receiver: %s\n", buffer);

        // Check for exit condition
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Echo the message back to sender
        sendto(sockfd, buffer, n, 0, (struct sockaddr *)&sender_addr, addr_len);
    }

    close(sockfd);
    return 0;
}

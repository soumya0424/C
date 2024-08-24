#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in server_addr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_address);

    char buffer[BUFSIZE];
    socklen_t addr_len = sizeof(server_addr);

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFSIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &server_addr, addr_len);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        memset(buffer, 0, BUFSIZE);
        recvfrom(sockfd, buffer, BUFSIZE, 0, (struct sockaddr *) &server_addr, &addr_len);
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}



// Reciever function


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port = atoi(argv[2]);

    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_address);

    if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFSIZE];
    socklen_t addr_len = sizeof(client_addr);

    while (1) {
        memset(buffer, 0, BUFSIZE);
        recvfrom(sockfd, buffer, BUFSIZE, 0, (struct sockaddr *) &client_addr, &addr_len);
        printf("Received: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        printf("Enter message: ");
        fgets(buffer, BUFSIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &client_addr, addr_len);

        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

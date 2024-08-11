// Go-Back-N Protocol - Client
// client_go_back_n.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 8080
#define MAXLINE 1024
#define WINDOW_SIZE 4

typedef struct {
    int seq_num;
    char data[MAXLINE];
} Frame;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len;
    Frame frame;
    char buffer[MAXLINE];
    int ack;
    int base = 0;
    int next_seq_num = 0;
    bool sent[WINDOW_SIZE] = {false};

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error("Socket creation failed");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        while (next_seq_num < base + WINDOW_SIZE) {
            frame.seq_num = next_seq_num;
            printf("Enter message: ");
            fgets(frame.data, MAXLINE, stdin);
            frame.data[strcspn(frame.data, "\n")] = '\0';

            // Send frame to server
            sendto(sockfd, &frame, sizeof(Frame), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
            printf("Frame sent with sequence number %d\n", frame.seq_num);

            sent[next_seq_num % WINDOW_SIZE] = true;
            next_seq_num++;

            if (strcmp(frame.data, "exit") == 0) {
                break;
            }
        }

        // Wait for acknowledgment
        recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&servaddr, &len);
        printf("Acknowledgment received for sequence number %d\n", ack);

        if (ack >= base) {
            int shift = ack - base + 1;
            base = ack + 1;
            memmove(sent, sent + shift, (WINDOW_SIZE - shift) * sizeof(bool));
            memset(sent + (WINDOW_SIZE - shift), false, shift * sizeof(bool));
        }

        if (strcmp(frame.data, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

// Go-Back-N Protocol - Server
// server_go_back_n.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024
#define WINDOW_SIZE 4

typedef struct {
    int seq_num;
    char data[MAXLINE];
} Frame;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    Frame frame;
    int expected_seq_num = 0;
    int ack;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error("Socket creation failed");
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        error("Bind failed");
    }

    while (1) {
        len = sizeof(cliaddr);
        recvfrom(sockfd, &frame, sizeof(Frame), 0, (struct sockaddr *)&cliaddr, &len);
        printf("Frame received with sequence number %d: %s\n", frame.seq_num, frame.data);

        if (frame.seq_num == expected_seq_num) {
            ack = frame.seq_num;
            expected_seq_num++;
        } else {
            ack = expected_seq_num - 1;
        }

        sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&cliaddr, len);
        printf("Acknowledgment sent for sequence number %d\n", ack);

        if (strcmp(frame.data, "exit") == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

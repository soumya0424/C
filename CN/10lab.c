// client program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define BUFFER_SIZE 4096
#define HEADER_SIZE 20
#define MTU_SIZE 1500

typedef struct {
    int id;
    int flag;
    int offset;
    int header_length;
    int total_length;
    char payload[BUFFER_SIZE];
} Fragment;

int get_mtu_size(const char *interface) {
    int sockfd;
    struct ifreq ifr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, interface, IFNAMSIZ-1);

    if (ioctl(sockfd, SIOCGIFMTU, &ifr) == -1) {
        perror("ioctl");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    return ifr.ifr_mtu;
}

void send_fragment(int sockfd, Fragment *fragment, struct sockaddr_in *server_addr) {
    sendto(sockfd, fragment, sizeof(Fragment), 0, (struct sockaddr *)server_addr, sizeof(*server_addr));
    printf("Sent fragment with ID: %d, Flag: %d, Offset: %d\n", fragment->id, fragment->flag, fragment->offset);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Interface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd, mtu_size, num_fragments, payload_size;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = "This is a large buffer of data that needs to be fragmented and sent to the server.";

    mtu_size = get_mtu_size(argv[3]);
    printf("MTU Size: %d\n", mtu_size);

    if (strlen(buffer) + HEADER_SIZE <= mtu_size) {
        printf("No fragmentation needed.\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("Fragmentation needed.\n");
        payload_size = mtu_size - HEADER_SIZE;
        num_fragments = (strlen(buffer) + payload_size - 1) / payload_size;
        printf("Number of fragments required: %d\n", num_fragments);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    Fragment fragment;
    int id = 1;
    int offset = 0;

    for (int i = 0; i < num_fragments; i++) {
        fragment.id = id;
        fragment.flag = (i == num_fragments - 1) ? 0 : 1;
        fragment.offset = offset;
        fragment.header_length = HEADER_SIZE;
        fragment.total_length = payload_size + HEADER_SIZE;
        strncpy(fragment.payload, buffer + offset, payload_size);

        send_fragment(sockfd, &fragment, &server_addr);

        offset += payload_size;
    }

    close(sockfd);
    return 0;
}

// server program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 4096
#define HEADER_SIZE 20

typedef struct {
    int id;
    int flag;
    int offset;
    int header_length;
    int total_length;
    char payload[BUFFER_SIZE];
} Fragment;

void receive_fragment(int sockfd, Fragment *fragment, struct sockaddr_in *client_addr) {
    socklen_t len = sizeof(*client_addr);
    recvfrom(sockfd, fragment, sizeof(Fragment), 0, (struct sockaddr *)client_addr, &len);
    printf("Received fragment with ID: %d, Flag: %d, Offset: %d\n", fragment->id, fragment->flag, fragment->offset);
}

void reassemble_fragments(Fragment *fragments, int num_fragments, char *buffer) {
    for (int i = 0; i < num_fragments; i++) {
        strncpy(buffer + fragments[i].offset, fragments[i].payload, fragments[i].total_length - HEADER_SIZE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr, client_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    Fragment fragments[10];
    int num_fragments = 0;
    char buffer[BUFFER_SIZE] = {0};

    while (1) {
        Fragment fragment;
        receive_fragment(sockfd, &fragment, &client_addr);
        fragments[num_fragments++] = fragment;

        if (fragment.flag == 0) {
            printf("All fragments received. Reassembling...\n");
            reassemble_fragments(fragments, num_fragments, buffer);
            printf("Assembled data: %s\n", buffer);
            break;
        }
    }

    close(sockfd);
    return 0;
}

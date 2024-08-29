// lab 3 print hello world
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int fd; // socket return type is int, so fd is required

    // Create a socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Check if socket was created successfully
    if (fd == -1) {
        printf("Socket not Created\n");
    } else {
        printf("Socket Created\n");
        printf("Socket FD: %d\n", fd);
    }

    // Environment setup
    struct sockaddr_in x;
    x.sin_family = AF_INET;
    x.sin_port = htons(6000); // Port number
    x.sin_addr.s_addr = inet_addr("127.0.0.1"); // Localhost

    // Bind the socket to the address and port number
    int result = bind(fd, (struct sockaddr*) &x, sizeof(x));
    
    // Check if binding was successful
    if (result == -1) {
        printf("Binding not successful\n");
    } else {
        printf("Binding successful\n");
        printf("Hello, World!\n");
    }

    return 0;
}


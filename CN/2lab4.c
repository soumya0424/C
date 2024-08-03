#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    int num;
    struct pkt packet;

    printf("Enter a number: ");
    scanf("%d", &num);

    packet.ch1 = num & 0xFF;
    packet.ch2[0] = (num >> 8) & 0xFF;
    packet.ch2[1] = (num >> 16) & 0xFF;
    packet.ch3 = (num >> 24) & 0xFF;

    printf("ch1: %d\n", packet.ch1);
    printf("ch2[0]: %d\n", packet.ch2[0]);
    printf("ch2[1]: %d\n", packet.ch2[1]);
    printf("ch3: %d\n", packet.ch3);

    int original_number = packet.ch1 | (packet.ch2[0] << 8) | (packet.ch2[1] << 16) | (packet.ch3 << 24);
    printf("Original number: %d\n", original_number);

    return 0;
}

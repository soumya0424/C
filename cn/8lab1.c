// Packet Structure
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_ADDR_SIZE 16
#define DATA_SIZE 256

typedef struct {
    char src_ip[IP_ADDR_SIZE];
    char dest_ip[IP_ADDR_SIZE];
    char data[DATA_SIZE];
} Packet;

// Routing Within the Same Subnet
// Subnet Function
#include <stdbool.h>

bool is_same_subnet(const char* ip1, const char* ip2, const char* subnet_mask) {
    unsigned int ip1_addr, ip2_addr, mask;

    ip1_addr = inet_addr(ip1);
    ip2_addr = inet_addr(ip2);
    mask = inet_addr(subnet_mask);

    return (ip1_addr & mask) == (ip2_addr & mask);
}

// Sending and Receiving Packets
void send_packet_same_subnet(Packet packet) {
    printf("Sending packet from %s to %s within the same subnet\n", packet.src_ip, packet.dest_ip);
    printf("Data: %s\n", packet.data);
}

int main() {
    Packet packet;
    strcpy(packet.src_ip, "192.168.1.1");
    strcpy(packet.dest_ip, "192.168.1.2");
    strcpy(packet.data, "Hello, this is a packet!");

    char subnet_mask[IP_ADDR_SIZE] = "255.255.255.0";

    if (is_same_subnet(packet.src_ip, packet.dest_ip, subnet_mask)) {
        send_packet_same_subnet(packet);
    } else {
        printf("IPs are not in the same subnet\n");
    }

    return 0;
}

// Routing Across Different Subnets
// Router Function
typedef struct {
    char ip[IP_ADDR_SIZE];
    char next_hop[IP_ADDR_SIZE];
} RoutingTableEntry;

RoutingTableEntry routing_table[] = {
    {"192.168.1.0", "192.168.1.1"},
    {"192.168.2.0", "192.168.2.1"}
};

char* get_next_hop(const char* dest_ip) {
    for (int i = 0; i < sizeof(routing_table) / sizeof(routing_table[0]); i++) {
        if (strstr(dest_ip, routing_table[i].ip) != NULL) {
            return routing_table[i].next_hop;
        }
    }
    return NULL;
}

void send_packet_different_subnets(Packet packet) {
    char* next_hop = get_next_hop(packet.dest_ip);
    if (next_hop) {
        printf("Routing packet from %s to %s via next hop %s\n", packet.src_ip, packet.dest_ip, next_hop);
        printf("Data: %s\n", packet.data);
    } else {
        printf("No route to %s\n", packet.dest_ip);
    }
}

// Main Function for Different Subnets
int main() {
    Packet packet;
    strcpy(packet.src_ip, "192.168.1.1");
    strcpy(packet.dest_ip, "192.168.2.2");
    strcpy(packet.data, "Hello, this is a packet!");

    char subnet_mask[IP_ADDR_SIZE] = "255.255.255.0";

    if (is_same_subnet(packet.src_ip, packet.dest_ip, subnet_mask)) {
        send_packet_same_subnet(packet);
    } else {
        send_packet_different_subnets(packet);
    }

    return 0;
}


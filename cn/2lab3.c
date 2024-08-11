#include <stdio.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    char byte1 = num & 0xFF;
    char byte2 = (num >> 8) & 0xFF;
    char byte3 = (num >> 16) & 0xFF;
    char byte4 = (num >> 24) & 0xFF;

    printf("Byte 1: %d\n", byte1);
    printf("Byte 2: %d\n", byte2);
    printf("Byte 3: %d\n", byte3);
    printf("Byte 4: %d\n", byte4);

    return 0;
}

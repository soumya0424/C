#include <stdio.h>

int main() {
    unsigned int num = 1;
    char *c = (char *)&num;

    if (*c) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    printf("Original number in bytes:\n");
    for (int i = 0; i < sizeof(int); i++) {
        printf("%d ", *((unsigned char *)&number + i));
    }
    printf("\n");

    int converted_number = ((number >> 24) & 0xFF) | ((number << 8) & 0xFF0000) | ((number >> 8) & 0xFF00) | ((number << 24) & 0xFF000000);

    printf("Converted number in bytes:\n");
    for (int i = 0; i < sizeof(int); i++) {
        printf("%d ", *((unsigned char *)&converted_number + i));
    }
    printf("\n");

    return 0;
}

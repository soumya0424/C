#include <stdio.h>
#include <stdlib.h>

// Function to convert a number to binary using recursion
void decimalToBinary(int n, char *binary, int index) {
    if (n > 1) {
        decimalToBinary(n / 2, binary, index - 1);
    }
    binary[index] = (n % 2) ? '1' : '0';
}

// Function to write binary equivalent to output file
void writeBinaryToFile(FILE *outFile, int number) {
    char binary[17]; // 16 bits for the binary number plus one for the null terminator
    for (int i = 0; i < 16; i++) {
        binary[i] = '0';
    }
    binary[16] = '\0';
    decimalToBinary(number, binary, 15);
    fprintf(outFile, "The binary equivalent of %d is %s\n", number, binary);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source file> <destination file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *sourceFile = argv[2];
    char *destinationFile = argv[3];

    FILE *inFile = fopen(sourceFile, "r");
    if (inFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    FILE *outFile = fopen(destinationFile, "w");
    if (outFile == NULL) {
        perror("Error opening destination file");
        fclose(inFile);
        return 1;
    }

    int number;
    for (int i = 0; i < n && fscanf(inFile, "%d", &number) != EOF; i++) {
        writeBinaryToFile(outFile, number);
    }

    fclose(inFile);
    fclose(outFile);

    // Display the contents of the output file
    outFile = fopen(destinationFile, "r");
    if (outFile == NULL) {
        perror("Error opening output file for reading");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), outFile)) {
        printf("%s", line);
    }

    fclose(outFile);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Function to calculate GCD using recursion
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    char *sourceFile = argv[1];
    char *destinationFile = argv[2];

    FILE *inFile = fopen(sourceFile, "r");
    FILE *outFile = fopen(destinationFile, "w");

    if (inFile == NULL || outFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    int a, b;
    while (fscanf(inFile, "%d %d", &a, &b) != EOF) {
        int result = gcd(a, b);
        fprintf(outFile, "The GCD of %d and %d is %d\n", a, b, result);
    }

    fclose(inFile);
    fclose(outFile);

    // Display the contents of the output file
    outFile = fopen(destinationFile, "r");
    if (outFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), outFile)) {
        printf("%s", line);
    }

    fclose(outFile);

    return 0;
}

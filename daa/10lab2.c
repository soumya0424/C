#include <stdio.h>
#include <string.h>

// Function to increment a fitstring
void incrementFitString(char fitstring[], int n) {
    for (int i = 0; i < n; i++) {
        if (fitstring[i] == '0') {
            fitstring[i] = '1';
            break;
        } else {
            fitstring[i] = '0';
        }
    }
}

// Function to decrement a fitstring
void decrementFitString(char fitstring[], int n) {
    for (int i = 0; i < n; i++) {
        if (fitstring[i] == '1') {
            fitstring[i] = '0';
            break;
        } else {
            fitstring[i] = '1';
        }
    }
}

void printFitString(char fitstring[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", fitstring[i]);
    }
    printf("\n");
}

int main() {
    char fitstring[] = "101110"; // Represents F6 + F4 + F3 + F2 = 14
    int n = strlen(fitstring);

    printf("Original fitstring: ");
    printFitString(fitstring, n);

    incrementFitString(fitstring, n);
    printf("After incrementing: ");
    printFitString(fitstring, n);

    decrementFitString(fitstring, n);
    decrementFitString(fitstring, n);
    printf("After decrementing twice: ");
    printFitString(fitstring, n);

    return 0;
}

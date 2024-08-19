#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *bits;
    int size;
    int highOrderOne; // Position of the highest-order 1 bit
} BinaryCounter;

void initializeCounter(BinaryCounter *counter, int n) {
    counter->bits = (int *)malloc(n * sizeof(int));
    counter->size = n;
    counter->highOrderOne = -1;
    for (int i = 0; i < n; i++) {
        counter->bits[i] = 0;
    }
}

void incrementCounter(BinaryCounter *counter) {
    int i = 0;
    while (i < counter->size && counter->bits[i] == 1) {
        counter->bits[i] = 0;
        i++;
    }
    if (i < counter->size) {
        counter->bits[i] = 1;
        counter->highOrderOne = i;
    }
}

void resetCounter(BinaryCounter *counter) {
    for (int i = 0; i <= counter->highOrderOne; i++) {
        counter->bits[i] = 0;
    }
    counter->highOrderOne = -1;
}

void printCounter(BinaryCounter *counter) {
    for (int i = counter->size - 1; i >= 0; i--) {
        printf("%d", counter->bits[i]);
    }
    printf("\n");
}

int main() {
    int n = 8; // Number of bits in the counter
    BinaryCounter counter;
    initializeCounter(&counter, n);

    printf("Initial counter: ");
    printCounter(&counter);

    for (int i = 0; i < 10; i++) {
        incrementCounter(&counter);
        printf("After increment %d: ", i + 1);
        printCounter(&counter);
    }

    resetCounter(&counter);
    printf("After reset: ");
    printCounter(&counter);

    free(counter.bits);
    return 0;
}

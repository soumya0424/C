// Quick Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

int quickComparisons = 0;

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        quickComparisons++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to read data from a file
void readFile(int arr[], int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        exit(1);
    }
    *n = 0;
    while (fscanf(file, "%d", &arr[*n]) != EOF && *n < MAX) {
        (*n)++;
    }
    fclose(file);
}

// Function to write data to a file
void writeFile(int arr[], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Unable to open file %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

int main() {
    int arr[MAX], n;
    clock_t start, end;
    double time_spent;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Quick Sort - Ascending Order\n");
        printf("2. Quick Sort - Descending Order\n");
        printf("3. Quick Sort - Random Order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readFile(arr, &n, "inAsce.dat");
                quickComparisons = 0;
                start = clock();
                quickSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outQuickAsce.dat");
                printf("Quick Sort (Ascending): %d comparisons, time spent = %f seconds\n", quickComparisons, time_spent);
                break;

            case 2:
                readFile(arr, &n, "inDesc.dat");
                quickComparisons = 0;
                start = clock();
                quickSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outQuickDesc.dat");
                printf("Quick Sort (Descending): %d comparisons, time spent = %f seconds\n", quickComparisons, time_spent);
                break;

            case 3:
                readFile(arr, &n, "inRand.dat");
                quickComparisons = 0;
                start = clock();
                quickSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outQuickRand.dat");
                printf("Quick Sort (Random): %d comparisons, time spent = %f seconds\n", quickComparisons, time_spent);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
















// Without file handling

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to take input from the user
void inputArray(int arr[], int *n) {
    printf("Enter the number of elements: ");
    scanf("%d", n);
    if (*n > MAX) {
        printf("Error: Number of elements exceeds the maximum allowed size (%d).\n", MAX);
        exit(1);
    }
    printf("Enter the elements: ");
    for (int i = 0; i < *n; i++) {
        scanf("%d", &arr[i]);
    }
}

// Function to display the array
void displayArray(int arr[], int n, const char *order) {
    printf("Sorted array(%s): ", order);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to generate a random array
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;  // Generate random numbers between 0 and 999
    }
}

int main() {
    int arr[MAX], n;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Quick Sort - Ascending Order\n");
        printf("2. Quick Sort - Descending Order\n");
        printf("3. Quick Sort - Random Order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputArray(arr, &n);
                quickSort(arr, 0, n - 1);
                displayArray(arr, n, "Ascending");
                break;

            case 2:
                inputArray(arr, &n);
                quickSort(arr, 0, n - 1);
                // Reverse the array to display in descending order
                for (int i = 0; i < n / 2; i++) {
                    int temp = arr[i];
                    arr[i] = arr[n - 1 - i];
                    arr[n - 1 - i] = temp;
                }
                displayArray(arr, n, "Descending");
                break;

            case 3:
                printf("Enter the number of elements: ");
                scanf("%d", &n);
                if (n > MAX) {
                    printf("Error: Number of elements exceeds the maximum allowed size (%d).\n", MAX);
                    exit(1);
                }
                generateRandomArray(arr, n);
                quickSort(arr, 0, n - 1);
                displayArray(arr, n, "Random");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

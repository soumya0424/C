// Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

int mergeComparisons = 0;

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        mergeComparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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
        printf("1. Merge Sort - Ascending Order\n");
        printf("2. Merge Sort - Descending Order\n");
        printf("3. Merge Sort - Random Order\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readFile(arr, &n, "inAsce.dcm");  // Changed to inAsce.dcm
                mergeComparisons = 0;
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outMergeAsce.dcm");  // Changed to outMergeAsce.dcm
                printf("Merge Sort (Ascending): %d comparisons, time spent = %f seconds\n", mergeComparisons, time_spent);
                break;

            case 2:
                readFile(arr, &n, "inDesc.dcm");  // Changed to inDesc.dcm
                mergeComparisons = 0;
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outMergeDesc.dcm");  // Changed to outMergeDesc.dcm
                printf("Merge Sort (Descending): %d comparisons, time spent = %f seconds\n", mergeComparisons, time_spent);
                break;

            case 3:
                readFile(arr, &n, "inRand.dcm");  // Changed to inRand.dcm
                mergeComparisons = 0;
                start = clock();
                mergeSort(arr, 0, n - 1);
                end = clock();
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                writeFile(arr, n, "outMergeRand.dcm");  // Changed to outMergeRand.dcm
                printf("Merge Sort (Random): %d comparisons, time spent = %f seconds\n", mergeComparisons, time_spent);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
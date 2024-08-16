#include <stdio.h>

int main()  
{  
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Duplicate elements in the given array:\n");  
    for (int i = 0; i < n; i++) {  
        for (int j = i + 1; j < n; j++) {  
            if (arr[i] == arr[j]) {
                printf("%d\n", arr[j]);
                break;             }
        }
    }
    int maxCount = 0, mostRepeatingElement = arr[0];
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            mostRepeatingElement = arr[i];
        }
    }

    printf("Most repeating element in the array: %d (repeated %d times)\n", mostRepeatingElement, maxCount);
    return 0;  
}  

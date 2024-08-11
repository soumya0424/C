#include <stdio.h>  
   
int main()  
{  
    int n, rotations;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of rotations: ");
    scanf("%d", &rotations);
    printf("Original array: \n");  
    for (int i = 0; i < n; i++) {   
        printf("%d ", arr[i]);   
    }   
    printf("\n");
    for (int i = 0; i < rotations; i++) {  
        int j, last;  
        last = arr[n - 1];  
        for (j = n - 1; j > 0; j--) {  
            arr[j] = arr[j - 1];  
        }  
        arr[0] = last;  
    }  
    printf("Array after right rotation: \n");  
    for (int i = 0; i < n; i++) {  
        printf("%d ", arr[i]);  
    }  
    printf("\n");
    
    return 0;  
}  

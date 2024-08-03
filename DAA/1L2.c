#include <stdio.h>
void fillPrefixSum(int arr[], int n, int prefixSum[])
{
    prefixSum[0] = arr[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];
}
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

    int prefixSum[n];
    fillPrefixSum(arr, n, prefixSum);
    printf("Prefix Sum array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", prefixSum[i]);
    printf("\n");
    return 0;
}

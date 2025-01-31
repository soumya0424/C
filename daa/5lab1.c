#include <stdio.h>

typedef struct {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
} ITEM;

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

float fractionalKnapsack(ITEM items[], int n, float capacity) {
    heapSort(items, n);

    float total_profit = 0.0;
    for (int i = 0; i < n; i++) {
        if (items[i].item_weight <= capacity) {
            capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
        } else {
            total_profit += items[i].item_profit * (capacity / items[i].item_weight);
            break;
        }
    }
    return total_profit;
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM items[n];

    for (int i = 0; i < n; i++) {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    float max_profit = fractionalKnapsack(items, n, capacity);

    printf("Maximum profit: %.2f\n", max_profit);
    return 0;
}


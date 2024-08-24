#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[50];
    int age;
    int height;
    int weight;  // Weight in kg
};

void swap(struct person* a, struct person* b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct person heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].age < heap[smallest].age)
        smallest = left;

    if (right < n && heap[right].age < heap[smallest].age)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

void maxHeapify(struct person heap[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].weight > heap[largest].weight)
        largest = left;

    if (right < n && heap[right].weight > heap[largest].weight)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

void buildMinHeap(struct person heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(heap, n, i);
    }
}

void buildMaxHeap(struct person heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, n, i);
    }
}

void displayHeap(struct person heap[], int n) {
    for (int i = 0; i < n; i++) {
        printf("ID: %d, Name: %s, Age: %d, Height: %d, Weight: %d kg\n",
               heap[i].id, heap[i].name, heap[i].age, heap[i].height, heap[i].weight);
    }
}

void displayWeightOfYoungest(struct person heap[], int n) {
    printf("Weight of youngest person: %.2f kg\n", (float)heap[0].weight);
}

void insertMinHeap(struct person heap[], int* n, struct person newPerson) {
    (*n)++;
    int i = *n - 1;
    heap[i] = newPerson;

    while (i != 0 && heap[(i - 1) / 2].age > heap[i].age) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    printf("Heap after insertion:\n");
    displayHeap(heap, *n);
}

void deleteOldest(struct person heap[], int* n) {
    if (*n == 0) {
        printf("Heap is empty.\n");
        return;
    }

    int oldestIndex = 0;
    for (int i = 1; i < *n; i++) {
        if (heap[i].age > heap[oldestIndex].age) {
            oldestIndex = i;
        }
    }

    printf("Deleting person with ID %d (Oldest)\n", heap[oldestIndex].id);

    heap[oldestIndex] = heap[*n - 1];
    (*n)--;
    minHeapify(heap, *n, oldestIndex);

    printf("Heap after deleting the oldest person:\n");
    displayHeap(heap, *n);
}

void readData(struct person** persons, int* n) {
    printf("Enter the number of persons: ");
    scanf("%d", n);
    *persons = (struct person*)malloc(*n * sizeof(struct person));

    for (int i = 0; i < *n; i++) {
        printf("Enter details for person %d (ID Name Age Height Weight(kg)): ", i);
        scanf("%d %s %d %d %d", &(*persons)[i].id, (*persons)[i].name, &(*persons)[i].age, &(*persons)[i].height, &(*persons)[i].weight);
    }
}

int main() {
    struct person* persons = NULL;
    int n = 0;
    int choice;
    int heapSize = 0;

    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readData(&persons, &n);
                heapSize = n;
                break;
            case 2:
                buildMinHeap(persons, heapSize);
                printf("Min-heap created based on age:\n");
                displayHeap(persons, heapSize);
                break;
            case 3:
                buildMaxHeap(persons, heapSize);
                printf("Max-heap created based on weight:\n");
                displayHeap(persons, heapSize);
                break;
            case 4:
                if (heapSize > 0)
                    displayWeightOfYoungest(persons, heapSize);
                else
                    printf("Heap is empty.\n");
                break;
            case 5: {
                struct person newPerson;
                printf("Enter person details (ID Name Age Height Weight(kg)): ");
                scanf("%d %s %d %d %d", &newPerson.id, newPerson.name, &newPerson.age, &newPerson.height, &newPerson.weight);
                insertMinHeap(persons, &heapSize, newPerson);
                break;
            }
            case 6:
                deleteOldest(persons, &heapSize);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    free(persons);
    return 0;
}


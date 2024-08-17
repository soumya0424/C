#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char alphabet;
    int frequency;
} SYMBOL;

typedef struct Node {
    SYMBOL symbol;
    struct Node *left, *right;
} Node;

typedef struct {
    Node* array[100];
    int size;
} MinHeap;

Node* createNode(char alphabet, int frequency) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol.alphabet = alphabet;
    node->symbol.frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    return minHeap;
}

void insertMinHeap(MinHeap* minHeap, Node* node) {
    minHeap->array[minHeap->size] = node;
    int i = minHeap->size;
    minHeap->size++;
    while (i && node->symbol.frequency < minHeap->array[(i - 1) / 2]->symbol.frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

Node* extractMin(MinHeap* minHeap) {
    Node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    int i = 0;
    while (2 * i + 1 < minHeap->size) {
        int smallest = i;
        if (2 * i + 1 < minHeap->size && minHeap->array[2 * i + 1]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
            smallest = 2 * i + 1;
        if (2 * i + 2 < minHeap->size && minHeap->array[2 * i + 2]->symbol.frequency < minHeap->array[smallest]->symbol.frequency)
            smallest = 2 * i + 2;
        if (smallest == i)
            break;
        Node* temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[smallest];
        minHeap->array[smallest] = temp;
        i = smallest;
    }
    return temp;
}

Node* buildHuffmanTree(SYMBOL symbols[], int size) {
    MinHeap* minHeap = createMinHeap();

    for (int i = 0; i < size; ++i)
        insertMinHeap(minHeap, createNode(symbols[i].alphabet, symbols[i].frequency));

    while (minHeap->size != 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);

        Node* newNode = createNode('$', left->symbol.frequency + right->symbol.frequency);
        newNode->left = left;
        newNode->right = right;
        insertMinHeap(minHeap, newNode);
    }

    return extractMin(minHeap);
}

void printCodes(Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->symbol.alphabet);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

int main() {
    SYMBOL symbols[] = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    int size = sizeof(symbols) / sizeof(symbols[0]);

    Node* root = buildHuffmanTree(symbols, size);

    int arr[100], top = 0;
    printCodes(root, arr, top);

    return 0;
}

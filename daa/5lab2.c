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

void inOrderTraversal(Node* root) {
    if (root == NULL)
        return;
    inOrderTraversal(root->left);
    if (root->symbol.alphabet != '$') // To avoid printing internal nodes with '$'
        printf("%c ", root->symbol.alphabet);
    inOrderTraversal(root->right);
}

int main() {
    int size;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &size);

    SYMBOL symbols[size];

    printf("Enter the alphabets: ");
    for (int i = 0; i < size; i++) {
        scanf(" %c", &symbols[i].alphabet); // Space before %c to consume any trailing whitespace
    }

    printf("Enter their frequencies: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &symbols[i].frequency);
    }

    Node* root = buildHuffmanTree(symbols, size);

    printf("In-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}


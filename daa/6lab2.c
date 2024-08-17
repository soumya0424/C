#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent, rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void KruskalMST(Edge edges[], int n, int e) {
    qsort(edges, e, sizeof(Edge), compareEdges);

    Subset *subsets = (Subset *)malloc(n * sizeof(Subset));
    for (int i = 0; i < n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    Edge result[n];
    int i = 0, count = 0, totalCost = 0;
    while (count < n - 1 && i < e) {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.u);
        int y = find(subsets, nextEdge.v);

        if (x != y) {
            result[count++] = nextEdge;
            Union(subsets, x, y);
            totalCost += nextEdge.weight;
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < count; i++)
        printf("(%d, %d) = %d\n", result[i].u + 1, result[i].v + 1, result[i].weight);
    
    printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);

    free(subsets);
}

int main() {
    int n, e;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &e);

    Edge *edges = (Edge *)malloc(e * sizeof(Edge));

    printf("Enter the edges in format (u v weight):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
        edges[i].u--;
        edges[i].v--;
    }

    KruskalMST(edges, n, e);

    free(edges);

    return 0;
}

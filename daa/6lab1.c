#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void primMST(int **graph, int n) {
    int parent[n];
    int key[n];
    int mstSet[n];
    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, u;
        for (int v = 0; v < n; v++)
            if (mstSet[v] == 0 && key[v] < min)
                min = key[v], u = v;

        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int **mst = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mst[i] = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n; i++) {
        mst[parent[i]][i] = graph[i][parent[i]];
        mst[i][parent[i]] = graph[i][parent[i]];
        totalCost += graph[i][parent[i]];
    }

    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mst[i][j] == 0)
                printf("INF ");
            else
                printf("%d ", mst[i][j]);
        }
        printf("\n");
    }
    printf("Total cost of the Minimum Spanning Tree: %d\n", totalCost);

    for (int i = 0; i < n; i++)
        free(mst[i]);
    free(mst);
}

int main() {
    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    int n;
    fscanf(file, "%d", &n);

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        graph[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &graph[i][j]);

    fclose(file);

    primMST(graph, n);

    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void printPath(int **next, int u, int v) {
    if (next[u][v] == -1) {
        printf("No path exists.\n");
        return;
    }

    printf("Shortest Path: %d ", u + 1);
    while (u != v) {
        u = next[u][v];
        printf("-> %d ", u + 1);
    }
    printf("\n");
}

void floydWarshall(int **graph, int n) {
    int **dist = (int **)malloc(n * sizeof(int *));
    int **next = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
        next[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != INF) {
                dist[i][j] = graph[i][j];
                next[i][j] = j;
            } else {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    int u, v;
    printf("Enter the pair of vertices (u v) to find the shortest path: ");
    scanf("%d %d", &u, &v);
    u--; v--;  // Adjust for 0-based indexing

    printPath(next, u, v);

    for (int i = 0; i < n; i++) {
        free(dist[i]);
        free(next[i]);
    }
    free(dist);
    free(next);
}

int main() {
    FILE *file = fopen("inDiAdjMat2.dat", "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    int n;
    fscanf(file, "%d", &n);

    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    fclose(file);

    floydWarshall(graph, n);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}

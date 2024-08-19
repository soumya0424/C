#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void dijkstra(int **graph, int n, int src) {
    int dist[n];
    int visited[n];
    int parent[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INF, u;

        for (int v = 0; v < n; v++)
            if (visited[v] == 0 && dist[v] < min)
                min = dist[v], u = v;

        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
    }

    printf("Vertex\t Distance from Source\t Path\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t\t\t", i + 1, dist[i]);
        int path_vertex = i;
        while (parent[path_vertex] != -1) {
            printf("%d <- ", path_vertex + 1);
            path_vertex = parent[path_vertex];
        }
        printf("%d\n", src + 1);
    }
}

int main() {
    FILE *file = fopen("inDiAdjMat1.dat", "r");
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

    int src;
    printf("Enter the starting vertex: ");
    scanf("%d", &src);
    src--;  // Adjusting for 0-based indexing

    dijkstra(graph, n, src);

    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);

    return 0;
}

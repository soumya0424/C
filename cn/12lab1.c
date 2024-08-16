// Main Simulation Code
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX
#define NODES 5

// Function prototypes
void bellmanFord(int graph[NODES][NODES], int src);
void dijkstra(int graph[NODES][NODES], int src);

int main() {
    int graph[NODES][NODES] = {
        {0, 2, INF, 1, INF},
        {2, 0, 3, 2, INF},
        {INF, 3, 0, 4, 5},
        {1, 2, 4, 0, 3},
        {INF, INF, 5, 3, 0}
    };

    printf("Distance Vector Routing (Bellman-Ford):\n");
    bellmanFord(graph, 0);

    printf("\nLink State Routing (Dijkstra's Algorithm):\n");
    dijkstra(graph, 0);

    return 0;
}

void printSolution(int dist[], int n) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

void bellmanFord(int graph[NODES][NODES], int src) {
    int dist[NODES];

    for (int i = 0; i < NODES; i++) {
        dist[i] = INF;
    }
    dist[src] = 0;

    for (int k = 0; k < NODES - 1; k++) {
        for (int u = 0; u < NODES; u++) {
            for (int v = 0; v < NODES; v++) {
                if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    printSolution(dist, NODES);
}

int minDistance(int dist[], bool sptSet[]) {
    int min = INF, min_index;

    for (int v = 0; v < NODES; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void dijkstra(int graph[NODES][NODES], int src) {
    int dist[NODES];
    bool sptSet[NODES];

    for (int i = 0; i < NODES; i++) {
        dist[i] = INF, sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < NODES - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < NODES; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, NODES);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

struct Edge {
    int src, dest, weight;
};


void printEdgeList(struct Edge edges[], int E) {
    printf("Edge List:\n");
    for (int i = 0; i < E; i++) {
        printf("Source: %d, Destination: %d, Weight: %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }
}

void bellmanFord(struct Edge edges[], int V, int E, int src, int target) {
    int dist[V];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX; 
    }
    dist[src] = 0;


    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    
    int negativeCycleDetected = 0;
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle.\n");
            negativeCycleDetected = 1;
            break;
        }
    }

    if (!negativeCycleDetected) {
        if (dist[target] == INT_MAX) {
            printf("Power Station %d is not reachable from Power Station %d\n", target, src);
        } else {
            printf("Shortest Distance from Power Station %d to Power Station %d (Bellman-Ford): %d\n", src, target, dist[target]);
        }
    }
}

int main() {
    int V, E;
    char filename[50];
    
    
    printf("Enter the input file name : ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return -1;
    }

    
    fscanf(file, "%d %d", &V, &E);
    struct Edge edges[E];

    
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        fscanf(file, "%d %d %d", &src, &dest, &weight);
        edges[i].src = src;
        edges[i].dest = dest;
        edges[i].weight = weight;
    }

    fclose(file);  


    printEdgeList(edges, E);

    int src, target;
    printf("Enter the source power station: ");
    scanf("%d", &src);
    printf("Enter the target power station: ");
    scanf("%d", &target);

    
    clock_t start = clock();
    
    printf("\nBellman-Ford Algorithm:\n");
    bellmanFord(edges, V, E, src, target);

    
    clock_t end = clock();
    

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to execute Bellman-Ford algorithm: %f seconds\n", time_taken);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

struct GraphMatrix {
    int V;         
    int** matrix; 
};


struct GraphMatrix* createGraphMatrix(int V) {
    struct GraphMatrix* graph = (struct GraphMatrix*) malloc(sizeof(struct GraphMatrix));
    graph->V = V;
    graph->matrix = (int**) malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->matrix[i] = (int*) malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}


void addEdgeMatrix(struct GraphMatrix* graph, int src, int dest, int weight) {
    graph->matrix[src][dest] = weight;
    graph->matrix[dest][src] = weight; 
}


void readGraphFromFile(const char* filename, struct GraphMatrix* graph) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    int E;  
    fscanf(file, "%d %d", &graph->V, &E);  // Reading number of vertices and edges

    int src, dest, weight;
    while (fscanf(file, "%d %d %d", &src, &dest, &weight) != EOF) {
        addEdgeMatrix(graph, src, dest, weight);
    }

    fclose(file);
}


void dijkstra(struct GraphMatrix* graph, int src) {
    int V = graph->V;
    int dist[V];
    int visited[V];

    
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;  

    for (int count = 0; count < V - 1; count++) {
        int u = -1;

        
        for (int i = 0; i < V; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1 || dist[u] == INT_MAX) break;

        visited[u] = 1;

        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph->matrix[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];
            }
        }
    }


    printf("\nShortest distances from source power station  %d:\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("this power station  %d is not reachable from powerstation  %d\n", i, src);
        else
            printf("Distance to powerstation  %d: %d\n", i, dist[i]);
    }
}

int main() {
    char filename[100];
    printf("Enter the filename containing graph data: ");
    scanf("%s", filename);


    clock_t start_time = clock();

    
    if (strstr(filename, ".txt") == NULL) {
        printf("Error: The file should have a .txt extension.\n");
        return 1;
    }


    struct GraphMatrix* graphMatrix = NULL;
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        int V, E;
        fscanf(file, "%d %d", &V, &E);  
        fclose(file);
        
        graphMatrix = createGraphMatrix(V);  
    } else {
        printf("Error: Could not open file.\n");
        return 1;
    }


    readGraphFromFile(filename, graphMatrix);

    
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < graphMatrix->V; i++) {
        for (int j = 0; j < graphMatrix->V; j++) {
            printf("%d ", graphMatrix->matrix[i][j]);
        }
        printf("\n");
    }


    int src;
    printf("\nEnter the source power station for shortest path calculations: ");
    scanf("%d", &src);

    
    if (src >= graphMatrix->V || src < 0) {
        printf("Invalid source power station !\n");
        return 1;
    }


    dijkstra(graphMatrix, src);

    
    clock_t end_time = clock();

    
    double time_taken = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %.6f seconds\n", time_taken);


    for (int i = 0; i < graphMatrix->V; i++) {
        free(graphMatrix->matrix[i]);
    }
    free(graphMatrix->matrix);
    free(graphMatrix);

    return 0;
}


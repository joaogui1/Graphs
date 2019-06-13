#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include "queue.h"
#include "pair.h"

#define noEdge -1
#define maxSize 300
#define oo 0x3f3f3f3f

typedef enum _relations {
    strangers, friends, wasRequested, sendRequest
} relations;

typedef enum _colors {
    white, gray, black
} colors;

typedef struct _edge {
    int proximity;
    int relation;
} Edge;

typedef struct _graph {
    int currSize;
    int visited[maxSize];
    int distance[maxSize][maxSize];
    int prev[maxSize];
    int res[maxSize][maxSize];
    Edge edges[maxSize][maxSize];
} Graph;

Graph* createGraphMatrix(int* error);
void destroyGraphMatrix(Graph* g, int* error);
int degree(Graph* g, int vertex, int* error);
int degreeOut(Graph* g, int vertex, int* error);
int degreeIn(Graph* g, int vertex, int* error);
void removeEdgeMatrix(Graph* g, int from, int to, int* error);
void addEdgeMatrix(Graph* g, int from, int to, int proximity, int* error);
void printMatrix(Graph* g, int debug);
void bfs(Graph* g, int source);
void flow(Graph* g);
void floydWarshall(Graph* g);
int edmondKarps(Graph* g, int pos, int pos2);
void bfsFlow(Graph* g, int source, int sink);
int convertToFile(Graph* g, char* filename);
int getFromFile(Graph* g, char* filename);

#endif
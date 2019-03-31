#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAXV 100
#define noEdge 0
typedef int elem;

typedef struct _graph {
	elem edges[MAXV][MAXV];
	int numVertices; // amount of numVertices
	int numEdges;
	int weighted;
	int directed;
} graph;


graph* createGraph(int* n, int* dir, int* wei, int* error);
void destroyGraph(graph* g, int* error);
void insertEdge(graph* g, int* from, int* to, elem* weight, int* error);
void removeEdge(graph* g, int* from, int* to, int* error);
int* eulerCycle(graph* g, int* error);
void findBridges(graph* g, int** isBridge);

#endif
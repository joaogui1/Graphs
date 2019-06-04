#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <string.h>
#include "adj_matrix.h"

int min(int x, int y) {
    return (x < y ? x : y);
}

bool outOfBoudaries(int vertex) {
    if(vertex >= maxSize || vertex < 0) return true;
    return false;
}

Graph* createGraphMatrix(int* error) {
    Graph* g = malloc(sizeof(Graph));

    if(g == NULL) {
        *error = 1;
        return NULL;
    }

    g->currSize = 0;

    for (int i = 0; i < maxSize; i++) {
        for (int j = 0; j < maxSize; j++) {
            g->edges[i][j].proximity = -1;
            g->edges[i][j].relation = strangers;
        }
    }

    *error = 0;
    return g;
}

void destroyGraphMatrix(Graph* g, int* error) {
    free(g);
    return;
}

void printMatrix(Graph* g, int debug) {
    if(debug) 
        printf("size: %d\n\n", g->currSize);

    for(int i = 0; i < g->currSize; i++) {
        for(int j = 0; j < g->currSize; j++) {
            printf("%d\t", g->edges[i][j].proximity);
        }
        printf("\n");
    }

    printf("\n");
    for(int i = 0; i < g->currSize; i++) {
        for(int j = 0; j < g->currSize; j++) {
            printf("%d\t", g->edges[i][j].relation);
        }
        printf("\n");
    }

}

void addEdgeMatrix(Graph* g, int from, int to, int proximity, int* error) {    
    if(g == NULL || outOfBoudaries(from) || outOfBoudaries(to)) {
        *error = 1;
        return;
    }

    g->edges[from][to].proximity = proximity;
    g->edges[to][from].proximity = proximity;

    *error = 0;
    return;
}

void removeEdgeMatrix(Graph* g, int from, int to, int* error) {
    if(g == NULL || outOfBoudaries(from) || outOfBoudaries(to)) {
        *error = 1;
        return;
    }

    g->edges[from][to].proximity = noEdge;
    g->edges[to][from].proximity = noEdge;

    *error = 0;
    return;
}

void bfs(Graph* g, int source) {
    memset(g->distance, -1, maxSize*maxSize);
    memset(g->visited, white, maxSize);
    memset(g->prev, -1, maxSize);

    Queue* q = createQueue();

    insertQueue(q, source, 0);
    g->distance[source][source] = 0;

    while (!isEmptyQueue(q)) {
        Pair p = popQueue(q);
        
        int u = p.first;
        int w = p.second;

        for(int i = 0; i < g->currSize; i++) {
            if(g->edges[i][u].relation == friends && g->visited[i] == white) {
                insertQueue(q, i, w + 1);
                g->prev[i] = u;
                g->distance[source][i] = w + 1;
                g->visited[i] = gray;
            }
        }

        g->visited[u] = black;
    }

    return;    
}

void floydWarshall(Graph* g) {
    for(int i = 0; i < g->currSize; i++) {
        for(int j = 0; j < g->currSize; j++) {
            if(i == j) g->distance[i][j] = 0;
            else if(g->edges[i][j].relation == friends) g->distance[i][j] = 1;
            else g->distance[i][j] = oo;
        }
    }

    int size = g->currSize;

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                g->distance[i][j] = min(g->distance[i][j], g->distance[i][k] + g->distance[k][j]);
            }
        }
    }

    return;
}

int degreeIn(Graph* g, int vertex, int* error) {
    if(g == NULL || outOfBoudaries(vertex)) {
        *error = 1;
        return -1;
    }

    int deg = 0;

    for(int i = 0; i < maxSize; i++) {
        if(g->edges[i][vertex].proximity != noEdge)
            deg++;
    }

    *error = 0;
    return deg;
}

int degreeOut(Graph* g, int vertex, int* error) {
    if(g == NULL || outOfBoudaries(vertex)) {
        *error = 1;
        return -1;
    }

    int deg = 0;

    for(int i = 0; i < maxSize; i++) {
        if(g->edges[vertex][i].proximity != noEdge)
            deg++;
    }

    *error = 0;
    return deg;
}
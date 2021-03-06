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

void fillRes(Graph* g) {
    for(int i = 0; i < g->currSize; i++) {
        for(int j = 0; j < g->currSize; j++) {
            g->res[i][j] = g->edges[i][j].proximity;
        }
    }
    return;
}

void bfsFlow(Graph* g, int source, int sink) {
    memset(g->visited, white, maxSize);
    memset(g->prev, -1, maxSize);

    Queue* q = createQueue();

    insertQueue(q, source, 0);
    g->distance[source][source] = 0;

    while (!isEmptyQueue(q)) {
        Pair p = popQueue(q);
        
        int u = p.first;
        int w = p.second;

        if(u == sink) break;

        for(int i = 0; i < g->currSize; i++) {
            if(g->edges[i][u].relation == friends && g->visited[i] == white && g->res[u][i] > 0) {
                insertQueue(q, i, w + 1);
                g->prev[i] = u;
                g->visited[i] = gray;
            }
        }

        g->visited[u] = black;
    }

    return;    
}

int augment(Graph* g, int currId, int minEdge, int source) {
    int flow = 0;

    if(currId == source) {
        return minEdge;
        
    } else if (g->prev[currId] != -1) {
        int prev = g->prev[currId];
        int newMin = min(minEdge, g->res[prev][currId]);

        flow = augment(g, prev, newMin, source);

        g->res[prev][currId] -= flow;
        g->res[currId][prev] += flow;
    }
    
    return flow;
}

int edmondKarps(Graph* g, int pos, int pos2) {
    int maxFlow = 0;
    fillRes(g);

    while(true) {
        bfsFlow(g, pos, pos2);
        int flow = augment(g, pos2, oo, pos);
        
        if(flow == 0) break;
        maxFlow += flow;
    }
    
    return maxFlow;
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

int convertToFile(Graph* g, char* filename){
    if(g == NULL) return 0;

    FILE* fp;
    char slash_n = '\n';

    if( !(fp = fopen(filename, "w")) ){
        return 0;
    }

    fwrite(&g->currSize, sizeof(int), 1, fp);
    fwrite(&slash_n, sizeof(char), 1, fp);

    for(int i = 0; i < g->currSize; i++){
        fwrite(g->edges[i], sizeof(Edge), g->currSize, fp);
        fwrite(&slash_n, sizeof(char), 1, fp);
    }

    fclose(fp);
    return 1;
}

int getFromFile(Graph* g, char* filename){
    if(g == NULL) return 0;

    FILE* fp;

    if( !(fp = fopen(filename, "r")) ){
        return 0;
    }

    fread(&g->currSize, sizeof(int), 1, fp);
    fseek(fp, sizeof(char), SEEK_CUR);

    for(int i = 0; i < g->currSize; i++){
        fread(g->edges[i], sizeof(Edge), g->currSize, fp);
        fseek(fp, sizeof(char), SEEK_CUR);
    }

    fclose(fp);
    return 1;
}
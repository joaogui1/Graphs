#include "Lista.h"

#define NUM_VERT 100


typedef struct{
  Lista adj[NUM_VERT];
  int numVert;
}Grafo;

Grafo* CriarGrafo(int numVert, int* error);
void removerAresta(Grafo* g, int v1, int v2, elem p, int* error);
void inserirAresta(Grafo* g, int v1, int v2, elem p, int* error);
void liberaGrafo(Grafo *g, int* error);

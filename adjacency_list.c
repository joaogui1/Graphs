#include "adjacency_list.h"
#include <stdio.h>
#include <stdlib.h>

Grafo* CriarGrafo(int numVert, int* error){
  Grafo* g = calloc(1, sizeof(Grafo));
  if(!g){
    *error = 1;
    return NULL;
  }
  *error = 0;
  g->numVert = numVert;

  for(int i = 0; i < g->numVert; i++){
    g->adj[i].ini = calloc(1, sizeof(Node));
    g->adj[i].fim = g->adj[i].ini;
  }

  return g;
}

Node* search(Grafo* g, int v1, int v2){
  int size = g->adj[v1].tam;
  Node* atual = g->adj[v1].ini;
  for(int i = 0; i < size; i++){
    if(atual->next->id == v2) return atual;
    atual = atual->next;
  }

  return NULL;
}

void inserirAresta(Grafo* g, int v1, int v2, elem p, int* error){
  Node *n = calloc(1, sizeof(Node));
  if(n){
    *error = 0;
    n->id = v2;
    n->peso = p;
    g->adj[v1].fim->next = n;
    g->adj[v1].fim = n;
  }
  else *error = 1;

  if(!*error) g->adj[v1].tam++;
}

void removerAresta(Grafo* g, int v1, int v2, elem p, int* error){
  if(v1 >= g->numVert){
    *error = 1;
    return;
  }

  Node* pos = search(g, v1, v2);
  if(!pos){
    *error = 2;
    return;
  }

  Node* toBeFreed = pos->next;
  pos->next = pos->next->next;

  if(toBeFreed == g->adj[v1].fim){
    g->adj[v1].fim = pos;
  }
  free(toBeFreed);

  *error = 0;
}

//

//TODO
/*
taVazia
Primeiro Vertice
ExisteAresta
Transposta
numArestas
  -iterativa
  -recursiva
algoritmo guloso de Welsh-Powell, 1975
*/

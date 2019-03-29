#include "graph.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
  return (a + b - abs(a - b))/2;
  // return (a > b)?b:a;
}

int max(int a, int b){
  return -min(-a, -b);
}

double jacquard(int *n, graph *g1, graph *g2){
  double intersection = 0.0, Union = 0.0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j){
      Union += max(g1->edges[i][j], g2->edges[i][j]);
      intersection += min(g1->edges[i][j], g2->edges[i][j]);
    }

  return intersection/Union;
}

int main(){
  int n, edges_one, edges_two, u, v;
  int one = 1, aux = 0, error = 0;
  graph *G1, *G2;

  scanf("%d %d", &n, &m);
  scanf("%d %d", &edges_one, &edges_two);
  G1 = createGraph(&n, &one, &one, &error);
  G2 = createGraph(&n, &one, &one, &error);
  for(int i = 0; i < edges_one; ++i){
    scanf("%d %d", &u, &v);
    aux = G1->edges[i][j] + 1;
    insertEdge(G1, u, v, &aux, &error);
  }

  for(int i = 0; i < edges_two; ++i){
    scanf("%d %d", &u, &v);
    aux = G2->edges[i][j] + 1;
    insertEdge(G2, u, v, &aux, &error);
  }



  return 0;
}

#include "graph.h"
#include <stdio.h>

int main(){
  graph *G;
  int zero = 0, um = 1;
  int n, m, u, v, error;

  scanf("%d %d", &n, &m);

  G = createGraph(&n, &zero, &um, &error);
  for(int i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    insertEdge(G, &u, &v, &um, &error);
  }
  int *path;
  path = eulerCycle(G, &error);
  
  for (int i = 0; i < m; i++) {
    printf("%d ", path[i]);
  }
  printf("\n");
  free(path);
  destroyGraph(G, &error);

  return 0;
}

#include "adjacency_list.h"

typedef struct{
  int x, y;
}position;

int main(){
  int n, m, error;
  position pacman, ghost;
  Grafo *tabuleiro;
  scanf("%d %d", &n, &m);
  tabuleiro = createGraph(n*m, &error);
  if(error)
    return 1;

  for(int i = 0; i < n; ++i){
    for(int j = 0; j < m; ++j){
      if(i > 0) inserirAresta(tabuleiro, i*m + j, (i - 1)*m + j, 1, &error);
      if(i < n - 1) inserirAresta(tabuleiro, i*m + j, (i + 1)*m + j, 1, &error);
      if(j > 0) inserirAresta(tabuleiro, i*m + j, i*m + j - 1, 1, &error);
      if(j < m - 1) inserirAresta(tabuleiro, i*m + j, i*m + j + 1, 1, &error);

    }
  }



  return 0;
}

#include "adjacency_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int x, y;
}position;

void print_tab(int n, int m, position pacman, position ghost){
  for(int i = 0; i <= m + 1; ++i)
    printf("- ");
  printf("\n");

  for(int i = 0; i < n; ++i){
    printf("| ");
    for(int j = 0; j < m; ++j)
      if(j == pacman.x && i == pacman.y)
        printf("@ ");
      else if(j == ghost.x && i == ghost.y)
        printf("G ");
      else
        printf("* ");
    printf("|\n");
  }

  for(int i = 0; i <= m + 1; ++i)
    printf("- ");
  printf("\n\n");
}

int main(){
  Node *pos;
  Lista *adj;
  Grafo *tabuleiro;
  position pacman, ghost;
  int n, m, error, move, size;
  scanf("%d %d", &n, &m);
  tabuleiro = CriarGrafo(n*m, &error);
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
  scanf("%d %d", &ghost.x, &ghost.y);
  scanf("%d %d", &pacman.x, &pacman.y);

  print_tab(n, m, pacman, ghost);

  while(pacman.x != ghost.x || pacman.y != ghost.y){
    if(pacman.x < ghost.x)  ++pacman.x;
    else if(pacman.x > ghost.x)  --pacman.x;
    else if(pacman.y < ghost.y)  ++pacman.y;
    else  --pacman.y;

    move = rand()%2;
    if(move){
      adj = &(tabuleiro->adj[ghost.y*m + ghost.x]);
      size = adj->tam;
      move = rand()%size;
      pos = adj->ini;
      while(move-->0)
        pos = pos->next;
      ghost.x = pos->id%m;
      ghost.y = pos->id/m;

      // if(move == 0 && ghost.x > 0)  --ghost.x;
      // else if(move == 1 && ghost.x < m - 1)  ++ghost.x;
      // else if(move == 2 && ghost.y > 0)  --ghost.y;
      // else if(move == 3 && ghost.y < n - 1)  ++ghost.y;
    }

    print_tab(n, m, pacman, ghost);
  }



  return 0;
}

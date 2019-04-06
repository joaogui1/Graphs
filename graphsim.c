#include "graph.h"
#include "hash.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b){
  return (a > b)?a:b;
}

double jacquard(int *n, graph *g1, graph *g2){
  double intersection = 0.0, Union = 0.0;
  for(int i = 0; i < *n; ++i)
    for(int j = 0; j < *n; ++j){
      Union += max(g1->edges[i][j], g2->edges[i][j]);
      intersection += min(g1->edges[i][j], g2->edges[i][j]);
    }

  return intersection/Union;
}

double cossine(int *n, graph *g1, graph *g2){
  double dotprod = 0.0, length1 = 0.0, length2 = 0.0;
  for(int i = 0; i < *n; ++i)
    for(int j = 0; j < *n; ++j){
      dotprod += g1->edges[i][j]*g2->edges[i][j];
      length1 += g1->edges[i][j]*g1->edges[i][j];
      length2 += g2->edges[i][j]*g2->edges[i][j];
    }

  return dotprod/(sqrt(length1)*sqrt(length2));
}

//Parse string by end
//@return parsed string
char* parse(char* str, int *pos, char end, int* length){
	char* parsed = calloc(strlen(str), sizeof(char));
  *length = 0;

  while(str[*pos] != end && str[*pos] != '\0'){
    parsed[*length] = str[*pos];
    (*pos)+=1; (*length)+=1;
  }

  parsed[*length] = '\0';
  return parsed;

}

/*
guarda CN, V -> substantivo e verbo
*/
int* TextToNumbers(char *str, int* text_size, HashTable** t){
	int length = strlen(str);
  int parsed_len = 0;
  char* parsed;
  int intoHash = 0, error = 0;

  int* text = calloc((*t)->m, sizeof(int));
  *text_size = 0;

	for(int i = 0; i < length; i++){
    parsed = parse(str, &i, ' ', &parsed_len); //Divide por espaco
    int pos = i - parsed_len;
    for(int j = i; j >= pos; j--){
      if(str[j] == '/'){ //Encontrar '/'
        //A palavra e' um verbo ou substantivo?
        if(str[j+1] == 'V' || (str[j+1] == 'C' && str[j+2] == 'N')){
          //Gravar palavra
          int k = j-1, parsed_len = 0;
          while(k >= pos && str[k] != '/' && str[k] != ' '){
            parsed[parsed_len] = str[k];
            k--; parsed_len++;
          }
          parsed[parsed_len] = '\0';
          int parsed_num = insert(t, parsed, &error);
          text[*text_size] = parsed_num;
          *text_size += 1;
          if(error == 1){
            intoHash = 0;
            error = 0;
          } else intoHash = 1;
        }
        break;
      }
    }
    if(!intoHash) free(parsed);
    intoHash = 0;
	}

  return text;

}

void TextToGraph(int* text, int size, graph** g){
  int error = 0, aux = 0;
  for(int i = 0; i < size-1; ++i){
    aux = (*g)->edges[i][i+1] + 1;
    insertEdge(*g, &text[i], &text[i+1], &aux, &error);
  }
}

int main(){
  graph *G1, *G2;
  int edges_one, edges_two, u, v;
  int one = 1, error = 0;


  char* str1 = "<p><s> eu/PRS#gs1 visitei/VISITAR/V#ppi-1s sua/POSS#fs tia/TIO/CN#fs";
  char* str2 = "<p><s> eu/PRS#gs1 visitei/VISITAR/V#ppi-1s sua/POSS#fs tia/TIO/CN#fs comi/COMER/V#blabha maca/CN";

  HashTable* t = createHash();

  int size1 = 0, size2 = 0;
  int* text1 = TextToNumbers(str1, &size1, &t);
  int* text2 = TextToNumbers(str2, &size2, &t);

  G1 = createGraph(&t->n, &one, &one, &error);
  G2 = createGraph(&t->n, &one, &one, &error);

  TextToGraph(text1, size1, &G1);
  TextToGraph(text2, size2, &G2);

  double cos = cossine(&t->n, G1, G2);
  double jaq = jacquard(&t->n, G1, G2); 

  printf("A similaridade de cosseno foi: %.2lf%%\n", cos*100);
  printf("A similaridade de jacquard foi: %.2lf%%\n", jaq*100);

  destroy(&t);
  destroyGraph(G1, &error);
  destroyGraph(G2, &error);
  free(text1);
  free(text2);
  return 0;
}

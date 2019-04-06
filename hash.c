#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash.h"

#define TABLESIZE 8 //Preferivel potencias de 2

int isEqual(char* s1, char s2[]){
	int size1 = strlen(s1);
	int size2 = strlen(s2);
	int i = 0;

	while( s1[i] != '\0' && s2[i] != '\0'){
		if(s1[i] != s2[i]) return 0;
		i++;
	}

	if(s1[i] == '\0' && s2[i] == '\0') return 1;
	else return 0;
}

HashTable* createHash(){
	HashTable* t = calloc(1, sizeof(HashTable));
  t->m = TABLESIZE;
	t->n = 0;
	t->table = (elem_h*) calloc(t->m, sizeof(elem_h));
  for(int i = 0; i < t->m; i++){
    t->table[i].pos = 0;
  }
  return t;
}

int hashcoder(int m, char* key, int k){
	int length = strlen(key);
	int p = 7, hash = 0;

	for(int i = 0; i < length; i++){
		hash += ( ((int)key[i]) * (int)pow(p, i) ) % m;
	}

	k = k*((k+1)/2);
	return (hash+k)%m;
}

int insert(HashTable** t, char* word, int* error){
	int k = 0;

	//Enquanto tiver colidindo procurar um novo hashing
	int pos = 0;
  do{
		pos = hashcoder((*t)->m, word, k++);
		if( (*t)->table[pos].ocupied == FULL && strcmp(word, (*t)->table[pos].word) == 0 ){
      *error = 1;
      return (*t)->table[pos].pos; //Se ja existir essa palavra retorna o .pos
    }
	}while((*t)->table[pos].ocupied == FULL);


  elem_h palavra;
  palavra.word = word;
  palavra.pos = (*t)->n;
  palavra.ocupied = FULL;

	(*t)->table[pos] = palavra;


	(*t)->n++;
	return palavra.pos; //Se conseguiu inserir na tabela retorna o pos da palavra
}


int find(HashTable* t, char* word){
	int k = 0;
	//Procura pelo usuario na posicao
	int pos;

	do{
		pos = hashcoder(t->m, word, k++);
		if( t->table[pos].pos != FULL ) return -1;  //Se nao existir a palavra retorna -1
		else if( isEqual(t->table[pos].word, word) ){
			return t->table[pos].pos; //Retorna o pos da palavra no grafo
		}
	} while(1);

}

void destroy(HashTable** t){
  for(int i = 0; i < (*t)->m; i++){
    if((*t)->table[i].ocupied == FULL)
      free((*t)->table[i].word);
  }
  (*t)->n = 0;
  (*t)->m = 0;
  free((*t)->table);
  free(*t);
}

void exibir(HashTable* t){
  for(int i = 0; i < t->m; i++){
    if(t->table[i].ocupied == FULL)
      printf("%s : %d\n", t->table[i].word, t->table[i].pos);
  }
}
/*
void remove(HashTable* t, elem_h word);
*/

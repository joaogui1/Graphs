#define FULL 1

typedef struct{
	char* word;
	int pos;
  int ocupied;
}elem_h;

typedef struct{
	elem_h* table;
	int m;
	int n;
}HashTable;

HashTable* createHash(); //Cria a estrutura de hash, alocando o vetor e setando um tamanho para a tabela
int hashcoder(int m, char* key, int k); //Aplica a funcao hash no char* recebido. A funcao hash usada e' primo
void tableDoubling(); //Retorna o tamanho esperado para hashtable
int insert(HashTable** t, char* word, int* error); //Insere um elemento na tabela e retorna o hash dela.
int find(HashTable* t, char* word); //Verifica se a palavra esta na tabela. Retorna o id dela.
//void exibir(HashTable* t);
void exibir(HashTable* t);
void destroy(HashTable** t);

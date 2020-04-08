#define elem int

typedef struct n{
  int id;
  elem peso;
  struct n* next;
}Node;

/*typedef struct{
  union{
    char c;
    int i;
    double d;
  } info;
  Node* next;
  enum{character, integer, racional} type;
}Sentinela;
*/
typedef struct{
  Node* ini;
  Node* fim;
  int tam;
}Lista;

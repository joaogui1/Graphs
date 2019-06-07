
#include "csv.h"
#include "adj_matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDATA 9

//Parse string by end, '\0' and '\n'
//@return parsed string
char* parse(char* str, int *pos, char end, int* length){
	char* parsed = calloc(12000, sizeof(char));
    *length = 0;

    while(str[*pos] != end && str[*pos] != '\0' && str[*pos] != '\n'){
        parsed[*length] = str[*pos];
        (*pos)+=1; (*length)+=1;
    }
	(*pos)+=1;
	
    parsed[*length] = '\0';
    parsed = (char*) realloc(parsed, (*length)+1);
    return parsed;
}

/**
 * Instancia uma nova struct CSVFile, inicializando seus valores com 0 ou NULL
 * @return retorna a struct instanciada.
*/
CSVFile* new_CSVFile(){

    CSVFile* file = (CSVFile*) malloc(sizeof(CSVFile)*1);

    file->metadados = NULL;
    file->values = NULL;
    file->numColumns = 0;
    file->numLines = 0;

    return file;
}

/**
 * Essa funcao abre um arquivo CSV de nome fileName e guarda seus dados em (CSVFile*)file.
 * A primeira linha do csv, equivalente aos nomes das colunas, e' armazenada em file->metadados
 * Ja as proximas sao armazenadas em file->values[i], sendo i o numero da linha, contando apartir da segunda.
 * em file->numLines fica o numero de linhas com dados e em file->numColumns o numero de colunas de dados
 * 
 * @params:
 *  - file -> struct para arquivos CSV
 *  - fileName -> nome do arquivo CSV a ser lido
 * @return:
 *  - 0 -> se houve falha na leitura do arquivo
 *  - n -> Numero de usuarios
*/
int readCSV(CSVFile* file, const char* fileName){
    char buffer[1200];
    int size = 0;
    int pos = 0;
    int numLines = 0;
    int numColumns = 0;

    FILE* fp;
    
    if( !(fp = fopen(fileName, "r")) ){
        printf("Erro ao carregar arquivo de dados\n");
        return 0;
    }

    file->metadados = (char**) calloc(MAXDATA, sizeof(char*));

    char* call = fgets(buffer, 12000, fp);
    
    size = strlen(call);
    do{
        char* buffer2 = parse(call, &pos, ',', &size);
        if(size == 0) break;
        file->metadados[numColumns] = (char*) calloc(size+1, sizeof(char));
        strncpy(file->metadados[numColumns], buffer2, size+1);
        free(buffer2);

        numColumns++;
        if(numColumns > MAXDATA){
            return 0;
        }
    } while(size != 0);
    free(call);

    //file->metadados = (char**) realloc(file->metadados, sizeof(char*) * numColumns);
    file->numColumns = numColumns;

    file->values = (char***) calloc(maxSize, sizeof(char**));

    while(!feof(fp)){
        call = fgets(buffer, 12000, fp);
        if(call == NULL) break;

        size = strlen(call);
        pos = 0;
        file->values[numLines] = (char**) calloc(numColumns, sizeof(char*));
        for(int i = 0; i < numColumns; i++){
            char* buffer2 = parse(call, &pos, ',', &size);
            
            file->values[numLines][i] = (char*) calloc(size+1, sizeof(char));
            strncpy(file->values[numLines][i], buffer2, size+1);
            free(buffer2);
        }
        numLines++;
        free(call);
    }
    //file->values = (char***) realloc(file->values, sizeof(char**) * numLines);
    file->numLines = numLines;

    fclose(fp);
    return numLines;
}


/**
 * Essa funcao cria um arquivo CSV de acordo com os dados em (CSVFile*)file.
 * A primeira linha do csv equivale aos nomes das colunas armazenados em file->metadados.
 * Ja as proximas linhas equivalem aos dados armazenados em file->values.
 * 
 * @params:
 *  - file -> struct para arquivos CSV
 *  - fileName -> nome do arquivo CSV a ser escrito
 * @return:
 *  - 0 -> se houve falha na abertura do arquivo
 *  - n -> Numero de usuarios escritos
*/
int writeCSV(CSVFile* file, const char* fileName){
    FILE* fp;
    if( !(fp = fopen(fileName, "w")) ){
        printf("Erro ao carregar arquivo de dados\n");
        return 0;
    }
    

    int n = file->numColumns;
    char coma = ',';

    for(int i = 0; i < n; i++){
        fwrite(file->metadados[i], strlen(file->metadados[i]), 1, fp);
        if(i != n-1) fwrite(&coma, 1, 1, fp); 
    }

    int m = file->numLines;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            fwrite(file->values[i][j], strlen(file->values[i][j]), 1, fp);
            if(j != n-1) fwrite(&coma, 1, 1, fp);
        }
    }

    fclose(fp);
    return file->numLines;
}

void DestroyCSV(CSVFile* file){
    if(file == NULL) return;
    if(file->metadados != NULL){
        for(int i = 0; i < file->numColumns; i++)
            free(file->metadados[i]);
        free(file->metadados);
    }

    if(file->values != NULL){
        for(int i = 0; i < file->numLines; i++){
            for(int j = 0; j < file->numColumns; j++){
                free(file->values[i][j]);
            }
            free(file->values[i]);
        }
        free(file->values);
    }
    free(file);
}

int teste(){
    CSVFile* file = new_CSVFile();
    readCSV(file, "resources/teste.csv");
    
    for(int i = 0; i < file->numColumns; i++){
        printf("\t%s", file->metadados[i]);
    }
    printf("\n");

    for(int i = 0; i < file->numLines; i++){
        for(int j = 0; j < file->numColumns; j++){
            printf("\t%s", file->values[i][j]);
        }
        printf("\n");
    }

    writeCSV(file, "resources/copia_teste.csv");
    DestroyCSV(file);


    return 0;
}
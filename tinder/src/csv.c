
#include "csv.h"
#include "adj_matrix.h"
#include "profile.h"

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
    if(file == NULL){
        printf("Veio null pra mim aqui rapa!\n");
        return 0;
    } 
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
    char* buffer2;

    size = strlen(call);
    do{
        buffer2 = parse(call, &pos, ',', &size);
        if(size == 0) break;
        file->metadados[numColumns] = (char*) calloc(size+1, sizeof(char));
        strncpy(file->metadados[numColumns], buffer2, size+1);
        free(buffer2);

        numColumns++;
        if(numColumns > MAXDATA){
            printf("Excedeu aqui\n");
            return 0;
        }
    } while(size != 0);
    //free(call); --> crasha...

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
            buffer2 = parse(call, &pos, ',', &size);
            
            file->values[numLines][i] = (char*) calloc(size+1, sizeof(char));
            strncpy(file->values[numLines][i], buffer2, size+1);
            free(buffer2);
        }
        numLines++;
        //free(call); --> crasha...
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
    char slash_n = '\n';

    for(int i = 0; i < n; i++){
        //printf("%s %ld\n", file->metadados[i], strlen(file->metadados[i]));
        fwrite(file->metadados[i], strlen(file->metadados[i]), 1, fp);
        if(i != n-1) fwrite(&coma, 1, 1, fp);
        else fwrite(&slash_n, 1, 1, fp);
    }

    int m = file->numLines;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            //printf("%s %ld\n", file->values[i][j], strlen(file->values[i][j]));
            fwrite(file->values[i][j], strlen(file->values[i][j]), 1, fp);
            if(j != n-1) fwrite(&coma, 1, 1, fp);
            else fwrite(&slash_n, 1, 1, fp);
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

void setDefaultHeader(CSVFile* csv){
    csv->metadados = (char**) calloc(MAXDATA, sizeof(char*));
    for(int i = 0; i < MAXDATA; i++)
        csv->metadados[i] = (char*) calloc(50, sizeof(char));
    strncpy(csv->metadados[0], "Name", 5);
    strncpy(csv->metadados[1], "Age", 4);
    strncpy(csv->metadados[2], "City", 5);
    strncpy(csv->metadados[3], "Movie", 6);
    strncpy(csv->metadados[4], "Food", 5);
    strncpy(csv->metadados[5], "Paper", 6);
    strncpy(csv->metadados[6], "Algorithm", 10);
    strncpy(csv->metadados[7], "Avenger", 8);
    strncpy(csv->metadados[8], "Team", 5);

    csv->numColumns = MAXDATA;
}

void addProfile(CSVFile* csv, Profile profile){
    if(csv->numLines >= maxSize) return;


    if(csv->numLines == 0) csv->values = (char***) malloc(sizeof(char**) * maxSize);

    csv->values[csv->numLines] = calloc(csv->numColumns, sizeof(char*));
    


    csv->values[csv->numLines][0] = calloc(strlen(profile.name)+1, sizeof(char));
    csv->values[csv->numLines][1] = calloc(300, sizeof(char));
    csv->values[csv->numLines][2] = calloc(strlen(profile.city)+1, sizeof(char));
    csv->values[csv->numLines][3] = calloc(strlen(profile.movie)+1, sizeof(char));
    csv->values[csv->numLines][4] = calloc(strlen(profile.food)+1, sizeof(char));
    csv->values[csv->numLines][5] = calloc(strlen(profile.paper)+1, sizeof(char));
    csv->values[csv->numLines][6] = calloc(strlen(profile.algorithm)+1, sizeof(char));
    csv->values[csv->numLines][7] = calloc(strlen(profile.avenger)+1, sizeof(char));
    csv->values[csv->numLines][8] = calloc(strlen(profile.best)+1, sizeof(char));
    
    strncpy(csv->values[csv->numLines][0], profile.name, strlen(profile.name)+1);
    sprintf(csv->values[csv->numLines][1], "%d", profile.age);
    strncpy(csv->values[csv->numLines][2], profile.city, strlen(profile.city)+1);
    strncpy(csv->values[csv->numLines][3], profile.movie, strlen(profile.movie)+1);
    strncpy(csv->values[csv->numLines][4], profile.food, strlen(profile.food)+1);
    strncpy(csv->values[csv->numLines][5], profile.paper, strlen(profile.paper)+1);
    strncpy(csv->values[csv->numLines][6], profile.algorithm, strlen(profile.algorithm)+1);
    strncpy(csv->values[csv->numLines][7], profile.avenger, strlen(profile.avenger)+1);
    strncpy(csv->values[csv->numLines][8], profile.best, strlen(profile.best)+1);

    csv->numLines++;
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

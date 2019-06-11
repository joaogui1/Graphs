#ifndef CSV_H
#define CSV_H

#include "profile.h"

typedef struct{
    char** metadados;
    char*** values;
    int numColumns;
    int numLines;
} CSVFile;

CSVFile* new_CSVFile();
int readCSV(CSVFile* file, const char* fileName);
int writeCSV(CSVFile* file, const char* fileName);
void setDefaultHeader(CSVFile* csv);
void addProfile(CSVFile* file, Profile profile);
void DestroyCSV(CSVFile* file);
//void addColumn(CSVFile* file, char* name, char** values);
//void addLine(CSVFile* file, char** values);
int teste();

#endif

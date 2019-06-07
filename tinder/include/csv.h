#ifndef CSV_H
#define CSV_H

typedef struct{
    char** metadados;
    char*** values;
    int numColumns;
    int numLines;
} CSVFile;

CSVFile* new_CSVFile();
int readCSV(CSVFile* file, const char* fileName);
int writeCSV(CSVFile* file, const char* fileName);
void addColumn(CSVFile* file, char* name, char** values);
void addLine(CSVFile* file, char** values);
int teste();

#endif

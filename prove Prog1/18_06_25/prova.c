//./prova input.txt output.bin
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 100
#define MAX_LEN 21
#define MAX_RECORD 200

typedef struct{
    char fileInput[LEN];
    char fileOutput[LEN];
}ParametriInput;

typedef struct{
    char key[MAX_LEN]; //parola
    int lenght; //lunghezza parola

} Record;

ParametriInput readInput(int argc, char *argv[]);
void buildArray(const char *fileName, Record record[], size_t size);
void filter(Record record[]);
void createSet(Record record[]);
void printArray(Record record[]);
void save(const char *fileName, Record record[]);
void read(const char *filename);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\noutput: %s\n", parametri.fileInput, parametri.fileOutput);

    Record record[MAX_RECORD];
    buildArray(parametri.fileInput, record, MAX_RECORD);
    filter(record);
    createSet(record);
    printArray(record);
    save(parametri.fileOutput, record);
    read(parametri.fileOutput);
}

void read(const char *fileName){
    FILE *fPtr = fopen(fileName, "rb");
    if(fPtr == NULL){
        fprintf(stderr, "errore nell'apertura del file. controllare se %s e' un nome valido\n", fileName);
        exit(EXIT_FAILURE);
    }
    printf("\nlettura file output.bin:\n");
    Record record;
    while(fread(&record, sizeof(Record), 1, fPtr) == 1 && !feof(fPtr)){
        printf("%s [%d]\n", record.key, record.lenght);
    }
    fclose(fPtr);
}

void save(const char *fileName, Record record[]){
    FILE *fPtr = fopen(fileName, "wb");
    if(fPtr == NULL){
        fprintf(stderr, "errore nell'apertura del file. controllare se %s e' un nome valido\n", fileName);
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < MAX_RECORD;i++){
        if(record[i].lenght != -1)
            fwrite(&record[i], sizeof(Record), 1, fPtr);
        }
        
    fclose(fPtr);
}

void printArray(Record record[]){
    printf("\nstampa array:\n");
    for(size_t i = 0; i < MAX_RECORD; i++){
        if(record[i].lenght > 0 && record[i].lenght < MAX_LEN){
            printf("%s [%d]\n", record[i].key, record[i].lenght);
        }
    }
}

void createSet(Record record[]){
    for(size_t i = 0; i < MAX_RECORD - 1; i++){
        if(record[i].lenght <= 0){
            continue;
        }
        for(size_t j = i + 1; j < MAX_RECORD; j++){
            if(record[j].lenght <= 0){
            continue;
        }
            if(strcmp(record[i].key, record[j].key) == 0){
                record[j].lenght = -1;
            }
        }
    }
}

void filter(Record record[]) {
    for (size_t i = 0; i < MAX_RECORD && record[i].lenght > 0; i++) {
        char buffer[MAX_LEN];
        int z = 0;

        for (int j = 0; j < record[i].lenght; j++) {
            unsigned char c = (unsigned char)record[i].key[j];
            if (c != ',' && c != ';' && c != ':' && c != '.') {
                buffer[z++] = c;
            }
        }

        buffer[z] = '\0';
        strcpy(record[i].key, buffer);
        record[i].lenght = strlen(buffer);
    }
}

void buildArray(const char *fileName, Record record[], size_t size){
    FILE *fPtr = fopen(fileName, "r");
    if(fPtr == NULL){
        fprintf(stderr, "errore nell'apertura del file. controllare se %s e' un nome valido\n", fileName);
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_LEN];
    int i = 0;
    while(fscanf(fPtr, "%20s", buffer) == 1){
        strncpy(record[i].key, buffer, MAX_LEN - 1);
        record[i].key[MAX_LEN - 1] = '\0';
        record[i].lenght = strlen(buffer);
        i++;
    }
    if(i < MAX_RECORD){
        record[i].lenght = -1;
        i++;
    }
}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 3){
        fprintf(stderr, "use: %s <fileInput> <fileOutput>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.fileInput, argv[1], LEN - 1);
    parametri.fileInput[LEN -1] = '\0';

    strncpy(parametri.fileOutput, argv[2], LEN - 1);
    parametri.fileOutput[LEN -1] = '\0';

    return parametri;
}


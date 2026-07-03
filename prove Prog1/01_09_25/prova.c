#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_FILE 100
#define LEN 30
#define MAX_ARRAY 30

typedef struct{
    char inputF[MAX_FILE];
    char outputF[MAX_FILE];
}ParametriInput;

typedef struct{
    char codice[LEN];
    char nome[LEN];
    char cognome[LEN];
    int eta;
}Record;

ParametriInput readInput(int argc, char *argv[]);
void buildArray(Record array[], const char *inputF, size_t size);
void printRecord(Record array[], size_t size);
void sortArray(Record array[], size_t size);
void elab(Record array[], const char *outputF, size_t size);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\toutput: %s\n", parametri.inputF, parametri.outputF);

    Record array[MAX_ARRAY];
    buildArray(array, parametri.inputF, MAX_ARRAY);
    printRecord(array, MAX_ARRAY);
    sortArray(array, MAX_ARRAY);
    printRecord(array, MAX_ARRAY);
    elab(array, parametri.outputF, MAX_ARRAY);
}

void elab(Record array[], const char *outputF, size_t size){
    FILE *fptr = fopen(outputF, "w");

    if(fptr == NULL){
        fprintf(stderr, "impossibile creare il file\n");
        exit(EXIT_FAILURE);
    }
    
    for(size_t i = 0; i < size; i++){
        char iniziale = tolower(array[i].codice[0]);
        if(array[i].eta > 0 && (iniziale == 'x' || iniziale == 'z')){
            fprintf(fptr, "%-15s%-15s%-15s%-15d\n",
            array[i].codice, array[i].nome, array[i].cognome, array[i].eta);
        }
    }

    fclose(fptr);
}

void sortArray(Record array[], size_t size){
    for(size_t i = 1; i < size; i++){
        size_t posizione = i;
        Record elemento = array[i];

        if(array[i].eta <= 0) continue;

        while(posizione > 0 && strcmp(array[posizione-1].cognome, elemento.cognome) > 0){
            array[posizione] = array[posizione - 1];
            --posizione;
        }

        array[posizione] = elemento;
    }
}

void printRecord(Record array[], size_t size){
    for(size_t i = 0; i < size && strlen(array[i].codice) > 0; i++){
        printf("%-15s%-15s%-15s%-15d\n", array[i].codice, array[i].nome, array[i].cognome, array[i].eta);
    }
    puts("");
}

void buildArray(Record array[], const char *inputF, size_t size){
    FILE *fPtr = fopen(inputF, "rb");
    
    if(fPtr == NULL){
        fprintf(stderr, "errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    Record record = {" ", " ", " ", 0};
    size_t i = 0;

    while(i < size && (fread(&record, sizeof(Record), 1, fPtr)) == 1){
        array[i++] = record;
    }

    fclose(fPtr);
}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;

    if(argc != 3){
        fprintf(stderr, "use: %s <inputFile> <outputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.inputF, argv[1], MAX_FILE-1);
    parametri.inputF[MAX_FILE-1] = '\0';

    strncpy(parametri.outputF, argv[2], MAX_FILE-1);
    parametri.outputF[MAX_FILE-1] = '\0';

    return parametri;
}


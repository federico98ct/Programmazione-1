//OUTPUT DI CONTROLLO  
//./prova eventi.bin output.txt 800  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 31

typedef struct{
    char inputFile[100];
    char outputFile[100];
    int k;
}ParametriInput;

typedef struct{
    char codiceEvento[MAX_LEN];
    char nomeLuogo[MAX_LEN];
    int capienzaMax;
}Record;

struct lista{
    Record record;
    struct lista* nextPtr;
};

typedef struct lista Lista;
typedef Lista *ListaPtr;

ParametriInput readInput(int argc, char* argv[]);
ListaPtr buildList(const char *fileName);
void insertRecord(Record record, ListaPtr *sPtr);
void printList(ListaPtr sPtr);
void elab(const char *fileName, ListaPtr sPtr, int k);

int main(int argc, char* argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\noutput: %s\nk: %d\n", parametri.inputFile, parametri.outputFile, parametri.k);

    ListaPtr startPtr = buildList(parametri.inputFile);
    elab(parametri.outputFile, startPtr, parametri.k);

}

void elab(const char *fileName, ListaPtr sPtr, int k){
    FILE *fPtr = fopen(fileName, "w");
    if(fPtr == NULL){
        fprintf(stderr, "impossibile aprire il file\n");
        exit(EXIT_FAILURE);
    }

    while(sPtr != NULL){
        if(sPtr->record.capienzaMax > k){
            fprintf(fPtr,"%s %s %d\n", sPtr->record.codiceEvento, sPtr->record.nomeLuogo, sPtr->record.capienzaMax);
        }
        ListaPtr temp = sPtr;
        sPtr = sPtr->nextPtr;
        free(temp);
    }
    fclose(fPtr);
}

void printList(ListaPtr sPtr){
    if(sPtr == NULL){
        printf("la lista e' vuota\n");
        exit(EXIT_FAILURE);
    }
    while(sPtr != NULL){
        printf("%s %s %d\n", sPtr->record.codiceEvento, sPtr->record.nomeLuogo, sPtr->record.capienzaMax);
        sPtr = sPtr->nextPtr;
    }
}

ListaPtr buildList(const char *fileName){
    FILE *fptr = fopen(fileName, "rb");
    if(fptr == NULL){
        fprintf(stderr, "impossibile aprire il file\n");
        exit(EXIT_FAILURE);
    }

    Record record;
    ListaPtr startPtr = NULL;
    while(fread(&record, sizeof(Record), 1, fptr) == 1){
        insertRecord(record, &startPtr);
    }
    fclose(fptr);
    printList(startPtr);
    return startPtr;
}

void insertRecord(Record record, ListaPtr *sPtr){
    ListaPtr newPtr = malloc(sizeof(Lista));
    if(newPtr == NULL){
        fprintf(stderr, "impossibile allocare nuova memoria\n");
        exit(EXIT_FAILURE);
    }
    newPtr->record = record;
    newPtr->nextPtr = NULL;

    ListaPtr previousPtr = NULL;
    ListaPtr currentPtr = *sPtr;

    while(currentPtr != NULL && strcmp(newPtr->record.codiceEvento, currentPtr->record.codiceEvento) > 0){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }
    if(previousPtr == NULL){
        newPtr->nextPtr = *sPtr;
        *sPtr = newPtr;
    }
    else{
        previousPtr->nextPtr = newPtr;
        newPtr->nextPtr = currentPtr;
    }
}

ParametriInput readInput(int argc, char* argv[]){
    ParametriInput parametri;
    if(argc != 4){
        fprintf(stderr, "Uso: %s <inputFile> <outputFile> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int lunghezza = sizeof(parametri.inputFile) - 1;
    strncpy(parametri.inputFile, argv[1], lunghezza);
    parametri.inputFile[lunghezza] = '\0';

    strncpy(parametri.outputFile, argv[2], lunghezza);
    parametri.outputFile[lunghezza] = '\0';

    char *endPtr = NULL;
    int k = strtol(argv[3], &endPtr, 10);
    if(*endPtr != '\0'){
        perror("errore k non valido\n");
        exit(EXIT_FAILURE);
    }
    parametri.k = k;

    return parametri;
}

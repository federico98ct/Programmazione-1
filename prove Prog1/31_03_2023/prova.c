#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILE 100
#define LEN 31

typedef struct{
    char inputFile[MAX_FILE];
    int k;
}ParametriInput;

struct lista{
    char stringa[LEN];
    struct lista* nextPtr;
    struct lista* prevPtr;
};

typedef struct lista Lista;
typedef Lista* ListaPtr;

ParametriInput readInput(int argc, char *argv[]);
void buildList(ListaPtr *sPtr, const char *inputFile);
void insertWord(ListaPtr *sPtr, const char stringa[]);
void printList(ListaPtr sPtr);
void elab(ListaPtr sPtr, int k);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\tk: %d\n", parametri.inputFile, parametri.k);

    ListaPtr startPtr = NULL;
    buildList(&startPtr, parametri.inputFile);
    printList(startPtr);
    elab(startPtr, parametri.k);
}

void elab(ListaPtr sPtr, int k){
    while(sPtr != NULL){
        int dimensione = strlen(sPtr->stringa);
        if(dimensione >= k){
            printf("%s\n", sPtr->stringa);
        }
        sPtr = sPtr->nextPtr;
    }
}

void printList(ListaPtr sPtr){
    while(sPtr != NULL){
        printf("%s\n", sPtr->stringa);
        sPtr = sPtr->nextPtr;
    }
    puts(" ");
}

void insertWord(ListaPtr *sPtr, const char stringa[]){
    ListaPtr newPtr = malloc(sizeof(Lista));

    if(newPtr == NULL){
        fprintf(stderr, "impossibile allocare nuovs memoria\n");
        exit(EXIT_FAILURE);
    }

    newPtr->nextPtr = NULL;
    newPtr->prevPtr = NULL;
    strncpy(newPtr->stringa, stringa, LEN-1);
    newPtr->stringa[LEN-1] = '\0';

    ListaPtr currentPtr = *sPtr;
    ListaPtr previousPtr = NULL;

    while(currentPtr != NULL && strcmp(currentPtr->stringa, stringa) < 0){
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }

    newPtr->nextPtr = currentPtr;
    newPtr->prevPtr = previousPtr;

    if (previousPtr != NULL)
        previousPtr->nextPtr = newPtr;
    else
        *sPtr = newPtr;

    if (currentPtr != NULL)
        currentPtr->prevPtr = newPtr;
}

void buildList(ListaPtr *sPtr, const char *inputFile){
    FILE *fPtr = fopen(inputFile, "r");

    if(fPtr == NULL){
        fprintf(stderr, "errore nell'apertura del file\n");
        exit(EXIT_FAILURE);
    }

    char stringa[LEN];

    while(fscanf(fPtr, "%s", stringa) == 1){
        insertWord(sPtr, stringa);
    }

}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;

    if(argc != 3){
        fprintf(stderr, "use: %s <inputFile> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.inputFile,  argv[1], MAX_FILE-1);
    parametri.inputFile[MAX_FILE-1] = '\0';

    int numero = atoi(argv[2]);
    if(numero >= 7 && numero <= 13){
        parametri.k = numero;
    }
    else{
        fprintf(stderr, "inserire un numero compreso tra 7 e 13\n");
        exit(EXIT_FAILURE);
    }

    return parametri;
}
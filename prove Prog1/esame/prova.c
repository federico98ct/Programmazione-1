//FEDERICO ARENA

// FM ** 29 **

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE 100
#define LEN 21
#define MAX_ARRAY 200

typedef struct{
    char inputFile[MAX_FILE];
    int k;
}ParametriInput;

typedef struct{
    char key[LEN];
    int length;
}Record;

ParametriInput readInput(int argc, char *argv[]);
void buildArray(Record array[], size_t size, const char *inputFile);
void filter(Record array[], size_t size);
void createSet(Record array[], size_t size);
void printArray(Record array[], size_t  size, int k);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\tk: %d\n", parametri.inputFile, parametri.k);

    Record array[MAX_ARRAY];
    buildArray(array, MAX_ARRAY, parametri.inputFile);
    filter(array, MAX_ARRAY);
    createSet(array, MAX_ARRAY);
    printArray(array, MAX_ARRAY, 1);
    puts(" ");
    printArray(array, MAX_ARRAY, parametri.k);
}

void printArray(Record array[], size_t  size, int k){

    int j = 1;

    for(size_t i = 0; i < size; i++){
        if(array[i].length >= k){
            printf("[%d] %-20s\t%10s%d (>= %d)\n", j, array[i].key, "lunghezza: ", array[i].length, k);
            j++;
        }
    } 
    
}

void createSet(Record array[], size_t size){
    for(size_t i = 0; i < size; i++){
            for(size_t j = i + 1; j < size; j++){   
                if(strcmp(array[i].key, array[j].key) == 0){
                    array[i].length = -1;
                }
            }
    }
}

void filter(Record array[], size_t size){
    for(size_t i = 0; i < size; i++){
        if(array[i].length != -1){
            for(size_t j = 0; j < array[i].length; j++){
                if(array[i].key[j] == ',' || array[i].key[j] == ';' || array[i].key[j] == ':' || array[i].key[j] == '.'){
                    array[i].key[j] = '\0';
                    int lunghezza = strlen(array[i].key);
                    array[i].length = lunghezza;
                }
            }
        }
    }
}

void buildArray(Record array[], size_t size, const char *inputFile){
    FILE *fPtr = fopen(inputFile, "r");

    if(fPtr == NULL){
        fprintf(stderr, "impossibile aprire il file\n");
        exit(EXIT_FAILURE);
    }

    char stringa[LEN];
    for(size_t i = 0; i < size; i++){
        if(fscanf(fPtr, "%s", stringa) == 1){
            strcpy(array[i].key, stringa);
            int lunghezza = strlen(array[i].key);
            array[i].length = lunghezza;
        }
        else{
            array[i].length = -1;
        }
    }
    

}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;

    if(argc != 3){
        fprintf(stderr, "use: %s <inputFile> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.inputFile, argv[1], MAX_FILE-1);
    parametri.inputFile[MAX_FILE-1] = '\0';

    int numero = atoi(argv[2]);

    if(numero >= 5 && numero <= 10){
        parametri.k = numero;
    }
    else{
        fprintf(stderr, "inserire un numero che siaompreso tra 5 e 10\n");
        exit(EXIT_FAILURE);
    }

    return parametri;
}

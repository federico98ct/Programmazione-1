/*
 Scrivere un programma in C che:

 ● A. Prenda un input da tastiera (argomenti della funzione
 main) costituito dal nome di un file di testo (ES: input.txt)
 e due lettere minuscole dell’alfabeto a e b, per cui sia
 a<=b. Il file contiene una collezione di stringhe, una per
 riga; si suppone che la lunghezza di ogni stringa sia non
 superiore ai 30 caratteri;
 
 ● B. Legga tutte le stringhe contenute nel file di input e le
 memorizzi in una struttura dati dinamica di tipo FIFO (una
 CODA);
 
 ● C. Stampi tutte le stringhe, estraendole dalla coda, mediante
 una sequenza di operazioni ``dequeue``;
 
 ● D. con riferimento al punto C, tutti i caratteri delle
 stringhe compresi nell’intervallo [a, b], siano sostituiti, a
 schermo, dal carattere ‘0’ (zero).
 Specifiche
 
 Il programma potra’ essere strutturato in un unico file sorgente,
 ma dovra’ contenere almeno le seguenti funzioni:
 
 ● enqueue(): funzione che inserisce una stringa in coda;
 
 ● deQueue(): funzione che preleva una stringa dalla coda;
 
 ● buildQueue(): funzione che legge le stringhe presenti nel
 file e le inserisce una alla volta sullo stack mediante la
 funzione enqueue();
 
 ● elab(): funzione che prende in input una stringa e due
 caratteri a e b, e restituisca la stringa stessa in cui i
 caratteri contenuti nello intervallo [a,b] siano sostituiti
 con il carattere ‘0’ (zero).
 
 ● printQueue(): funzione che rimuove dalla coda e stampa tutte
 le stringhe contenute nella coda stessa, nel modo descritto
 nel punto D.
 
 È VIETATO usare variabili globali.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 100
#define MAX_LEN 30

typedef struct{
    char inputFile[LEN];
    char a;
    char b;
}ParametriInput;

struct lista{
    char stringa[MAX_LEN];
    struct lista* nextPtr;
};

typedef struct lista Lista;
typedef Lista* ListaPtr;

ParametriInput readInput(int argc, char *argv[]);
void buildqueue(const char *fileName);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\na: %c\nb: %c\n", parametri.inputFile, parametri.a, parametri.b);

}

void buildqueue(const char *fileName){
    FILE *fPtr = fopen(fileName, "w");
    if(fPtr == NULL){
        fprintf(stderr, "impossibile aprire il file\n");
        exit(EXIT_FAILURE);
    }

}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 4){
        fprintf(stderr, "use: %s <inputFile> <f>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.inputFile, argv[1], LEN);
    parametri.inputFile[LEN-1] = '\0';

    if (strlen(argv[2]) == 1 && isalpha(argv[2][0]) && islower(argv[2][0]) &&
        strlen(argv[3]) == 1 && isalpha(argv[3][0]) && islower(argv[3][0])) {
    
        // Controllo che a <= b
        if (argv[2][0] > argv[3][0]) {
            fprintf(stderr, "La lettera a deve essere minore o uguale alla lettera b\n");
            exit(EXIT_FAILURE);
        }

        parametri.a = argv[2][0];
        parametri.b = argv[3][0];
    }
    else{
        fprintf(stderr, "le lettere devono essere entrambe minuscole\n");
        exit(EXIT_FAILURE);
    }

    return parametri;
}


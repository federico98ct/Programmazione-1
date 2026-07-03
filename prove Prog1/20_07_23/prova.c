/*Scrivere un programma in C che:

il file contiene una matrice di double di dimensione N
x M, dove ogni riga del file di testo contiene una riga della matrice
stessa. I numeri N ed M dovranno essere contenuti nell’intervallo
[5,10];

● B. il programma crei in memoria una matrice A di dimensioni N x M di
puntatori a double. La matrice sia popolata da puntatori a celle
double che contengono i corrispondenti numeri presenti nel file di
input.

● C. Si crei una nuova matrice B di dimensioni N x M di puntatori a
double, in cui ogni singolo valore della matrice corrispondera’ al
valore corrispondente della matrice A, normalizzato rispetto al
massimo valore della colonna stessa di A, quindi:
 ○ B[i][j] = A[i][j]/MAX_A_j, dove MAX_A_j rappresenta il valore
massimo della colonna j-esima della matrice A, (i in [0,N-1] e j
in [0,M-1]).

● D. Si stampi, sullo standard output, la matrice A e la matrice B;

● E. Mediante un qualunque algoritmo di ordinamento (insertion sort /
bubble sort / selection sort), si ordini in modo crescente ogni
colonna della matrice B, e la si stampi sullo standard output;
Il programma potra’ essere strutturato in un unico file sorgente, ma
dovra’ contenere almeno le seguenti funzioni:

● allocateMatrix: funzione che crea una matrice di puntatori a double
delle dimensioni specificate tra i parametri formali;

● fillMatrix: funzione che legge il file di input e popola la
corrispondente matrice di puntatori a double;

● printMatrix: funzione che stampa una matrice sullo standard output;

● normalize: funzione che, presa una matrice sorgente ed una matrice
destinazione, popola la matrice destinazione sulla base si quanto
esposto al punto C

● sortMatrixCols: funzione che ordina le colonne di una matrice in input
in modo crescente.*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define LEN 100

typedef struct{
    char inputFile[LEN];
    int N;
    int M;
}ParametriInput;


//prototipi
ParametriInput readInput(int argc, char *argv[]);
double ***allocateMatrix(int N, int M);
double fillMatrix(FILE *fPtr);


//main
int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("input: %s\nN: %d\nM: %d\n\n", parametri.inputFile, parametri.N, parametri.M);

    double ***A = allocateMatrix(parametri.N, parametri.M);
    
}

double ***allocateMatrix(int N, int M){
    
}

double fillMatrix(FILE *fPtr){
    double buffer;
    fscanf(fPtr, "%lf ", &buffer);
    printf("n = %.2f ", buffer);

    return buffer;
}


ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 4){
        fprintf(stderr, "use: %s <inputFile> <N> <M>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.inputFile, argv[1], LEN - 1);
    parametri.inputFile[LEN - 1] = '\0';

    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    if(N < 5 || N > 10 || M < 5 || M > 10){
        fprintf(stderr, "N ed M devono essere numeri interi compresi tra 5 e 10\n");
        exit(EXIT_FAILURE);
    }

    parametri.N = N;
    parametri.M = M;

    return parametri;
}

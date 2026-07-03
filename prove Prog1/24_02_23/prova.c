#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int N;
    char a;
    char b;
}ParametriInput;

ParametriInput readInput(int argc, char *argv[]);

int main(int argc, char *argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("N = %d\ta = %c\tb = %c\n", parametri.N, parametri.a, parametri.b);
}

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 4){
        fprintf(stderr, "use: %s <N> <a> <b>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    if(N < 5 || N > 10){
        fprintf(stderr, "valore di N non valido, inserire numero compreso tra 5 e 10\n");
        exit(EXIT_FAILURE);
    }
    parametri.N = N;

    if(strlen(argv[2]) > 1 || strlen(argv[3]) > 1){
        fprintf(stderr, "inserire un solo carattere per 'a' e 'b'\n");
        exit(EXIT_FAILURE);
    }
    if(argv[2][0] < 'a' || argv[2][0] > 'z' || argv[3][0] < 'a' || argv[3][0] > 'z'){
        fprintf(stderr, "inserire per 'a' e 'b' solo lettere tra a e z\n");
        exit(EXIT_FAILURE);
    }
    parametri.a = argv[2][0];
    parametri.b = argv[3][0];

    return parametri;
}
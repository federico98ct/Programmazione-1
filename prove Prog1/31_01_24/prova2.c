/*Descrizione del programma 
Scrivere un programma in C che: 

A. Prenda un input da tastiera (argomenti della funzione main) 
costituito da due caratteri a e b, due numeri interi x e y, ed un 
numero intero n. Tali parametri devono rispettare le seguenti 
specifiche:  
- I due caratteri a e b devono appartenere al range [‘a’,’z’] 
oppure [‘A’, ‘Z’] (quindi entrambi minuscoli o entrambi 
maiuscoli); inoltre deve essere a<=b. Quindi ad esempio 
a=’C’, b=’Y’ oppure a=’d’, b=’h’; 
- numeri x e y devono appartenere al range [5,30], ed inoltre 
deve essere y-x>5;  
- il numero n deve appartenere al range [15,25].   

B. Produca n stringhe  che rispettino le seguenti specifiche:  
- Ogni stringa sia generata con caratteri pseudo-casuali 
appartenenti al range [a,b]; 
- la lunghezza di ogni stringa, sia L, dovra’ essere un 
numero subpseudo-casuale appartenente al range [x,y] (per 
ogni stringa sara’ generato un nuovo numero L in [x,y]). 

C. inserisca ogni stringa in una struttura dati dinamica CODA, e le 
stampi sullo standard output. 

D. Rimuova dalla coda tutti gli elementi e stampi sullo standard 
output le stringhe contenute all’interno di tali elementi, come 
specificato nel successivo punto E. 

E. Con riferimento al punto D, in fase di output, le vocali di ogni 
stringa andranno sostituite con il carattere ‘X’ (x maiuscolo).     
Specifiche 

Il programma potra’ essere strutturato in un unico file sorgente, ma 
dovra’ contenere almeno le seguenti funzioni: 

3. enqueue() e dequeue(): funzioni per la gestione della coda;  

Generazione di numeri pseudocasuali: 
• Si consideri la seguente funzione get_random() per la generazione 
di numeri pseudo-casuali interi positivi (qualora necessaria): 
unsigned int get_random() { 
static unsigned int m_w = 123456; 
static unsigned int m_z = 789123; 
m_z = 36969 * (m_z & 65535) + (m_z >> 16); 
m_w = 18000 * (m_w & 65535) + (m_w >> 16); 
return (m_z << 16) + m_w; 
} 
NB: Ai fini della eventuale generazione di numeri in virgola mobile, si 
faccia uso della costante UINT_MAX (<limits.h>) unitamente alla funzione 
get_random().
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_LEN 31

typedef struct{
    char a, b;
    int x, y;
    int n;
}ParametriInput;

struct coda{
    char stringa[MAX_LEN];
    struct coda* nextPtr;

};
typedef struct coda Coda;
typedef Coda* CodaPtr;


ParametriInput readInput(int argc, char *argv[]);
unsigned int get_random();
void buildQueue(CodaPtr* headPtr, CodaPtr* tailPtr, ParametriInput parametri);
void genString(int min, int max, int lunghezza, char stringa[]);
void queue(CodaPtr *headPtr, CodaPtr *tailPtr, char stringa[]);
void dequeue(CodaPtr* headPtr, char stringa[]);
void prinStrings(CodaPtr* headPtr);
void elabString(char stringa[]);



int main(int argc, char* argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("a = '%c' b = '%c' x = %d y = %d n = %d\n", parametri.a, parametri.b, parametri.x, parametri.y, parametri.n);

    CodaPtr testaPtr = NULL;
    CodaPtr codaPtr = NULL;
    buildQueue(&testaPtr, &codaPtr, parametri);
    prinStrings(&testaPtr);

}

/* 1. readInput(): funzione che prende in input l'array di puntatori a 
carattere argv ed il numero di argomenti argc della funzione 
main, controlla che gli argomenti richiesti siano nel numero e 
nei limiti specificati, e restituisca parametri {x,y,a,b,n} in 
una struct da restituire al chiamante.  */

ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 6){
        fprintf(stderr, "use: %s <a> <b> <x> <y> <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //controllo di a e b
    char a = *argv[1];
    char b = *argv[2];
    if(a >= 'a' && a <= 'z' && b >= 'a' && b <= 'z'){
        if(a > b){
            fprintf(stderr, "a deve essere minore o uguale a b\n");
            exit(EXIT_FAILURE);
        }
    }
    else if(a >= 'A' && a <= 'Z' && b >= 'A' && b <= 'Z'){
        if(a > b){
            fprintf(stderr, "a deve essere minore o uguale a b\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        fprintf(stderr, "i caratteri inseriti non sono entrambi maiuscoli o entrambi minuscoli\n");
        exit(EXIT_FAILURE);
    }
    
    //controllo x e y
    char *endPtr = NULL;
    int x = strtol(argv[3], &endPtr, 10);
    if(*endPtr != '\0'){
        fprintf(stderr, "errore: %s non e' un numero valido per x\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    int y = strtol(argv[4], &endPtr, 10);
    if(*endPtr != '\0'){
        fprintf(stderr, "errore: %s non e' un numero valido per y\n", argv[4]);
        exit(EXIT_FAILURE);
    }

    if(x < 5 || x > 30 || y < 5 || y > 30 || y - x < 5){
        fprintf(stderr, "x e y devono rientrare nel range 5-30 e la differenza y - x deve essere maggiore di 5\n");
        exit(EXIT_FAILURE);
    }

    //controllo n
    int n = strtol(argv[5], &endPtr, 10);
    if(*endPtr != '\0'){
        fprintf(stderr, "errore: %s non e' un numero valido per n\n", argv[5]);
        exit(EXIT_FAILURE);
    }
    if(n < 15 || n > 25){
        fprintf(stderr, "n deve rientrare nel range 15-25\n");
        exit(EXIT_FAILURE);
    }

    parametri.a = a;
    parametri.b = b;
    parametri.x = x;
    parametri.y = y;
    parametri.n = n;

    return parametri;
}

/*4. buildQueue(): funzione che crea una coda di stringhe sulla base 
delle specifiche presenti al punto C, utilizzando opportunamente 
la funzione genString() e la funzione enqueue(). La funzione 
dovra’ stampare tutte le stringhe generate e inserite nella coda. */

void buildQueue(CodaPtr* headPtr, CodaPtr* tailPtr, ParametriInput parametri){
    for(size_t i = 0; i < parametri.n; i++){
        int lunghezza= parametri.x +(get_random() % (parametri.y - parametri.x + 1));

        char stringa[MAX_LEN];
        genString(parametri.a, parametri.b, lunghezza, stringa);
        printf("Stringa %zu: %s\n", i + 1, stringa);
        queue(headPtr, tailPtr, stringa);
    }
}

/*2. genString(): funzione con opportuni parametri formali, che 
produca una stringa sulla base delle specifiche descritte nel 
punto B. NB: usare la funzione di generazione di numeri pseudo
casuali riportata in seguito nel testo (get_random()). */

void genString(int min, int max, int lunghezza, char stringa[]){
    int i = 0;
    for(; i < lunghezza; i++){
        char c = min +(get_random() % (max - min + 1));
        stringa[i] = c;
    }
    stringa[i] = '\0';
}

unsigned int get_random() { 
    static unsigned int m_w = 123456; 
    static unsigned int m_z = 789123; 
    m_z = 36969 * (m_z & 65535) + (m_z >> 16); 
    m_w = 18000 * (m_w & 65535) + (m_w >> 16); 
    return (m_z << 16) + m_w; 
} 

void queue(CodaPtr *headPtr, CodaPtr *tailPtr, char stringa[]){
    CodaPtr newPtr = malloc(sizeof(Coda));
    if (newPtr == NULL) {
        fprintf(stderr, "Impossibile allocare nuova memoria\n");
        exit(EXIT_FAILURE);
    }

    strncpy(newPtr->stringa, stringa, MAX_LEN - 1);
    newPtr->stringa[MAX_LEN - 1] = '\0';
    newPtr->nextPtr = NULL;

    if (*headPtr == NULL) {
        // La coda è vuota
        *headPtr = newPtr;
        *tailPtr = newPtr;
    } else {
        // Inserimento in coda
        (*tailPtr)->nextPtr = newPtr;
        *tailPtr = newPtr;
    }
}

void dequeue(CodaPtr* headPtr, char stringa[]){
    CodaPtr temp = *headPtr;
    strcpy(stringa, (*headPtr)->stringa);
    *headPtr = (*headPtr)->nextPtr;
    free(temp);
}

/*5. printStrings(): funzione che rimuove tutti gli elementi dalla 
coda mediante la funzione deQueue() e che stampi le stringhe nel 
modo specificato nel punto E mediante la funzione elabString() 
descritta al prossimo punto. */

void prinStrings(CodaPtr* headPtr){
    printf("stringhe formattate:\n");
    int i = 1;
    while(*headPtr != NULL){
        char stringa[MAX_LEN];
        dequeue(headPtr, stringa);
        elabString(stringa);
        printf("Stringa %zu: %s\n", i++, stringa);
    }
}

/* 6. elabString(): funzione che prenda in input una stringa e 
modifichi la stringa (o restituisca una copia) in cui le vocali 
sono state sostituite con il carattere ‘X’ (x maiuscolo). */ 
 void elabString(char stringa[]){
    int lunghezza = strlen(stringa);
    for(size_t i = 0; i < lunghezza; i++){
        if (strchr("aeiouAEIOU", stringa[i])) {
        stringa[i] = 'X';
        }       
    }
 }


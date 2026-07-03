/*Scrivere un programma in C che: 
A. Prenda un input da tastiera (argomenti della funzione main) 
costituito da due numeri in virgola mobile x e y, ed un numero 
intero n. Tali parametri devono rispettare le seguenti 
specifiche:  
- I numeri x e y devono entrambi appartenere al range 
[1.0,1000.0], y>x, ed infine deve essere (y-x)>500.0;  
  il numero n deve appartenere al range [20,30].   

B. Produca n numeri in virgola mobile (double) che appartengano al 
range [x, y];  

C. Inserisca ogni numero in una struttura dati dinamica PILA, e tale 
numero sia stampato sullo standard output. 

D. Rimuova dalla pila tutti gli elementi e stampi sullo standard 
output i numeri contenuti all’interno degli elementi stessi.  

E. Con riferimento al punto D, gli elementi rimossi dalla pila vanno 
contestuamente salvati all’interno di un array di n elementi 
double.  

F. Si stampi infine la media degli n valori contenuti all’interno 
dell’array ed il numero di elementi che risultino maggiori della 
media stessa.  
Specifiche 

Il programma potra’ essere strutturato in un unico file sorgente, ma 
dovra’ contenere almeno le seguenti funzioni: 
 

3. Push() e Pop(): funzioni per la gestione della pila; 


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
get_random().*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_RIGHE 500
#define MAX_COLONNE 1000

typedef struct {
    double x, y;
    int n;
} ParametriInput;

struct pila{
    double numero;
    struct pila* nextPtr;
};

typedef struct pila Pila;
typedef Pila* PilaPtr;

/*1. readInput(): funzione che prende in input l'array di puntatori a 
carattere argv ed il numero di argomenti argc della funzione 
main, controlla che gli argomenti richiesti siano nel numero e 
nei limiti specificati, e restituisca i parametri {x,y,n} in una 
struct da restituire al chiamante. */

ParametriInput readInput(int argc, char* argv[]){
    ParametriInput parametri;
    if(argc != 4){
        fprintf(stderr, "use: %s <x> <y> <n>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* endPtr = NULL;
    double x = strtod(argv[1], &endPtr);
    if (*endPtr != '\0') {
        fprintf(stderr, "Errore: '%s' non è un numero valido per x\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    double y = strtod(argv[2], &endPtr);
    if (*endPtr != '\0') {
        fprintf(stderr, "Errore: '%s' non è un numero valido per y\n", argv[2]);
        exit(EXIT_FAILURE);
    }


    if(x >= 1.0 && x <= 1000.0 && y >= 1.0 && y <= 1000.0 && y > x && (y - x) > 500.0){
        parametri.x = x;
        parametri.y = y;
    }
    else{
        fprintf(stderr, "Errore: x e y devono essere compresi nel range (1.0 - 1000.0), con y > x e (y - x) > 500.0\n");
        exit(EXIT_FAILURE);
    }

    int n = strtol(argv[3], &endPtr, 10);
    if (*endPtr != '\0') {
        fprintf(stderr, "Errore: '%s' non è un numero valido per n\n", argv[3]);
        exit(EXIT_FAILURE);
    }
    else if(n >= 20 && n <= 30){
        parametri.n = n;
    }
    else{
        fprintf(stderr, "Errore: n deve essere compreso nel range (20 - 30)\n");
        exit(EXIT_FAILURE);
    }

    return parametri;
}

/*2. genDouble(): funzione con opportuni parametri formali, che 
produca una valore sulla base delle specifiche descritte nel 
punto B. NB: usare opportunamente la funzione di generazione di 
numeri pseudo-casuali riportata in seguito nel testo 
(get_random()).  */

unsigned int get_random() { 
    static unsigned int m_w = 123456; 
    static unsigned int m_z = 789123; 
    m_z = 36969 * (m_z & 65535) + (m_z >> 16); 
    m_w = 18000 * (m_w & 65535) + (m_w >> 16); 
    return (m_z << 16) + m_w; 
} 

double genDouble(double min, double max){
    unsigned int r = get_random();
    double normalizzato = (double)r / (double)UINT_MAX;
    return min +(normalizzato *(max - min));
}

/* 4. buildStack(): funzione che crea una pila di numeri double sulla 
base delle specifiche presenti al punto C, utilizzando 
opportunamente la funzione geDouble() e la funzione push(). La 
funzione dovra’ stampare tutti i numeri generati ed inseriti 
nella pila. */

void push(PilaPtr *sPtr, double n){
    PilaPtr newPtr = malloc(sizeof(Pila));
    if(newPtr == NULL){
        fprintf(stderr, "non è stato possibile allocare nuova memoria\n");
        exit(EXIT_FAILURE);
    }
    newPtr->numero = n;
    newPtr->nextPtr = NULL;

    newPtr->nextPtr = *sPtr;
    *sPtr = newPtr;
}

void buildStack(ParametriInput parametri, PilaPtr* sPtr){
    printf("**buildStack()**\n");
    for(size_t i = 0; i < parametri.n; i++){
        double numero = genDouble(parametri.x, parametri.y);
        push(sPtr, numero);
        printf("dato inserito (%zu): %f\n", i, (*sPtr)->numero);
    }
    puts("");
}



/*5. buildArray(): funzione che rimuove tutti gli elementi dalla pila 
mediante la funzione pop(), che stampi i valori ed infine che li 
salvi all’interno di un un array di n double da restituire 
opportunamente al chiamante.  */

double pop(PilaPtr* sPtr){
    PilaPtr temp = *sPtr;
    double numero = (*sPtr)->numero;
    *sPtr = (*sPtr)->nextPtr;
    free(temp);

    return numero;
}

void buildArray(double array[],  PilaPtr* sPtr){
    int i = 0;
    printf("**buildArray()**\n");
    while(*sPtr != NULL){
        double numero = pop(sPtr);
        printf("Dato estratto (%zu): %f\n", i, numero);
        array[i++] = numero;
    }
    puts("");
}


/* 6. elabValues(): funzione che prende in input un array di n double, 
ne calcoli la media aritmetica e che successivamente stampi tale 
media ed il numero di valori dell’array che risultano maggiori di 
tale media. */

void elabValues(double array[], int size){
    double somma = 0.0;
    for(size_t i = 0; i <size; i++){
        somma += array[i];
    }
    double media = somma / size;
    printf("la media e': %f\n", media);

    int valori = 0;
    for(size_t i = 0; i < size; i++){
        if(array[i] > media){
            valori++;
        }
    }
    printf("ci sono %d valori piu' grandi della media\n", valori);
}

int main(int argc, char* argv[]){
    ParametriInput parametri = readInput(argc, argv);
    printf("x = %.2f\ny = %.2f\nn = %d\n", parametri.x, parametri.y, parametri.n);

    PilaPtr cimaPtr = NULL;
    buildStack(parametri, &cimaPtr);

    double array[parametri.n];
    buildArray(array, &cimaPtr);

    elabValues(array, parametri.n);
    
}
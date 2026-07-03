/*Descrizione del programma
 Scrivere un programma in C che:
 ● A. Prenda un input da tastiera (argomenti della funzione
 main) costituito dal nome di un file di testo (ES: input.txt)
 ed un numero intero “k” nell’intervallo [5-15]. il file
 contiene una collezione di stringhe, una per riga; si suppone
 che la lunghezza di ogni stringa sia non superiore ai 30
 caratteri;
 ● B. Legga tutte le stringhe contenute nel file di input e le
 memorizzi mediante operazioni ``push’’ in una PILA o stack;
 ● C. Stampi tutte le stringhe mediante una sequenza di
 operazioni di rimozione dallo stack (``pop’’).
 ● D. con riferimento al punto C, i caratteri delle stringhe che
 risultino di lunghezza maggiore o uguale al numero k andranno
 stampate in ordine lessicografico crescente.
 Specifiche
 Il programma potra’ essere strutturato in un unico file sorgente,
 ma dovra’ contenere almeno le seguenti funzioni:
 ● readInput: funzione che prende in input l'array di puntatori
 a carattere argv ed il numero di argomenti argc della
 funzione main, controlla che gli argomenti richiesti siano
 nel numero e nei limiti specificati, e restituisca tali
 parametri in una struct; se il controllo non va a buon fine,
 stampa un messaggio sullo standard error e termina il
 programma.
 ● pushWord: funzione che inserisce una stringa in uno stack di
 stringhe;
 ● popWord: funzione che preleva una stringa da uno stack di
 stringhe;
 ● buildStack: funzione che legge le stringhe presenti nel file
 e le inserisce una alla volta sullo stack mediante la
 funzione pushWord();
 ● sortWord: funzione che prende in input una stringa e
 restituisce una stringa con gli stessi caratteri in ordine
 lessicografico crescente. ES: absbfjridm--> abbdfijmrs
 ● printStack(): funzione che stampa (e rimuove) le stringhe
 contenute nello stack come indicato nei punti C e D.*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #define MAX_LEN 31

 typedef struct{
    char fileName[100];
    int k;
 }ParametriInput;

 struct pila{
   char stringa[MAX_LEN];
   struct pila* nextPtr;
 };

 typedef struct pila Pila;
 typedef Pila* PilaPtr;

  ParametriInput readInput(int argc, char *argv[]){
    ParametriInput parametri;
    if(argc != 3){
        fprintf(stderr, "Uso: %s <input.txt> <k>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int k = atoi(argv[2]);
    if(k < 5 || k > 15){
        fprintf(stderr, "Errore: k deve essere compreso tra 5 e 15.\n");
        exit(EXIT_FAILURE);
    }

    strncpy(parametri.fileName, argv[1], sizeof(parametri.fileName));
    parametri.k = k;

    return parametri;
 }

void  buildStack(char *fileName, PilaPtr *sPtr){
   FILE *file = fopen(fileName, "r");
   if(file == NULL){
      fprintf(stderr, "errore nell'apertura del file %s\n", fileName);
      exit(EXIT_FAILURE);
   }
   char buffer[MAX_LEN];
   while(fscanf(file, "%30s", buffer) == 1){
      
      pushWord(buffer, sPtr);
   }
   fclose(file);
 }

 void pushWord(char *stringa, PilaPtr* sPtr){
   PilaPtr newPtr = malloc(sizeof(Pila));
   if(newPtr == NULL){
      fprintf(stderr, "non è possibile allocare nuova memoria\n");
      exit(EXIT_FAILURE);
   }
   strncpy(newPtr->stringa, stringa, MAX_LEN-1);
   newPtr->stringa[MAX_LEN-1] = '\0';
   newPtr->nextPtr = NULL;

   newPtr->nextPtr = *sPtr;
   *sPtr = newPtr;

 }

 void printStack(PilaPtr* sPtr, int n){
   while (*sPtr!= NULL){
      int lunghezza = strlen((*sPtr)->stringa);
      if(lunghezza >= n){
         sortWord((*sPtr)->stringa);
      }
      char buffer[MAX_LEN];
      popWord(sPtr, &buffer);
      printf("%s\n", buffer);
   }
   
 }

 void sortWord(char *stringa){
   int lunghezza = strlen(stringa);
      for (int i = 1; i < lunghezza; i++) {
         int key = stringa[i];
         int j = i - 1;

         while (j >= 0 && stringa[j] > key) {
            stringa[j + 1] = stringa[j];
            j--;
         }

        stringa[j + 1] = key;
      }
}

void popWord(PilaPtr* sPtr, char *parola){
   PilaPtr temp = *sPtr;

   strcpy(parola, (*sPtr)->stringa);

   *sPtr = (*sPtr)->nextPtr;
   free(temp);
}


 int main(int argc, char *argv[]){
   ParametriInput parametri = readInput(argc, argv);
   printf("numero: %d\n", parametri.k);
   printf("nome file: %s\n", parametri.fileName);

   PilaPtr cimaPtr = NULL;
   buildStack(parametri.fileName, &cimaPtr);
   printStack(&cimaPtr, parametri.k);
 }
 
//$ ./prova input.txt 18.2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define MAX_LEN 31

typedef struct{
   char inputFile[LEN];
   double f;
}ParametriInput;

typedef struct{
   double numero;
   char parola[MAX_LEN];
}Record;

struct lista{
   struct lista *prevPtr;
   Record record;
   struct lista *nextPtr;
};

typedef struct lista Lista;
typedef Lista *ListaPtr;

ParametriInput readInput(int argc, char *argv[]);
ListaPtr buildList(const char *fileName);
void insertRecord(ListaPtr *sPtr, Record record);
void printList(ListaPtr sPtr);
void elab(ListaPtr sPtr, double f);
void freeList(ListaPtr sPtr);

int main(int argc, char *argv[]){
   ParametriInput parametri = readInput(argc, argv);
   printf("input: %s\nf: %.2f\n\n", parametri.inputFile, parametri.f);
   ListaPtr startPtr = buildList(parametri.inputFile);
   printList(startPtr);
   elab(startPtr, parametri.f);
   freeList(startPtr);
}

void elab(ListaPtr sPtr, double f){
   if(sPtr == NULL){
      printf("la lista e' vuota\n");
      exit(EXIT_FAILURE);
   }

   int count = 0;
   while(sPtr != NULL){
      if(sPtr->record.numero >= f){
         count++;
      }
       sPtr = sPtr->nextPtr;
   }
   printf("\nNumero di record aventi lunghezza pari o maggiore di %.2f: %d", f, count);
}

void printList(ListaPtr sPtr){
   if(sPtr == NULL){
      printf("la lista e' vuota\n");
      exit(EXIT_FAILURE);
   }
   printf("lista stampata:\n");
   while(sPtr->nextPtr != NULL){
      printf("%.2f %s\n", sPtr->record.numero, sPtr->record.parola);
      sPtr = sPtr->nextPtr;
   }
   printf("%.2f %s\n\n", sPtr->record.numero, sPtr->record.parola);


   printf("lista al contrario:\n");
   while(sPtr->prevPtr != NULL){
      printf("%.2f %s\n", sPtr->record.numero, sPtr->record.parola);
      sPtr = sPtr->prevPtr;
   }

}

void insertRecord(ListaPtr *sPtr, Record record){
   ListaPtr newPtr = malloc(sizeof(Lista));
   if(newPtr == NULL){
      fprintf(stderr, "impossibile allocare nuova memoria\n");
      exit(EXIT_FAILURE);
   }
   newPtr->record = record;
   newPtr->nextPtr = NULL;
   newPtr->prevPtr = NULL;

   ListaPtr previousPtr = NULL;
   ListaPtr currentPtr = *sPtr;

   while(currentPtr != NULL && strcmp(newPtr->record.parola, currentPtr->record.parola) > 0){
      previousPtr = currentPtr;
      currentPtr = currentPtr->nextPtr;
   }

   if(previousPtr == NULL){
      newPtr->nextPtr = *sPtr;
      newPtr->prevPtr = NULL;
      if(*sPtr != NULL){
          (*sPtr)->prevPtr = newPtr;
      }
      *sPtr = newPtr;
   }
   else{
      previousPtr->nextPtr = newPtr;
      newPtr->nextPtr = currentPtr;
      newPtr->prevPtr = previousPtr;
      if (currentPtr != NULL){
         currentPtr->prevPtr = newPtr;
      }
   }
}

ListaPtr buildList(const char *fileName){
   FILE *fPtr = fopen(fileName, "r");
   if(fPtr == NULL){
      fprintf(stderr, "impossibile aprire file o file inisistente\n");
      exit(EXIT_FAILURE);
   }
   Record record;
   ListaPtr startPtr = NULL;
   char numero[MAX_LEN];

   while(fscanf(fPtr, "%s %s", numero, record.parola) == 2){
      record.numero = strtod(numero, NULL);
      insertRecord(&startPtr, record);
   }
   fclose(fPtr);
   return startPtr;
}

ParametriInput readInput(int argc, char *argv[]){
   ParametriInput parametri;
   if(argc != 3){
      fprintf(stderr, "use: %s <inputFile> <f>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   strncpy(parametri.inputFile, argv[1], LEN - 1);
   parametri.inputFile[LEN - 1] = '\0';

   char *endPtr = NULL;
   parametri.f = strtod(argv[2], &endPtr);
   if(*endPtr != '\0'){
      fprintf(stderr, "il valore %s non e' un valore valido per <f>", argv[2]);
      exit(EXIT_FAILURE);
   }

   return parametri;
}
 
void freeList(ListaPtr sPtr){
    while(sPtr != NULL){
        ListaPtr temp = sPtr;
        sPtr = sPtr->nextPtr;
        free(temp);
    }
}
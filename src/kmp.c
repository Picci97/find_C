#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "kmp.h"

void search(char *cerca, int dimC, int *controllo){
//  cerca = head->wd;
//  char controllo = cerca; //controllo avrà la lunghezza adeguata
  controllo[0] = 0;
//  int M = strlen(cerca);
  int i = 1;
  int h = 0;

  while (i < dimC ){ // Finche cerca(word) e' minore di i
    if (cerca[i] == cerca[h]){ // se cerca i = h allora incrementa entrambi ed assegni controllo[i] = h 
      h++;
      controllo[i] = h;
      i++;
    } else {
      if(h != 0){ // se h diverso da 0 decrementi [h meno una posizione]
        h = controllo[h - 1];
      } else {
          controllo[i] = 0;
          i++;
      }
    }
  }
//  i++;
}
//  cerca = '\0'+cerca;

void kmp(char *cerca, char *frase){
  
//  int i = 0; //scorre tra le lettere di frase
  /*
  int* m = 0; //scorre tra le lettere di cerca
  int n = 0;
  int trova = 0; //salva quante parole sono state trovate
  */
  int dimF = strlen(frase);
  int dimC = strlen(cerca);

  int *controllo = (int*)malloc(dimF*sizeof(int));
  int j = 0;

//  char controllo;

  search(cerca, dimC, controllo);
  
  int i = 0;

  while (i < dimF){ //finchè la frase non finisce
    if(cerca[j] == frase[i]) { //se i caratteri confrontati tra le due frasi allora...
        j++;
        i++;
        }
      if (j == dimC) {
        printf("Trovato word nella posizione: %d\n",i - j);
        j = controllo[j - 1];
      }
      else if(cerca[j] != frase[i]){ // se la parola da cercare non è ancora finita...
        if (( j != 0)) {

        j = controllo[j - 1];

      } else { //
        i++;
        }      
      }
    free(controllo);
  }
}
/*
int main(int argc, char *argv[]){
  char inputs[200];
  char words[200];

  printf("Insert: ");
  scanf("%s",inputs);
  printf("Insert: ");
  scanf("%s",words);
  kmp(words,inputs);
}
*/
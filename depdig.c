#include<stdlib.h>
#include "io/text.h"
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "depdig.h"

static char  *nome[maxV], *comandos[maxV];

void depDigInit(){
  int i;

  for(i = 0; i < maxV; i++){
    nome[i] = comandos[i] = NULL;
  }
}

/*procura no vetor de nomes pelo indice do digrafo
  se ele existir, retorna seu indice
  caso contrario, retorna -1*/
int lookupNameNum(char *n){
  
}

void newVertex(Digraph G, char *n){
  nome[G->V] = n;

  G->V++;
}

Digraph genDepDig(text txt){
  text *aux;
  text_line line;
  char *nom;
  char *com;
  int target; /*flag que indica que um target já está sendo processado*/ 
  int pos, size_nom, size_com;

  nom = com = NULL;
  aux = &txt;
  target = -1;

  /*loop que percorre todas as linhas de um arquivo*/
  while(aux != NULL){
    line = aux->line;

    /*verifica linhas em branco*/
    if(line.size > 2){
      if(target < 0){
        size_nom = pos = 0;
        
        target = G->V;
        /*loop para capturar o nome de um target*/
        while(line.txt[pos] != ':'){
          nom = realloc(++size_nom*sizeof(char));
          if(nom == NULL){
            printf("\nCan't allocate memory for name");
            exit(-1);
          }

          nom[size_nom -1] = line.txt[pos];
          pos++;
        }

        newVertex(G, nom);
        nom = NULL;
      }
    }

    aux = aux->next_line;
  }
}

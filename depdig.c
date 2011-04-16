#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "io/text.h"
#include "io/input.h"
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
int lookupNameNum(char *n, int size){
  int i;

  for(i = 0; i < size - 1; i++){
    if(!strcmp(nome[i], n))
      return i;
  }

  return -1;
}

void newVert(Digraph G, char *n){
  nome[G->V] = n;

  G->V++;
}

Digraph depDigGen(text txt){
  text *aux;
  text_line line;
  char *nom;
  int pos, size_nom, size_com;
  Digraph G;
  Vertex target, dep;

  G = DIGRAPHinit();
  nom = NULL;
  aux = &txt;
  target = -1;

  /*loop que percorre todas as linhas de um arquivo*/
  while(aux != NULL){
    line = aux->line;

    /*verifica linhas em branco*/
    if(line.size > 2){
      if(target < 0){/*ainda não leu um target*/
        size_com = size_nom = pos = 0;

        /*loop para capturar o nome de um target*/
        while(pos < line.size && line.txt[pos] != ':'){
          nom = writeChar(line.txt[pos++], nom, &size_nom);
        }

        nom = writeChar('\0', nom, &size_nom); /*para o strcmp é importante que as strings terminem com o caracter nulo \0*/
        
        target = lookupNameNum(nom, G->V);
        if(target < 0){
          newVert(G, nom);
          target = G->V - 1;
        }
        printf("\ntarget[%d]:*%s*", target, nom); 
        nom = NULL;
        size_nom = 0;

        pos++;

        /*loop que captura nomes de dependencias*/
        while(pos < line.size){
          while(line.txt[pos] != ' '){ 
            nom = writeChar(line.txt[pos++], nom, &size_nom);
          }

          /*evita que espaços em branco e quebras de linha sejam entendidos como dependencias*/
          if(size_nom > 0){
            nom = writeChar('\0', nom, &size_nom);

            dep = lookupNameNum(nom, G->V);
            if(dep < 0){
              newVert(G, nom);
              dep = G->V - 1;
            }
            printf("\ndependency[%d]:*%s*", dep, nom); 
            nom = NULL;
            size_nom = 0;

            DIGRAPHinsertA(G, target, dep);
          }
          
          pos++;       
        }  
      }else{/*trata os comandos*/
        while(pos < line.size){
          comandos[target] = writeChar(line.txt[pos++], comandos[target], &size_com);
        }

        comandos[target] = writeChar(';', comandos[target], &size_com);
      }
    }else{
      target = -1;
    }

    aux = aux->next_line;

  }

  return G;
}

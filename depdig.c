#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "io/text.h"
#include "io/input.h"
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "depdig.h"
#include "syscalls.h"

typedef enum {FALSE,TRUE} Boolean;
static char  *nome[maxV], *comandos[maxV];
static int com_size[maxV], nam_size[maxV], targets[maxV];
long mod_time[maxV];
Boolean up_to_date[maxV];

void depDigInit(){
  int i;

  for(i = 0; i < maxV; i++){
    nome[i] = comandos[i] = NULL;
    mod_time[i] = com_size[i] = nam_size[i] = targets[i] = 0;
    up_to_date[i] = FALSE;
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
  mod_time[G->V] = mtime(n);
  if(mod_time[G->V] == -1){
    up_to_date[G->V] = FALSE;
  }else{
    up_to_date[G->V] = TRUE;
  }
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
        while(pos < line.size && line.txt[pos] != ':' && line.txt[pos] != '#'){
          nom = writeChar(line.txt[pos++], nom, &size_nom);
        }

        if(size_nom > 0){

          nom = writeChar('\0', nom, &size_nom); /*para o strcmp é importante que as strings terminem com o caracter nulo \0*/
          
          target = lookupNameNum(nom, G->V);
          if(target < 0){
            newVert(G, nom);
            target = G->V - 1;
            nam_size[target] = size_nom;
          }
          targets[target] = 1;

          nom = NULL;
          size_nom = 0;

          pos++;
          /*loop que captura nomes de dependencias*/
          while(pos < line.size){
            while(pos < line.size && line.txt[pos] != ' ' && line.txt[pos] != '#'){
              nom = writeChar(line.txt[pos++], nom, &size_nom);
            }

            /*evita que espaços em branco e quebras de linha sejam entendidos como dependencias*/
            if(size_nom > 0){
              nom = writeChar('\0', nom, &size_nom);

              dep = lookupNameNum(nom, G->V);
              if(dep < 0){
                newVert(G, nom);
                dep = G->V - 1;
                nam_size[dep] = size_nom;
              }
              if(mod_time[dep] == -1 || mod_time[dep] > mod_time[target])
                up_to_date[dep] = up_to_date[target] = FALSE;
              
              nom = NULL;
              size_nom = 0;

              DIGRAPHinsertA(G, target, dep);
            }
            
            pos++;       
          }
        }  
      }else{/*trata os comandos*/
        pos = 1;
        size_com = 0;

        while(pos < (line.size) && line.txt[0] != '#' && line.txt[pos] != EOF && line.txt[pos] != '\0'){
          comandos[target] = writeChar(line.txt[pos++], comandos[target], &size_com);
        }

        if(size_com > 0){
          comandos[target] = writeChar(';', comandos[target], &size_com);
          comandos[target] = writeChar('\0', comandos[target], &size_com);
          com_size[target] = size_com;
        }

      }
    }else{
      target = -1;
    }

    aux = aux->next_line;

  }

  return G;
}

text makefileGen(Digraph G){
  text *aux, *ret;
  Vertex v;
  link p;

  aux = malloc(sizeof(text));
  if(aux == NULL){
    printf("\nCan't allocate memory to line");
    exit(-1);
  }
  aux->line.txt = NULL;
  aux->line.size = 0;

  ret = aux;

  for(v = 0; v < G->V; v++){
    if(targets[v]){
      aux->line.txt = append(aux->line.txt, &aux->line.size,  nome[v], nam_size[v]);
      aux->line.txt = writeChar(':', aux->line.txt, &aux->line.size);
      for(p = G->adj[v]; p != NULL; p = p->next){/*escreve as dependencias*/
        aux->line.txt = writeChar(' ', aux->line.txt, &aux->line.size);
        aux->line.txt = append(aux->line.txt, &aux->line.size,  nome[p->w], nam_size[p->w]);
      }

      aux->next_line = malloc(sizeof(text));
      if(aux == NULL){
        printf("\nCan't allocate memory to line");
        exit(-1);
      }
      aux = aux->next_line;
      aux->line.txt = NULL;
      aux->line.size = 0;

      aux->line.txt = append(aux->line.txt, &aux->line.size,  comandos[v], com_size[v]);/*comandos numa nova linha*/

      /*linha em branco após os comandos*/
      aux->next_line = malloc(sizeof(text));
      if(aux == NULL){
        printf("\nCan't allocate memory to line");
        exit(-1);
      }
      aux = aux->next_line;
      aux->line.txt = NULL;
      aux->line.size = 0;

      aux->next_line = malloc(sizeof(text));
      if(aux == NULL){
        printf("\nCan't allocate memory to line");
        exit(-1);
      }
      aux = aux->next_line;
      aux->line.txt = NULL;
      aux->line.size = 0;
    }
  } 

  return *ret;
}

int make(Digraph G, char *c){
  Vertex target, dep;
  link p;
  int i;

  if(c != NULL){
    target = lookupNameNum(c, G->V);
    if(target < 0){
      printf("\nCouldn't find target: %s", c);
      return 0;
    }
  }else{
    target = -1;
    for(i = 0; i < G->V; i++)
      if(targets[i] && target < 0)
        target = i;

    if(target < 0){
      printf("\nCouldn't find any target");
      return 0;
    }
  }

  if(DIGRAPHcycle(G, target)){
    printf("\nCyclical dependencies for target: %s", nome[target]);
    return 0;
  }

  printf("alvo %s\n", nome[target]);

  for(p = G->adj[target]; p != NULL; p = p->next){
    dep = p->w;

    printf("dependencia: %s\n", nome[dep]);

    if(!up_to_date[dep]){
      if(targets[dep] == 1){
        if(!make(G, nome[dep]))
          return 0;
      }else{
        if(mod_time[dep] == -1){
          printf("\nMissing dependecy file: %s",nome[dep]);
          return 0;
        }
      } 
    }
  }

  up_to_date[target] = TRUE;

  return execute(comandos[target]);
  
}

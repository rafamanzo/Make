#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include "input.h"
#include "output.h"

#define fileClose fclose

FILE * fileOpenI(char *file){
  FILE *fp;

  fp = fopen(file, "r");
  if(fp == NULL){
    printf("\nCould not open file: %s", file);
    exit(-1);    
  }

  return fp;
  
}

FILE * fileOpenO(char *file){
  FILE *fp;

  fp = fopen(file, "w");
  if(fp == NULL){
    printf("\nCould not open file: %s", file);
    exit(-1);    
  }

  return fp;
  
}


text getText(char *file){
  FILE *fp;
  text head;
  text *before, *actual;
  text_line aux;
  
  fp = fileOpenI(file);  
  actual = malloc(sizeof(text));
  if(actual == NULL){
    printf("\nCan't allocate memory to line");
    exit(-1);
  }

  head.line = getLine(fp);
  head.next_line = actual;

  if(!head.line.final){
    aux = getLine(fp);

    do{
      actual->line = aux;
      actual->next_line = malloc(sizeof(text));
      if(actual->next_line == NULL){
        printf("\nCan't allocate memory to line");
        exit(-1);
      }
      
      before = actual;
      actual = actual->next_line;
      aux = getLine(fp);
    }while(!aux.final);
      
    before->next_line = NULL;
    free(actual);
  }else{
    free(head.next_line);
    head.next_line = NULL;
  }

  fileClose(fp);  

  return head;
}

void printText(text txt){
  text *aux;

  aux = &txt;

  do{
    printTextLine(aux->line);
    aux = aux->next_line;
  }while(aux != NULL);

}

void writeText(char *file, text txt){
  text *aux;
  FILE *fp;

  aux = &txt;
  fp = fileOpenO(file);  

  do{
    writeTextLine(fp, aux->line);
    aux = aux->next_line;
  }while(aux != NULL);

  fileClose(fp);
}

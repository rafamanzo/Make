#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include "input.h"

#define fileClose fclose

FILE fileOpen(char *file){
  text t;

  t->file = fopen(file, "r");
  if(t->file == NULL){
    printf("\nCould not open file: %s", file);
    exit(-1);    
  }
  
}

text getText(char *file){
  FILE *file;
  text head, *before, *actual;
  text_line aux;
  
  file = fileOpen(file);  
  actual = malloc(sizeof(text));
  if(actual == NULL){
    printf("\nCan't allocate memory to line");
    exit(-1);
  }

  head->line = getLine(file);
  head->next_line = actual;

  if(!head->line->final){
    aux = getLine(file);

    do{
      *actual->line = aux;
      *actual->next_line = malloc(sizeof(text));
      if(*actual->next_line == NULL){
        printf("\nCan't allocate memory to line");
        exit(-1);
      }
      
      before = actual;
      actual = *actual->next_line;
      aux = getLine(file)
    }while(!aux->final)
      
    before->next_line = NULL;
    free(actual);
  }else{
    free(head->next_line);
    head->next_line = NULL;
  }

  fileClose(file);  

  return head;
}

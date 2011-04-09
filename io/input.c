#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include "input.h"

text_line getLine(FILE *fp){
  text_line l;
  char c;

  l->size = 0;
  l->txt = NULL;
  c = getc(fp);

  while(c != EOF && c != '\n'){
    l->size++;
    l->txt = realloc(l->txt, l->size*sizeof(char));
    if(l->txt == NULL){
      printf("\nCan't allocate memory to buffer");
      exit(-1);
    }

    l->txt[l->size - 1] = c;

    c = getc(fp);
  }

  if(c == EOF){
    l->final = 1;
  }else{
    l->final = 0;
  }

  return l;
}


#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include "input.h"

char * writeChar(char c, char *str, int *size){
  str = realloc(str, ++*size*sizeof(char));
  if(str == NULL){
    printf("\nCan't allocate memory for string");
    exit(-1);
  }

  str[*size - 1] = c;

  return str;
}

text_line getLine(FILE *fp){
  text_line l;
  char c;

  l.size = 0;
  l.txt = NULL;
  c = getc(fp);

  while(c != EOF && c != '\n'){
    l.txt = writeChar(c, l.txt, &l.size);
    c = getc(fp);
  }

  if(c == EOF){
    l.final = 1;
  }else{
    l.final = 0;
  }

  return l;
}

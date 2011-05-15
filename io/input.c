#include<stdio.h>
#include<stdlib.h>
#include "text.h"
#include "input.h"

char * writeChar(char c, char *str, int *size){
  str = realloc(str, (++*size)*sizeof(char));
  if(str == NULL){
    printf("\nCan't allocate memory for string");
    exit(-1);
  }

  str[*size - 1] = c;

  return str;
}

/*concatenates str2 on the end of str1, adjusting size1 for size1 = size1 + size2*/
char * append(char *str1, int *size1, char *str2, int size2){
  int i;

  str1 = realloc(str1, (*size1 + size2)*sizeof(char));
  if(str1 == NULL){
    printf("\nCan't allocate memory for string");
    exit(-1);
  }

  for(i = *size1; i < (*size1 + size2); i++){
    str1[i] = str2[i - *size1];
  }

  *size1 = *size1 + size2;

  return str1;
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

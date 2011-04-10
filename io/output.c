#include<stdlib.h>
#include<stdio.h>
#include "text.h"
#include "output.h"

void printTextLine(text_line line){
  int i;

  printf("\n");

  for(i = 0;i < line.size; i++){
    printf("%c", line.txt[i]);
  }
}

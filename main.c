#include<stdio.h>
#include<stdlib.h>
#include "io/text.h"

#define MAKEFILE "MakeFile"
#define MAKEFILED "MakeFile.dg"

int main( int argc, const char* argv[]){
  text txt;

  txt = getText(MAKEFILE);
  printText(txt);
  writeText(MAKEFILED, txt);  

  return 0;
}

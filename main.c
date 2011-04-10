#include<stdio.h>
#include<stdlib.h>
#include "io/text.h"

#define MAKEFILE "MakeFile"

int main( int argc, const char* argv[]){
  text txt;

  txt = getText(MAKEFILE);
  printText(txt);

  return 0;
}

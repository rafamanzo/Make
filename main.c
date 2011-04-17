#include<stdio.h>
#include<stdlib.h>
#include "io/text.h"
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "depdig.h"

#define MAKEFILE "MakeFile"
#define MAKEFILED "MakeFile.dg"

int main( int argc, const char* argv[]){
  text txt;
  Digraph G;

  txt = getText(MAKEFILE);
  depDigInit();
  G = depDigGen(txt);
  txt = makefileGen(G);
  writeText(MAKEFILED, txt);

  return 0;
}

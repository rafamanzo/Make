#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "io/text.h"
#include "ed/vertex.h"
#include "ed/digraph.h"
#include "depdig.h"

#define MAKEFILE "MakeFile"
#define MAKEFILED "MakeFile.dg"

int main( int argc, const char* argv[]){
  text txt;
  Digraph G;
  int i;

  txt = getText(MAKEFILE);
  depDigInit();
  G = depDigGen(txt);

  
  if(argc == 2 && strcmp(argv[1], "-s") == 0){
    make(G, NULL);
    txt = makefileGen(G);
    writeText(MAKEFILED, txt);
  }else if(argc > 1){
    for(i = 1; i < argc; i++){
      if(strcmp(argv[i], "-s") == 0){
        txt = makefileGen(G);
        writeText(MAKEFILED, txt);
      }else{
        make(G, (char *) argv[i]);
      }
    }
  }else{
    make(G, NULL);
  }

  return 0;
}

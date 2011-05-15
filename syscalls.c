#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>

int execute(char *cmd){
  if(system(cmd) != 0){
    fprintf(stderr,"Erro na execução do comando: %s\n", cmd); 
    return 0;
  }

  return 1;
}

long mtime(char *f){
  struct stat bufst;

  if (stat(f, &bufst) == -1) return -1;
  return bufst.st_mtime;
}

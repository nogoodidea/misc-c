#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void onFork(char *programPath,char *programArgs) {
 execl(programPath,programArgs,NULL);
}

int main(int argc,char *argv[]) {
 if(argc <= 2){printf("needs 2 args");exit(1);}
 int programAmount = atoi(argv[1]);
 int programArgsLen = 10;
 char *programPath = argv[2];
 int i=3;
 char *programArgs = (char*) malloc(programArgsLen*sizeof(char**));
 int pid[programAmount];
 //arg handling
 for(;i!=argc;i+=1){
  if (i+1 >= programArgsLen){
   programArgsLen = programArgsLen*2;
   programArgs = (char*) realloc(programArgs,programArgsLen*sizeof(char**));
   if(programArgs == NULL){fprintf(stderr,"OUT OF RAM");exit(1);}
  }
  strcat(programArgs," ");
  strcat(programArgs,argv[i]);
 }
 printf("%s",programArgs);
 for(i=0;i!=programAmount;i+=1){ 
  if ((pid[i] = fork())==0){onFork(programPath,programArgs);}
 } 
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void onFork(char *programPath,char **programArgs) {
 fprintf(stderr,"%s\n",programPath);
 execve(programPath,programArgs,NULL);
}

int main(int argc,char *argv[]) {
 int i=2;
 int programAmount = 5;
 int programArgsLen = 10;
 char *programPath = argv[2];
 char **programArgs = (char**) malloc(programArgsLen*sizeof(char**));
 int pid[programAmount];
 //arg handling
 for(;i!=argc;i+=1){
  if(i==argc){break;}
  if (i+1 >= programArgsLen){
   programArgsLen = programArgsLen*2;
   programArgs = (char**) realloc(programArgs,programArgsLen*sizeof(char**));
   if(programArgs == NULL){fprintf(stderr,"OUT OF RAM");exit(1);}
  }
  strcpy(programArgs[i],argv[i]);
 }
 for(i=0;i!=programAmount;i+=1){ 
  if ((pid[i] = fork())==0){onFork(programPath,programArgs);}
 } 
}

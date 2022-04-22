#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void onFork(char *programPath,char *programArgs) {
 
 execlp(programPath,programArgs);
}

int main(int argc,char *argv[]) {
 int pid[5];
 int i=3;
 int programAmount = 5;
 int programArgsLen = 10;
 char *programArgs = (char*) malloc(programArgsLen*sizeof(char*));
 for(;i!=argc;i+=1){
  if (strlen(argv[i])+1 >= programArgsLen){
   programArgsLen = programArgsLen*2;
   programArgs = (char*) realloc(programArgs,programArgsLen*sizeof(char*));
   if(programArgs == NULL){fprintf(stderr,"OUT OF RAM");exit(1);}
  }
  strcat(programArgs," ");
  strcat(programArgs,argv[i]);
 }
 fprintf(stderr,"%s\n",programArgs);
 fprintf(stderr,"%i\n",programAmount);
 for(i=0;i!=programAmount;i+=1){ 
  pid[i] = fork();
  if (pid[i] == 0){onFork(argv[2],programArgs);}
  else {printf("%i\n",pid[i]);}
 } 
}

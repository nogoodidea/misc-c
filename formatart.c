#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

//needed for me to understand my own code
#define TRUE 1
#define FALSE 0

//checks if a file is part of the blacklist
int checkBlacklist(char *inputStr){
 char *blacklist[] = {".",".."};
 int blacklistLen = 2;
 int i=0;
 while (blacklistLen != i){
 //check if the string is = than the blacklist string
  if (strcmp(inputStr,blacklist[i])==0){return FALSE;}
  i++;}
 return TRUE;
}

/*check if the file extenction is a image
 * fix later use the blacklist function for now */
int checkValidImage(char *inputStr){
 int inputLen = strlen(inputStr);
 char *suffex = "png";
 int suffexLen = strlen(suffex);
 int i = 0;
 int i2 = 0;
 i = inputLen-suffexLen;
 if (inputLen == suffexLen) {return FALSE;}
  while (i != inputLen){
  if (inputStr[i]=!suffex[i2]) {return FALSE;}
  i2++;
  i++;
 }
 return TRUE;
}

void checkNull(char* pointer){if(pointer==NULL){fprintf(stderr,"out of mem");exit(1);}}

//malloc, how hard can it be, VERY
char** readFile(char *fileStr){
 FILE *confFile; 
 if ((confFile = fopen(fileStr,"r")) == NULL){fprintf(stderr,"file \"%s\" not found",fileStr);exit(1);}
 int i = 0;
 int arrayLen = 10;
 char *array = (char*) malloc(arrayLen*sizeof(char));
 checkNull(array);
 int c;
 while ((c = fgetc(confFile)) != EOF){
  if (i == arrayLen -2){
    arrayLen = arrayLen*2;
    array = realloc(array,arrayLen*sizeof(char));
    checkNull(array);
    }
    array[i] = (char) c;
   i++;
  }
  array[i]='\0'; //end str
  fclose(confFile);
  arrayLen = 2;
  i=0;
  char **arrayOut = (char**) malloc(arrayLen*sizeof(char*));
  char *temp;
  while(temp = strtok(array,"\n")!= NULL){
   fprintf(stderr,"GOT HERE %c",temp[0]); 
   if(i==arrayLen){
    arrayLen = arrayLen*2;
    arrayOut = realloc(arrayOut,arrayLen*sizeof(char*));
    checkNull(arrayOut);
    fprintf(stderr,"PAIN");
   }
   fprintf(stderr,"got here %s \n",temp);
   arrayOut[i] = (char*) malloc(strlen(temp)*sizeof(char*));
   checkNull(arrayOut);
   arrayOut[i] = temp;
   i++;
  }
  free(array);
  return arrayOut;
}

int main(int argc, char *argv[]) {
  //errors out if the user does not input a file, uses relative path
  if (argc == 2) { fprintf(stderr,"needs <CONFIG FILE> <DIR>");return 1;}
  char **format = readFile(argv[1]);
  DIR *targetDir;
  struct dirent *dir;
  targetDir = opendir(argv[1]);
  printf("%s",format[0]);
  if (targetDir) {
    while ((dir = readdir(targetDir)) != NULL) {
      if (checkBlacklist(dir->d_name) == TRUE){
         printf(format[1],dir->d_name);
        }
    }    closedir(targetDir);
  }else{fprintf(stderr,"dir \"%s\" not found",argv[1]);}
  printf("%s",format[2]);
  free(format);
  return(0);
}

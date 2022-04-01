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
 if (inputLen <= suffexLen) {return FALSE;}
  while (i != inputLen){
  if (inputStr[i]=!suffex[i2]) {return FALSE;}
  i2++;
  i++;
 }
 return TRUE;
}

//malloc, how hard can it be, VERY
char** readFile(char *fileStr){
 FILE *confFile; 
 if ((confFile = fopen(fileStr,"r")) == NULL){fprintf(stderr,"file \"%s\" not found",fileStr);exit(1);}
 int i = 0;
 int arrayLen = 10;
 char *array = malloc(arrayLen*sizeof(char));
 if(array==NULL){fprintf(stderr,"out of mem");exit(1);}
 int c;
 while ((c = fgetc(confFile)) != EOF){
  if (i == arrayLen){
    arrayLen = arrayLen*2;
    array = realloc(array,arrayLen);
    if(array==NULL){fprintf(stderr,"out of mem");exit(1);}
    }
   array[i] = c;
   i++;
  }
  fclose(confFile);
  array = realloc(array,i);
  arrayLen = i;
  char **arrayOut;
  char *temp;
  temp = strtok(array,"\n");
//segfalts here
  arrayOut[0] = malloc(strlen(temp)*sizeof(char));
  if(arrayOut==NULL){fprintf(stderr,"out of mem");exit(1);}
  arrayOut[i] = temp;
  for (i=1;3==i;i++){
   temp = strtok(temp,"\n");
   arrayOut[i] = malloc(strlen(temp)*sizeof(char));
   if(arrayOut==NULL){fprintf(stderr,"out of mem");exit(1);}
   arrayOut[i] = temp;
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

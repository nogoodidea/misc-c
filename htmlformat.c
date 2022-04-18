#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

//needed for me to understand my own code
#define TRUE 1
#define FALSE 0

//checks if a file is part of the blacklist
int checkBlackList(char *inputStr){
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
  if ((inputStr[i])=!suffex[i2]) {return FALSE;}
  i2++;
  i++;
 }
 return TRUE;
}

void checkNull(void* pointer){if(pointer==NULL){fprintf(stderr,"out of mem");exit(1);}}

void init(void* arr, int len) {
  for (int i = 0; i < len; i++) {
    arr= 0;
  }
}

char** readFile(char *fileStr){
 FILE *confFile; 
 if ((confFile = fopen(fileStr,"r")) == NULL){fprintf(stderr,"file \"%s\" not found",fileStr);exit(1);}
 int i = 0;
 int arrayLen = 10;
 char *array = (char) malloc(arrayLen*sizeof(char));
 checkNull(array);
 int c;
 while ((c = fgetc(confFile)) != EOF){
  if (i == arrayLen -2){
    arrayLen = arrayLen*2;
    array = (char) realloc(array,arrayLen*sizeof(char));
    checkNull(array);
    }
    array[i] = c;
   i++;
  }
fprintf(stderr,"got here");
  array[i]='\0'; //end str
  fclose(confFile);
  arrayLen = 2;
  i=0;//1
  char **arrayOut = (char**) malloc(arrayLen*sizeof(char**));
  init(arrayOut, arrayLen);
  char *temp;
  temp = strtok(array,"\n");
  while(temp) { // fails if temp == '\0' so if we run out 
   strcpy(arrayOut[i],strcat(temp, "\0"));
   fprintf(stderr,"%s\n",arrayOut[i]);
   i += 1;
   temp = strtok(NULL,"\n");
   if(i==arrayLen){//fails here
    arrayLen = arrayLen*2;
    arrayOut = (char**) realloc(arrayOut,arrayLen*sizeof(char**));
    checkNull(arrayOut);
   }
  } 
  free(array);
  return arrayOut;
}

int main(int argc, char *argv[]) {
 //errors out if the user does not input a file, uses relative path
 if (argc == 2) { fprintf(stderr,"needs <CONFIG FILE> <DIR>");return 1;}
 char **format = (char**) readFile(argv[1]);
 fprintf(stderr,"got here");
 DIR *targetDir;
 char *targetDirName;
 struct dirent *dir;
 fprintf(stderr,"got here too");
 targetDir = opendir(argv[2]);
 printf("%s\n",format[0]);
 if (targetDir) {
  while ((dir = readdir(targetDir)) != NULL) {
   if (checkBlackList(dir->d_name) == TRUE){
    targetDirName = strcat(dir->d_name,format[2]);
    targetDirName = strcat(format[1],targetDirName);
    printf("%s\n",targetDirName);
    targetDirName = '\0';
   }
  }
 closedir(targetDir);
 }else{fprintf(stderr,"dir %s not found",argv[2]);exit(1);}
 printf("%s\n",format[3]);
 free(format);
 return(0);
}

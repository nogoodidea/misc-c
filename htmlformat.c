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

char** readFile(char *fileStr){
 FILE *confFile; 
 if ((confFile = fopen(fileStr,"r")) == NULL){fprintf(stderr,"file \"%s\" not found",fileStr);exit(1);}
 int i = 0;
 int arrayLen = 10;
 char *array = (char *) malloc(arrayLen*sizeof(char *));
 checkNull(array);
 int c;
 while ((c = fgetc(confFile)) != EOF){
  if (i == arrayLen -2){
    arrayLen = arrayLen*2;
    array = (char *) realloc(array,arrayLen*sizeof(char *));
    checkNull(array);
    }
    array[i] = c;
   i++;
  }
  array[i]='\0'; //end str
  fclose(confFile);
  arrayLen = 5;
  i=0;//1
  char **arrayOut = (char **) malloc(arrayLen*sizeof(char **));
  char *temp;
  temp = strtok(array,"\n");
  while(temp) { // breaks if temp == '\0' so if we exit the loop
   arrayOut[i] = strcat(temp, "\0");
   i += 1;
   temp = strtok(NULL,"\n");
   if(i==arrayLen){
    arrayLen = arrayLen*2;
    arrayOut = (char **) realloc(arrayOut,arrayLen*sizeof(char **));
    checkNull(arrayOut);
    checkNull(arrayOut[i]);
   }
  } 
  free(array);
  return arrayOut;
}

int main(int argc, char *argv[]) {
 //errors out if the user does not input a file, uses relative path
 if (argc == 2) { fprintf(stderr,"needs <CONFIG FILE> <DIR>");return 1;}
 char **format;
 format = (char**) readFile(argv[1]);
 DIR *targetDir;
 int fileNameHtmlLen = 30;
 int line = 0;
 int loopStartLine = 0;
 char *fileNameHtml = (char *) malloc(fileNameHtmlLen*sizeof(char *));
 char *temp = (char *) malloc(fileNameHtmlLen*sizeof(char *));
 struct dirent *dir;
 targetDir = opendir(argv[2]);
 for(;strstr(format[line],"<FILE>") == NULL;line += 1){
  printf("%s\n",format[line]);
 }
 line += 1;
 loopStartLine = line;
 if (targetDir) {
  while ((dir = readdir(targetDir)) != NULL) {
    line=loopStartLine;
    if (checkBlackList(dir->d_name) == TRUE){
     for(loopStartLine = line;strstr(format[line],"</FILE>")==NULL;line+=1){
     if (strlen(format[line]) + strlen(dir->d_name)-5 == fileNameHtmlLen) {
      fileNameHtmlLen = strlen(format[line]) + strlen(dir->d_name)-1;
      fileNameHtml = (char *) realloc(fileNameHtml,fileNameHtmlLen);
      temp = (char *) realloc(fileNameHtml,fileNameHtmlLen);
      }
     checkNull(fileNameHtml);
     checkNull(temp);
     strcpy(temp,format[line]);
     strcpy(fileNameHtml,strtok(temp,"FILE"));
     strcat(fileNameHtml,dir->d_name);
     strcat(fileNameHtml,strtok(NULL,"FILE"));
     printf("%s\n",fileNameHtml);
    }
   }
  }
 closedir(targetDir);
 line +=1;
 }else{fprintf(stderr,"dir %s not found",argv[2]);exit(1);}
 for(;strstr(format[line],"END")== NULL;line+=1){
  printf("%s\n",format[line]);
 }
 free(format);
 return(0);
}
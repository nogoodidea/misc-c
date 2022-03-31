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
 * fix later useing the blacklist function now */
int checkValidImage(char *inputStr){
 int inputLen = strlen(inputStr);
 char *suffex = "png";
 int suffexLen = strlen(suffex);
 int i;
 int i2 = 0;
 int returnInt = TRUE;
 i = inputLen-suffexLen;
 if (inputLen <= suffexLen) {returnInt = FALSE;return returnInt;}
  while (i != inputLen){
  if (inputStr[i] =! suffex[i2]) { returnInt = FALSE;break;}
  i2++;
  i++;
 }
 return returnInt;
}
//malloc, how hard can it be
char readFile(char *fileStr){
 FILE = *confFile;
 confFile = fopen(fileStr,'r');
 int i = 0;
 int arrayLen = 10;
 char *array = (char*) (malloc (arrayLen) * sizeof(char));
 char arrayOld;
 int c;
 while ((c = fgetc(confFile)) != EOF){
  if (i == arrayLen){
    arrayLen = arrayLen*2;
    arrayOld = @array;
    array = realloc(array,arrayLen);
    free(arrayOld);
    }
   array[i] = c;
   i++;
  }
  realloc(array,i);
}

int main(int argc, char *argv[]) {
  //errors out if the user does not input a file, uses relative path
  if (argc == 2) { fprintf(stderr,"NEEDS <CONFIG FILE> <DIR>");return 1;}
  char *format[] = readFile(argv[1]);
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
  }else{printf("ERROR %s NOT FOUND",argv[1]);}
  printf("%s",format[2]);
  return(0);
}

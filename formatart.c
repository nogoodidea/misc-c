#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
//needed for me to understand my own code
#define TRUE 1
#define FALSE 0

//checks if a file is part of the blacklist
int checkBlacklist(char *inputStr){
 char *blacklist[] = {".",".."};
 int blacklistLen = 2;
 int i;
 int returnInt = FALSE;
fprintf(stderr,"%s",blacklist[1]);
 for (i=0;i==blacklistLen;i++){
fprintf(stderr,"%s ",blacklist[i]);
fprintf(stderr,"%s\n",inputStr);
 if (strcmp(blacklist[i],inputStr)==0){returnInt = TRUE;break;}
  }
 return returnInt;
}

/*check if the file extenction is a image
 * fix later useing the blacklist function now 
int checkValidImage(char *inputStr){
 int inputLen = strlen(inputStr);
 char *suffex = "png";
 int suffexLen = strlen(suffex);
 int i;
 int i2 = 0;
fprintf(stderr,"%s\n",inputStr);
 int returnInt = TRUE;
 i = inputLen-suffexLen;
fprintf(stderr,"%i\n",inputLen);
 if (inputLen <= suffexLen) {returnInt = FALSE;return returnInt;}
  while (i != inputLen){
  if (inputStr[i] =! suffex[i2]) { returnInt = FALSE;break;}
  i2++;
  i++;
 }
 return returnInt;
}*/

int main(int argc, char *argv[]) {
  //errors out if the user does not input a file, uses relative path
  if (argc == 1) { fprintf(stderr,"NEEDS <DIR>");return 1;}
  //FILE *fopen(argv[1],'r');
  DIR *targetDir;
  struct dirent *dir;
  targetDir = opendir(argv[1]);
  //headers
  const char *formatHeader = "<!DOCTYPE HTML>\n<HTML>\n<HEAD>\n<TITLE>Art</TITLE>\n<BODY>\n";
  const char *formatData = "<img src=\"art/%s\" style=\"width:70%;height:50%;\">\n";
  const char *formatFooter = "</BODY>\n</HTML>";
  printf("%s",formatHeader);
  if (targetDir) {
    while ((dir = readdir(targetDir)) != NULL) {
      if (checkBlacklist(dir->d_name) != TRUE){
         printf(formatData,dir->d_name);
        }
    }    closedir(targetDir);
  }else{printf("ERROR %s NOT FOUND",argv[1]);}
  printf("%s",formatFooter);
  return(0);
}

#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
//needed for me to understand my own code
#define TRUE 1
#define FALSE 0

//checks if a file is part of the blacklist ie
int checkBlacklist(char *inputStr){
 char *blacklist[] = {".",".."};
 int blacklistLen = 2;
 int i;
 int returnInt = FALSE;
 for (i=0;i==blacklistLen-1;i++){
	if (strcmp(blacklist[i],inputStr)==0){returnInt = TRUE;break;}
  }
 return returnInt;
}

//check if the file extenction is a image 
int checkValidImage(char *inputStr){
 int inputLen = strlen(inputStr);
 char *suffex = ".png";
 int suffexLen = strlen(suffex);
 int i;
 int i2 = 0;
 int returnInt = TRUE;
 if (inputLen <= suffexLen) {returnInt = FALSE;}
 for (i=inputLen-suffexLen;i==inputLen;i++){
  if (inputStr[i] =! suffex[i2]) { returnInt = FALSE;break;}
fprintf(stderr,"GOT HERE");
fprintf(stderr,"%s",inputStr[i]);
fprintf(stderr,"%s\n",suffex[i2]);
  i2++;
 }
 return returnInt;
}

int main(int argc, char *argv[]) {
  //errors out if the user does not input a file, uses relative path
  if (argc == 2) { fprintf(stderr,"NEEDS <CONFIG> <DIR>");return 1;}
  //FILE *fopen(argv[1],'r');
  DIR *targetDir;
  struct dirent *dir;
  targetDir = opendir(argv[2]);
  //headers
  const char *formatHeader = "<!DOCTYPE HTML>\n<HTML>\n<HEAD>\n<TITLE>Art</TITLE>\n<BODY>";
  const char *formatData = "<img src=\"art/%s\" style=\"width:70%;height:50%;\">\n";
  const char *formatFooter = "</BODY>\n</HTML>";
  printf("%s",formatHeader);
  if (targetDir) {
    while ((dir = readdir(targetDir)) != NULL) {
      if (checkValidImage(dir->d_name) != FALSE){
         printf(formatData,dir->d_name);
        }
    }    closedir(targetDir);
  }else{printf("ERROR %s NOT FOUND",argv[2]);}
  printf("%s",formatFooter);
  return(0);
}

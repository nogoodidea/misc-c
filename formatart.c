#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
//needed for me to understand my own code
#define TRUE 1
#define FALSE 0

int main(int argc, char argv[]) {
  //if (argc == 1) { fprintf(stderr,"NEEDS INPUT");return 0;}
  DIR *targetDir;
  struct dirent *dir;
  char targetConst = argv[1];
  //targetDir = opendir(targetConst);
  targetDir = opendir("../http/art/");
  printf("<!DOCTYPE HTML>\n<HTML>\n<HEAD>\n<TITLE>Art</TITLE>\n<BODY>");
  if (targetDir) {
    while ((dir = readdir(targetDir)) != NULL) {
      if (checkBlacklist(dir->d_name) == TRUE){
         printf("<img src=\"art/%s\" style=\"width:70%;height:50%;\">\n", dir->d_name);
        }
    }    closedir(targetDir);
  }else{printf("ERROR %s NOT FOUND",targetConst);}
  printf("</BODY>\n</HTML>");
  return(0);
}
int checkBlacklist(char *inputStr){
 char *blacklist = {"..","."};
 int blacklistLen = 2;
 int i;
 int returnInt = TRUE;
 for (i=0;i==blacklistLen;i++){
   if (strcmp(blacklist,inputStr)==0){returnInt = FALSE;break;}
  }
 return returnInt;
}

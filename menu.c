#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[]){
	int i;
	if (argc < 2) {printf("NEEDS INPUT");return 0;}
	for (i=1;i<argc;i++) {
		printf("%i-",i);
		printf("%s\n",argv[i]);
		}
	while(1){
		scanf("%i",&i);
		if ( i <= argc){
			fprintf(stderr,"%s",argv[i]);
			break;
		}
		printf("INPUT TO HIGH\n");
		}
	return 1;
}

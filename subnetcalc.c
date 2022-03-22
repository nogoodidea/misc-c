#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
//Copyed code from stackoverflow go burrrrr
int ipow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}

int main( int argc, char *argv[] ) {
	int i = 0;
	int inputInt = 0;
	unsigned long outputInt = 0;
	if (argc != 2 ){
		printf("%s\n","NEEDS INPUT");
		return EXIT_FAILURE;
	}
	char *inputStr = argv[1];
	int done = FALSE;
	while (done != TRUE){
		switch (inputStr[i]) {
		case '\0' :
			done = TRUE;
			break;
		default:
			inputInt = inputInt*10 + (inputStr[i]- '0');
			i++;
			break;
		}
	}
	printf("%i\n",inputInt);
	outputInt = ipow(2,inputInt);
	printf("%lu\n",outputInt);
	printf("%lu\n",outputInt-2);
}

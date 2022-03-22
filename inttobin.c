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
	int outputInt = 0;
	if (argc != 2 ){
		printf("Expected 1 arg got %i\n",argc-1);
		return EXIT_FAILURE;
	}
	char *inputStr = argv[1];
	//as you can see i have no idea what i am doing
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
	//honistly most of this code is bad
	i = 0;
	while (inputInt != 0){
		outputInt = outputInt + (inputInt%2)* ipow(10,i);
		inputInt = inputInt/2;
		i++;
		}
	printf("%i",outputInt);
}

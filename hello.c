#include <stdio.h>
// some sort of comment

//checks weekday prints str
int dayCheck(int day) {
	switch (day) {
		case 0:
			printf("Mon\n");
			return 0;
		case 1:
			printf("Tue\n");
			return 0;
		case 2:
			printf("Wed\n");
			return 0;
		case 3:
			printf("Thu\n");
			return 0;
		case 4:
			printf("Fri\n");
			return 0;
		case 5:
			printf("Sat\n");
			return 0;
		case 6:
			printf("Sun\n");
			return 0;
		default:
			printf("SUFFER\n");
			return 1;}
}

int main() {
	//testvars
	int testNumber = 10;
	int a = 1, b = 2, c = 3, d = 3;
	//loop ctl
	int loopCtl = 0;
	printf("Hello World!\n");
	printf("Line 2!!!!!!\n");
	printf("%d",testNumber+20);
	printf("%d",a+b+c+d);
	while (loopCtl <8){
		dayCheck(loopCtl);
		printf("%iYOUFOOL",loopCtl);
		loopCtl ++;
	}
	return 0;
}

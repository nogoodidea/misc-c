CC = gcc -Wall

clean:
	@echo "Removeing compiled files"
	rm hello
	rm inttobin
	rm subnetcalc
	rm move

all:
	${CC} hello.c -o hello
	${CC} inttobin.c -o inttobin
	${CC} subnetcalc.c -o subnetcalc
	${CC} move.c -o move -lncurses
	${CC} menu.c -o menu

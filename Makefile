CC = gcc -Wall -g

clean:
	@echo "Removeing compiled files"
	rm hello
	rm inttobin
	rm subnetcalc
	rm move

all: hello inttobin subnetcalc move menu formatart
hello:
	${CC} hello.c -o hello
inttobin:
	${CC} inttobin.c -o inttobin
subnetcalc:	
	${CC} subnetcalc.c -o subnetcalc
move:	
	${CC} move.c -o move -lncurses
menu:
	${CC} menu.c -o menu
htmlfromat:
	${CC} htmlformat.c -o htmlformat

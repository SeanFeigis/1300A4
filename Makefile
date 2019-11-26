all: 
	gcc -ansi -Wall -o cgol cgol.c 


nextGen:
	gcc -ansi -Wall -c nextGen.c

clean:
	rm cgol
	rm nextGen.o
cgol:
	gcc -ansi -Wall -o cgol cgol.c



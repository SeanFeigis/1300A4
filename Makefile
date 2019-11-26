all: 
	gcc -ansi -Wall -o cgol cgol.c 


clean:
	rm cgol
	
cgol:
	gcc -ansi -Wall -o cgol cgol.c



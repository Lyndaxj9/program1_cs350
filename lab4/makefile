all: lab4

lab4: lab4.c prints.o
	gcc -g -O -o lab4 lab4.c prints.o

prints.o: prints.c
	gcc -g -c prints.c

clean:
	rm -f lab4
	rm -f *.o

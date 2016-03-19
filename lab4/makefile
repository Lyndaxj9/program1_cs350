all: lab4

lab4: lab4.c prints.o
	gcc -O -o lab4 lab4.c prints.o

prints.o: prints.c
	gcc -c prints.c

clean:
	rm -f lab4
	rm -f *.o

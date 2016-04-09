all: lab4

lab4: lab4.cpp Process.o prints.o
	g++ -g -Wall -o lab4 lab4.cpp Process.o prints.o

Process.o: Process.cpp
	g++ -g -c Process.cpp

prints.o: prints.cpp
	g++ -g -c prints.cpp

test: lab4
	./lab4 -p 10000 -P 25 -r 1000 -R 2000 -n 1000 -N 2500 -l

clean:
	rm -f lab4
	rm -f *.o

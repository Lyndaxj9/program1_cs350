all: lab4

lab4: lab4.cpp Process.o prints.o
	g++ -g -Wall -o lab4 lab4.cpp Process.o prints.o

Process.o: Process.cpp
	g++ -g -c Process.cpp

prints.o: prints.cpp
	g++ -g -c prints.cpp

test: lab4
	./lab4 > output.txt; vim output.txt

clean:
	rm -f lab4
	rm -f *.o

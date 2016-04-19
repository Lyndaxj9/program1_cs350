all: lab5

lab5: lab5.o Process.o
	g++ -o lab5 lab5.o Process.o

lab5.o: lab5.cpp
	g++ -g -c lab5.cpp

Process.o: Process.cpp
	g++ -g -c Process.cpp

clean:
	rm -f lab5
	rm -f *.o

all: lab5

lab5: lab5.o Process.o Node.o Linklist.o Lru.o
	g++ -o lab5 lab5.o Process.o Node.o Linklist.o Lru.o

lab5.o: lab5.cpp
	g++ -g -c lab5.cpp

Process.o: Process.cpp
	g++ -g -c Process.cpp

Node.o:	Node.cpp
	g++ -g -c Node.cpp

Linklist.o: Linklist.cpp
	g++ -g -c Linklist.cpp

Lru.o: Lru.cpp
	g++ -g -c Lru.cpp

clean:
	rm -f lab5
	rm -f *.o

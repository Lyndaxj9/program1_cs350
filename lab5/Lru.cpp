#include <stdlib.h>
#include "Lru.h"



void Lru::initMap(int value)
{
	if(Map.size() -1 < value )
	{
		Map.resize(value +1);
	}
}

void Lru::hitPage(int page, int proc)
{
	Node * tmpProc = new Node(proc);
	Node * tmpPage = new Node(page);
	Procs.eraseAndAddFront(tmpProc);
	Map[proc].eraseAndAddFront(tmpPage);
}

int Lru::getLruProc()
{
	Procs.eraseBack()->getValue();
}

int Lru::getLruPage(int proc)
{
	Map[proc].eraseBack()->getValue();
}

int Lru::hitNewPage(int page, int proc)
{
	Node * tmpProc = new Node(proc);
	Node * tmpPage = new Node(page);
	Map[proc].addFront(tmpPage);
	Procs.addFront(tmpProc);
}




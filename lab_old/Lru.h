#ifndef LRU_H
#define LRU_H


#include "Linklist.h"
#include <vector>

class Lru{
	private:
		std::vector<Linklist> Map;
		Linklist Procs;
	public:
		void initMap(int value); //Ensure Map is large enough to map index to process number 
		void hitPage(int page, int proc); //Move page and process to the front of the Lru
		int getLruProc(); //return the LRU process, remove that process from the linklist
		int getLruPage(int proc); // return the LRU page for a process, remove that page from the linklist
		int hitNewPage(int page, int proc); //Put new page from an existing proc into the linklist
};

#endif

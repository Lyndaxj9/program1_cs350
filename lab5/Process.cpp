#include "Process.h"

Process::Process() {
    processNumber = -1;
    addressSpaceSize = 0;
    pages = new int[0];
}

Process::Process(int pNum, int size) {
    processNumber = pNum;
    addressSpaceSize = size;
    pages = new int[size];
    for (int i = 0; i < size; i++) {
        pages[i] = -1;
    }
}

Process::~Process() {
    delete [] pages;
}

Process & Process::operator=(const Process &rhs) {
    processNumber = rhs.processNumber;
    addressSpaceSize = rhs.addressSpaceSize;
    delete [] pages;
    pages = new int[addressSpaceSize];
    for (int i = 0; i < addressSpaceSize; i++) {
        pages[i] = rhs.pages[i];
    }

    return *this;
}

int Process::getProcessNumber() {
    return processNumber;
}

int Process::getProcessSize() {
    return addressSpaceSize;
}

int * Process::getPages() {
    return pages;
}

int Process::getPageLocation(int pageNum) {
    return pages[pageNum];
}

void Process::setPageLocation(int pageNum, int loc) {
    pages[pageNum] = loc;
}

int Process::getSize()
{
	return addressSpaceSize;
}

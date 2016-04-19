#include "Process.h"
#include <stdlib.h>
#include <time.h>

Process::Process() {
    processNumber = -1;
    addressSpaceSize = 0;
    pages = NULL;
    pagesInMemory = -1;
}

Process::Process(int pNum, int size) {
    processNumber = pNum;
    addressSpaceSize = size;
    pages = new int[size];
    for (int i = 0; i < size; i++) {
        pages[i] = -1;
    }
    pagesInMemory = 0;
}

Process::~Process() {
    delete [] pages;
}

Process & Process::operator=(const Process &rhs) {
    processNumber = rhs.processNumber;
    addressSpaceSize = rhs.addressSpaceSize;
    if (pages != NULL) delete [] pages;
    pages = new int[addressSpaceSize];
    for (int i = 0; i < addressSpaceSize; i++) {
        pages[i] = rhs.pages[i];
    }

    return *this;
}

int Process::getRandomPage() {
    srand(time(NULL));
    int ret = -1;
    if (pagesInMemory > 0) {
        int randPage = (rand() % pagesInMemory);
        int pageCounter = 0;
        for (int i = 0; i < addressSpaceSize; i++) {
            if (pages[i] != -1) {
                pageCounter++;
            }
            if (pageCounter == randPage) {
                ret = pages[i];
            }
        }
    }
    return ret;
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
    return pages[pageNum-1];
}

void Process::setPageLocation(int pageNum, int loc) {
    pages[pageNum-1] = loc;
    if (loc == -1) {
        pagesInMemory--;
    } else {
        pagesInMemory++;
    }
}

int Process::getSize() {
    return addressSpaceSize;
}

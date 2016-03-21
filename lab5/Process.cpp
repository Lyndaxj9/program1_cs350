//Process.cpp
#include <iostream>
#include "Process.h"
using namespace std;

Process::Process(){
    pNum = -1;
    size = 0;
    pages = new int[0];
    location = new int[0];
}

Process::Process(int pid, int sizeN){
    pNum = pid;
    size = sizeN;
    pages = new int[size];
    location = new int[size];
    for(int i = 0; i<size; i++){
        pages[i] = 0;
    }
}

Process::~Process(){
    delete[] pages;
    delete[] location;
}

Process::Process(const Process &rhs){
    pNum = rhs.pNum;
    size = rhs.size;
    pages = new int[size];
    location = new int[size];
}

Process& Process::operator=(const Process &rhs){
    if(this != &rhs){
        pNum = rhs.pNum;
        size = rhs.size;
        //delete[] this->pages;
        int* temp = new int[size];
        int* tmp = new int[size];
        delete[] pages;
        delete[] location;
        //this->pages = new int[this->size];
        pages = temp;
        location = tmp;
        //delete temp;
    }

    return *this;
}

int Process::getPnum(){
    return pNum;
}

int* Process::getAddrsp(){
    return pages;
}

void Process::setValid(int pgN){
    pages[pgN] = 1;
}

void Process::setInvalid(int pgN){
    pages[pgN] = 0;
}

int Process::getPgStat(int pgN){
    return pages[pgN];
}

void Process::setLocation(int pgN, int loc){
    location[pgN] = loc;
}

/*
 * CS350 Lab5
 * Team NULL
 * Omowumi L. Ademola
 * Nuri Ra
 * Daelin Fischman
 * 
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include "Process.h"
using namespace std;

struct Mempage{
    int pnum;
    int pgNum;
};

int main(int argc, char* argv[]){
    int diskSize = 1000;

    int numFramem;
    const char* fileName;

    if(argc==3){
        numFramem = atoi(argv[1]);
        fileName = argv[2];
        //cout<<"Using: "<<fileName<<" we have "<<numFramem<<" internal"
            //<<" page table memory"<<endl;
    }else{
        cout<<"Incorrect Argument Amount"<<endl;
    }

    //address space
    Mempage* addrSpace = NULL;
    addrSpace = new Mempage[numFramem]; //remember to delete memory afterward "delete[] addrSpace;"
    for(int i = 0; i<numFramem; i++){
        addrSpace[i].pnum = -1;
        addrSpace[i].pgNum = -1;
    }

    //"disk" space
    //vector<Process*> disk(diskSize, NULL);
    vector<Process> disk(diskSize);

    //open file
    ifstream inFile(fileName);
    string lineCmd;
    stringstream parse;
string cmd;
    string buff;
    int proN;
    int addrSize;
    int pageN;
    int pageFault = 0;

    while(getline(inFile, lineCmd)){
        //cout<<lineCmd<<endl;            
        parse.clear();
        parse.str(lineCmd);
        getline(parse, cmd, ' ');
        if(cmd == "START"){
            getline(parse, buff, ' ');            
            proN = atoi(buff.c_str());
            getline(parse, buff, ' ');
            addrSize = atoi(buff.c_str());
           //cout<<"proN: "<<proN<<" addS: "<<addrSize<<endl;
            disk[proN] = Process(proN, addrSize);
            //Process* aPro = new Process(atoi(proN.c_str()),atoi(addrSize.c_str())); 
        }else if(cmd == "REFERENCE"){
            getline(parse, buff, ' ');
            proN = atoi(buff.c_str());
            getline(parse, buff, ' ');
            pageN = atoi(buff.c_str());
            
            bool inMem = false;

           // if(disk[proN]->getPgStat(pageN) == 1){
            if(disk[proN].getPgStat(pageN) == 1){
                inMem = true;
                //cout<<"Process: "<<proN<<" Page: "<<pageN<<" already in memory"<<endl;
            }

            for(int p = 0; p<numFramem && !inMem; p++){
                if(addrSpace[p].pgNum == -1){
                   // addrSpace[p].pnum = disk[proN]->getPnum();
                    addrSpace[p].pnum = disk[proN].getPnum();
                    addrSpace[p].pgNum = pageN;
                    //disk[proN]->setValid(pageN);
                    disk[proN].setValid(pageN);
                    disk[proN].setLocation(pageN, p);
                    inMem = true;
                    //cout<<"Process: "<<addrSpace[p].pnum<<" Page: "<<addrSpace[p].pgNum<<" was added to memory"<<endl;
                }
            }

            if(!inMem){
                pageFault++;
                cout<<pageFault<<" page fault(s) so far"<<endl;
            }
        }else if(cmd == "TERMINATE"){
            getline(parse, buff, ' ');
            proN = atoi(buff.c_str());
            for(int p = 0; p<numFramem; p++){
                if(addrSpace[p].pnum == proN){
                    disk[proN].setLocation(addrSpace[p].pgNum, -1);
                    addrSpace[p].pnum = -1;
                    addrSpace[p].pgNum = -1;
                }
            }

            disk[proN] = Process();
            
            //cout<<"Process: "<<proN<<" terminated"<<endl;

        }else{
            cout<<"Command not supported"<<endl;
            exit(1);
        }
    }

    delete[] addrSpace;
    disk.clear();

    return 0;
}

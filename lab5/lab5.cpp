#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <limits>
#include <time.h>

#include "Process.h"

struct MemoryFrame {
    int processNumber;
    int pageNumber;
    unsigned long long timestamp;
};

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "Usage: ./lab5 <frames-of-memory> <input-file>" << std::endl;
        return 1;
    }

    int memFrames = atoi(argv[1]);
    if (memFrames == -1) {
        std::cout << "Invalid frames of memory.\n" << std::endl;
        return 1;
    }

    Process disk[5000];
    Process test1_disk[5000];
    Process test2_disk[5000];
    Process test3_disk[5000];
    Process test4_disk[5000];
    MemoryFrame * memory = new MemoryFrame[memFrames];
    MemoryFrame * test1_memory = new MemoryFrame[memFrames];
    MemoryFrame * test2_memory = new MemoryFrame[memFrames];
    MemoryFrame * test3_memory = new MemoryFrame[memFrames];
    MemoryFrame * test4_memory = new MemoryFrame[memFrames];
    int memSize = 0;
    int test1_memSize = 0;
    int test2_memSize = 0;
    int test3_memSize = 0;
    int test4_memSize = 0;
    int pageFaults = 0;
    int test1_pageFaults = 0;
    int test2_pageFaults = 0;
    int test3_pageFaults = 0;
    int test4_pageFaults = 0;
    int totalReferences = 0;
    for (int i = 0; i < memFrames; i++) {
        memory[i].processNumber = -1; memory[i].pageNumber = -1; memory[i].timestamp = -1;
        test1_memory[i].processNumber = -1; test1_memory[i].pageNumber = -1; test1_memory[i].timestamp = -1;
        test2_memory[i].processNumber = -1; test2_memory[i].pageNumber = -1; test2_memory[i].timestamp = -1;
        test3_memory[i].processNumber = -1; test3_memory[i].pageNumber = -1; test3_memory[i].timestamp = -1;
        test4_memory[i].processNumber = -1; test4_memory[i].pageNumber = -1; test4_memory[i].timestamp = -1;
    }

    std::ifstream inputFile(argv[2]);
    if (inputFile.fail()) {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    std::string line;
    std::string command;
    int processNum;
    int addressSpaceSize;
    int virtualPageNum;

    int diskUsageCounter = 0;
    unsigned long long time = 0;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        ss >> command >> processNum;

        if (command == "START") {
            ss >> addressSpaceSize;
            // std::cout << "START " << processNum << " " << addressSpaceSize << std::endl;
            Process p(processNum, addressSpaceSize);
            Process test1_p(processNum, addressSpaceSize);
            Process test2_p(processNum, addressSpaceSize);
            Process test3_p(processNum, addressSpaceSize);
            Process test4_p(processNum, addressSpaceSize);
            disk[diskUsageCounter] = p;
            test1_disk[diskUsageCounter] = test1_p;
            test2_disk[diskUsageCounter] = test2_p;
            test3_disk[diskUsageCounter] = test3_p;
            test4_disk[diskUsageCounter] = test4_p;
            diskUsageCounter++;
        } else if (command == "REFERENCE") {
            ss >> virtualPageNum;
            // std::cout << "REFERENCE " << processNum << " " << virtualPageNum << std::endl;
            int found = -1;
            for (int i = 0; i < diskUsageCounter; i++) {
                if (disk[i].getProcessNumber() == processNum) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                // Regular LRU Algorithm
                if (disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (memSize == memFrames) {
                        unsigned long long timeIter = -1;
                        int memAddress = 0;
                        for(int i = 0; i < memFrames; i++)
                        {
                            if(memory[i].timestamp < timeIter)
                            {
                                timeIter = memory[i].timestamp;
                                memAddress = i;
                            }
                        }
                        int tempProc = memory[memAddress].processNumber;
                        int tempPage = memory[memAddress].pageNumber;

                        memory[memAddress].processNumber = processNum;
                        memory[memAddress].pageNumber = virtualPageNum;
                        memory[memAddress].timestamp = time; 
                        disk[found].setPageLocation(virtualPageNum, memAddress);
                        for(int i =0; i<diskUsageCounter; i++)
                        {
                            if(disk[i].getProcessNumber() == tempProc)
                            {
                                disk[i].setPageLocation(tempPage, -1);
                            }
                        }

                        pageFaults++;
                    } else {
                        // not at capacity, just put it into memory
                        for (int i = 0; i < memFrames; i++) {
                            if (memory[i].processNumber == -1) {
                                memory[i].processNumber = processNum;
                                memory[i].pageNumber = virtualPageNum;
                                memory[i].timestamp = time;
                                disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        //std::cout << "No fault, space in memory: " << line << std::endl;
                        memSize++;
                    }
                } else {
                    memory[disk[found].getPageLocation(virtualPageNum)].timestamp = time;
                    //std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 1 - LRU w/in the ref'd process's own pages
                if (test1_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test1_memSize == memFrames) {
                        // look for process in disk - process was already found in disk?
                        //for(int i = 0; i < diskUsageCounter; i++){
                        // if the process is found go in and start looking for min page
                        if (test1_disk[found].getProcessNumber() == processNum){
                            // set minTime to infinity to be able to compare to timestamp
                            double minTime = std::numeric_limits<double>::infinity();
                            int mintimeLoc = -1;
                            int minPage = -1;
                            int notEmpty = 0;
                            int minProc = -1;
                            // go through the process's address space and look thru all pages
                            for (int j = 1; j <= test1_disk[found].getProcessSize(); j++){
                                // if the page is in memory then compare timestamps
                                if (test1_disk[found].getPageLocation(j) != -1){
                                    notEmpty = 1;
                                    if (test1_memory[test1_disk[found].getPageLocation(j)].timestamp < minTime){
                                        minTime = test1_memory[test1_disk[found].getPageLocation(j)].timestamp;
                                        mintimeLoc = test1_disk[found].getPageLocation(j);
                                        minPage = j;
                                    }
                                }
                            }
                            if (notEmpty == 1){
                                // the process has pages in memory and the lru page get's replaced
                                test1_memory[mintimeLoc].processNumber = processNum;
                                test1_memory[mintimeLoc].pageNumber = virtualPageNum;
                                test1_memory[mintimeLoc].timestamp = time;
                                test1_disk[found].setPageLocation(virtualPageNum, mintimeLoc);
                                test1_disk[found].setPageLocation(minPage, -1);
                            } else {
                                // regular lru
                                for (int j = 0; j < test1_memSize; j++) {
                                    if (test1_memory[j].timestamp < minTime) {
                                        minTime = test1_memory[j].timestamp;
                                        mintimeLoc = j;
                                    }
                                }

                                minProc = test1_memory[mintimeLoc].processNumber;
                                minPage = test1_memory[mintimeLoc].pageNumber;

                                test1_memory[mintimeLoc].processNumber = processNum;
                                test1_memory[mintimeLoc].pageNumber = virtualPageNum;
                                test1_memory[mintimeLoc].timestamp = time;
                                test1_disk[found].setPageLocation(virtualPageNum, mintimeLoc);

                                for (int i = 0; i < diskUsageCounter; i++) {
                                    if (test1_disk[i].getProcessNumber() == minProc){
                                        test1_disk[i].setPageLocation(minPage, -1);
                                    }
                                }
                            }
                        }
                        //}
                        test1_pageFaults++;
                        //std::cout << "Page Fault, memory full: " << line << std::endl;
                    } else {
                        // not at capacity, just put it into memory
                        for (int i = 0; i < memFrames; i++) {
                            if (test1_memory[i].processNumber == -1) {
                                test1_memory[i].processNumber = processNum;
                                test1_memory[i].pageNumber = virtualPageNum;
                                test1_disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        //std::cout << "No fault, space in memory: " << line << std::endl;
                        test1_memSize++;
                    }
                } else {
                    //std::cout << "No fault, already exists in memory: " << line << std::endl;
                }


                ////Algorithm 2
                //if (test2_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                //    if (test2_memSize == memFrames) {
                //        int pagesAbove = 50;
                //        if(((test2_disk[found].getSize()-1) - virtualPageNum) < 4)
                //        {
                //            pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                //        }
                //        for(int x = 0; x < pagesAbove; x++)
                //        {
                //            unsigned long long timeIter = -1;
                //            int memAddress = 0;
                //            for(int i = 0; i < memFrames; i++)
                //            {
                //                if(test2_memory[i].timestamp < timeIter)
                //                {
                //                    timeIter = test2_memory[i].timestamp;
                //                    memAddress = i;
                //                }
                //            }
                //            int tempProc = test2_memory[memAddress].processNumber;
                //            int tempPage = test2_memory[memAddress].pageNumber;

                //            test2_memory[memAddress].processNumber = processNum;
                //            test2_memory[memAddress].pageNumber = virtualPageNum+x;
                //            test2_memory[memAddress].timestamp = time; 
                //            test2_disk[found].setPageLocation(virtualPageNum+x, memAddress);
                //            for(int i =0; i<diskUsageCounter; i++)
                //            {
                //                if(test2_disk[i].getProcessNumber() == tempProc)
                //                {
                //                    test2_disk[i].setPageLocation(tempPage, -1);
                //                }
                //            }
                //        }

                //        test2_pageFaults++;
                //        //std::cout << "Page Fault, memory full: " << line << std::endl;
                //    } else {
                //        if((memFrames - test2_memSize) > 4)
                //        {
                //            int pagesAbove = 50;
                //            if(((test2_disk[found].getSize()-1) - virtualPageNum) < 4)
                //            {
                //                pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                //            }
                //            bool done = false;
                //            for (int i = 0; i < memFrames; i++) {
                //                for(int x = 0; x < pagesAbove; x++)
                //                {
                //                    if (test2_memory[i].processNumber == -1) {
                //                        done = true;
                //                        //std::cout << " Adding new Page: " << virtualPageNum+x << std::endl;
                //                        test2_memory[i].processNumber = processNum;
                //                        test2_memory[i].pageNumber = virtualPageNum+x;
                //                        test2_memory[i].timestamp = time;
                //                        test2_disk[found].setPageLocation(virtualPageNum+x, i);
                //                    }
                //                }
                //                if (done) break;
                //            }

                //        }
                //        else
                //        {
                //            int pagesAbove = 50;
                //            if(test2_disk[found].getSize() < 4)
                //            {
                //                pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                //            }
                //            if(pagesAbove > (memFrames-test2_memSize))
                //            {
                //                pagesAbove = memFrames-test2_memSize;
                //            }
                //            bool done = false;
                //            for (int i = 0; i < memFrames; i++) {
                //                for(int x = 0; x < pagesAbove; x++)
                //                {
                //                    if (test2_memory[i].processNumber == -1) {
                //                        done = true;
                //                        //std::cout << " Adding new Page: " << virtualPageNum+x << std::endl;
                //                        test2_memory[i].processNumber = processNum;
                //                        test2_memory[i].pageNumber = virtualPageNum+x;
                //                        test2_memory[i].timestamp = time;
                //                        test2_disk[found].setPageLocation(virtualPageNum+x, i);
                //                    }
                //                }
                //                if (done) break;
                //            }

                //        }
                //        //std::cout << "No fault, space in memory: " << line << std::endl;
                //        test2_memSize++;
                //    }
                //} else {
                //    //std::cout << "No fault, already exists in memory: " << line << std::endl;
                //}

                //Algorithm 2
                if (test2_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test2_memSize == memFrames) {
                        int pagesAbove = 0;
                        if(((test2_disk[found].getSize()-1) - virtualPageNum) < 4)
                        {
                            pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                        }
                        for(int x = 0; x < pagesAbove; x++)
                        {
                            unsigned long long timeIter = -1;
                            int memAddress = 0;
                            for(int i = 0; i < memFrames; i++)
                            {
                                if(test2_memory[i].timestamp < timeIter)
                                {
                                    timeIter = test2_memory[i].timestamp;
                                    memAddress = i;
                                }
                            }
                            int tempProc = test2_memory[memAddress].processNumber;
                            int tempPage = test2_memory[memAddress].pageNumber;

                            test2_memory[memAddress].processNumber = processNum;
                            test2_memory[memAddress].pageNumber = virtualPageNum+x;
                            test2_memory[memAddress].timestamp = time; 
                            test2_disk[found].setPageLocation(virtualPageNum+x, memAddress);
                            for(int i =0; i<diskUsageCounter; i++)
                            {
                                if(test2_disk[i].getProcessNumber() == tempProc)
                                {
                                    test2_disk[i].setPageLocation(tempPage, -1);
                                }
                            }
                        }

                        test2_pageFaults++;
                        //std::cout << "Page Fault, memory full: " << line << std::endl;
                    } else {
                        if((memFrames - test2_memSize) > 4)
                        {
                            int pagesAbove = 4;
                            if(((test2_disk[found].getSize()-1) - virtualPageNum) < 4)
                            {
                                pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                            }
                            bool done = false;
                            for (int i = 0; i < memFrames; i++) {
                                for(int x = 0; x < pagesAbove; x++)
                                {
                                    if (test2_memory[i].processNumber == -1) {
                                        done = true;
                                        //std::cout << " Adding new Page: " << virtualPageNum+x << std::endl;
                                        test2_memory[i].processNumber = processNum;
                                        test2_memory[i].pageNumber = virtualPageNum+x;
                                        test2_memory[i].timestamp = time;
                                        test2_disk[found].setPageLocation(virtualPageNum+x, i);
                                    }
                                }
                                if (done) break;
                            }

                        }
                        else
                        {
                            int pagesAbove = 4;
                            if(test2_disk[found].getSize() < 4)
                            {
                                pagesAbove = (test2_disk[found].getSize()-1) - virtualPageNum;
                            }
                            if(pagesAbove > (memFrames-test2_memSize))
                            {
                                pagesAbove = memFrames-test2_memSize;
                            }
                            bool done = false;
                            for (int i = 0; i < memFrames; i++) {
                                for(int x = 0; x < pagesAbove; x++)
                                {
                                    if (test2_memory[i].processNumber == -1) {
                                        done = true;
                                        //std::cout << " Adding new Page: " << virtualPageNum+x << std::endl;
                                        test2_memory[i].processNumber = processNum;
                                        test2_memory[i].pageNumber = virtualPageNum+x;
                                        test2_memory[i].timestamp = time;
                                        test2_disk[found].setPageLocation(virtualPageNum+x, i);
                                    }
                                }
                                if (done) break;
                            }

                        }
                        //std::cout << "No fault, space in memory: " << line << std::endl;
                        test2_memSize++;
                    }
                } else {
                    //std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 3
                if (test3_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test3_memSize == memFrames) {
                        // memory is at capacity, need to replace here
                        int randomPage = test3_disk[found].getRandomPage();
                        if (randomPage == -1) { // process has no pages in memory, regular LRU
                            unsigned long long timeIter = -1;
                            int memAddress = 0;
                            for(int i = 0; i < memFrames; i++)
                            {
                                if(test3_memory[i].timestamp < timeIter)
                                {
                                    timeIter = test3_memory[i].timestamp;
                                    memAddress = i;
                                }
                            }
                            int tempProc = test3_memory[memAddress].processNumber;
                            int tempPage = test3_memory[memAddress].pageNumber;

                            test3_memory[memAddress].processNumber = processNum;
                            test3_memory[memAddress].pageNumber = virtualPageNum;
                            test3_memory[memAddress].timestamp = time; 
                            test3_disk[found].setPageLocation(virtualPageNum, memAddress);

                            for(int i =0; i<diskUsageCounter; i++)
                            {
                                if(test3_disk[i].getProcessNumber() == tempProc)
                                {
                                    test3_disk[i].setPageLocation(tempPage, -1);
                                }
                            }

                        } else {
                            // int oldProcessNum = test3_memory[randomPage].processNumber;
                            // int oldPageNum = test3_memory[randomPage].pageNumber;
                            // test3_memory[randomPage].processNumber = processNum;
                            // test3_memory[randomPage].pageNumber = virtualPageNum;
                            // test3_memory[randomPage].timestamp = time;

                            // for (int i = 0; i < diskUsageCounter; i++) {
                            //     if (test3_disk[i].getProcessNumber() == oldProcessNum) {
                            //         test3_disk[i].setPageLocation(oldPageNum, -1);
                            //     }
                            // }
                        }
                        test3_pageFaults++;
                        // std::cout << "Page Fault, memory full: " << line << std::endl;
                    } else {
                        // not at capacity, just put it into memory
                        for (int i = 0; i < memFrames; i++) {
                            if (test3_memory[i].processNumber == -1) {
                                test3_memory[i].processNumber = processNum;
                                test3_memory[i].pageNumber = virtualPageNum;
                                test3_disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        // std::cout << "No fault, space in memory: " << line << std::endl;
                        test3_memSize++;
                    }
                } else {
                    // std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 4
                if (test4_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test4_memSize == memFrames) {
                        // memory is at capacity, need to replace here
                        
                        srand(time(NULL));
                    } else {
                        for (int i = 0; i < memFrames; i++) {
                            if (test4_memory[i].processNumber == -1) {
                                test4_memory[i].processNumber = processNum;
                                test4_memory[i].pageNumber = virtualPageNum;
                                test4_disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        // std::cout << "No fault, space in memory: " << line << std::endl;
                        test4_memSize++;
                    }
                } else {
                    // std::cout << "No fault, already exists in memory: " << line << std::endl;
                }
                time++;
                totalReferences++;
            } else {
                //std::cout << "Invalid: " << line << std::endl;
            }
        } else if (command == "TERMINATE") {
            // std::cout << "TERMINATE " << processNum << std::endl;
            int found = -1;
            for (int i = 0; i < diskUsageCounter; i++) {
                if (disk[i].getProcessNumber() == processNum) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                for (int i = 0; i < memFrames; i++) {
                    if (memory[i].processNumber == processNum) {
                        memory[i].processNumber = -1;
                        memory[i].pageNumber = -1;
                        memSize--;
                    }
                    if (test1_memory[i].processNumber == processNum) {
                        test1_memory[i].processNumber = -1;
                        test1_memory[i].pageNumber = -1;
                        test1_memSize--;
                    }
                    if (test2_memory[i].processNumber == processNum) {
                        test2_memory[i].processNumber = -1;
                        test2_memory[i].pageNumber = -1;
                        test2_memSize--;
                    }
                    if (test3_memory[i].processNumber == processNum) {
                        test3_memory[i].processNumber = -1;
                        test3_memory[i].pageNumber = -1;
                        test3_memSize--;
                    }
                }

                // get rid of process in disk
                // disk[found];
            } else {
                //std::cout << "Invalid: " << line << std::endl;
            }
        } else {
            //std::cout << "Unrecognized Command: " << command << std::endl;
        }
    }

    std::cout << "\nLRU Results:" << std::endl;
    std::cout << "Page Fault Amount: " << pageFaults << std::endl;
    std::cout << "Total Page References: " << totalReferences << std::endl;

    std::cout << "\nAlgorithm 1 Results:" << std::endl;
    std::cout << "Page Fault Amount: " << test1_pageFaults << std::endl;
    std::cout << "Total Page References: " << totalReferences << std::endl;

    std::cout << "\nAlgorithm 2 Results:" << std::endl;
    std::cout << "Page Fault Amount: " << test2_pageFaults << std::endl;
    std::cout << "Total Page References: " << totalReferences << std::endl;

    std::cout << "\nAlgorithm 3 Results:" << std::endl;
    std::cout << "Page Fault Amount: " << test3_pageFaults << std::endl;
    std::cout << "Total Page References: " << totalReferences << std::endl;

    delete [] memory;
    delete [] test1_memory;
    delete [] test2_memory;
    delete [] test3_memory;
    return 0;
}

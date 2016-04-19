#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

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
    MemoryFrame * memory = new MemoryFrame[memFrames];
    MemoryFrame * test1_memory = new MemoryFrame[memFrames];
    MemoryFrame * test2_memory = new MemoryFrame[memFrames];
    MemoryFrame * test3_memory = new MemoryFrame[memFrames];
    int memSize = 0;
    int test1_memSize = 0;
    int test2_memSize = 0;
    int test3_memSize = 0;
    int pageFaults = 0;
    int test1_pageFaults = 0;
    int test2_pageFaults = 0;
    int test3_pageFaults = 0;
    int totalReferences = 0;
    for (int i = 0; i < memFrames; i++) {
        memory[i].processNumber = -1; memory[i].pageNumber = -1; memory[i].timestamp = -1;
        test1_memory[i].processNumber = -1; test1_memory[i].pageNumber = -1; test1_memory[i].timestamp = -1;
        test2_memory[i].processNumber = -1; test2_memory[i].pageNumber = -1; test2_memory[i].timestamp = -1;
        test3_memory[i].processNumber = -1; test3_memory[i].pageNumber = -1; test3_memory[i].timestamp = -1;
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
            disk[diskUsageCounter] = p;
            test1_disk[diskUsageCounter] = test1_p;
            test2_disk[diskUsageCounter] = test2_p;
            test3_disk[diskUsageCounter] = test3_p;
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
                        // std::cout << "Page Fault, memory full " << line << " Kicking out " << tempProc << " " << tempPage << std::endl;
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
                        std::cout << "No fault, space in memory: " << line << std::endl;
                        memSize++;
                    }
                } else {
					memory[disk[found].getPageLocation(virtualPageNum)].timestamp = time;
                    std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 1
                if (test1_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test1_memSize == memFrames) {
                        // memory is at capacity, need to replace here
                        // ******************************
                        // ADD REPLACEMENT ALGORITHM HERE
                        // ******************************
                        test1_pageFaults++;
                        std::cout << "Page Fault, memory full: " << line << std::endl;
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
                        std::cout << "No fault, space in memory: " << line << std::endl;
                        test1_memSize++;
                    }
                } else {
                    std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 2
                if (test2_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test2_memSize == memFrames) {
                        // memory is at capacity, need to replace here
                        // ******************************
                        // ADD REPLACEMENT ALGORITHM HERE
                        // ******************************
                        

                        test2_pageFaults++;
                        std::cout << "Page Fault, memory full: " << line << std::endl;
                    } else {
                        // not at capacity, just put it into memory
                        for (int i = 0; i < memFrames; i++) {
                            if (test2_memory[i].processNumber == -1) {
                                test2_memory[i].processNumber = processNum;
                                test2_memory[i].pageNumber = virtualPageNum;
                                test2_disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        std::cout << "No fault, space in memory: " << line << std::endl;
                        test2_memSize++;
                    }
                } else {
                    std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                //Algorithm 3
                if (test3_disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (test3_memSize == memFrames) {
                        // memory is at capacity, need to replace here
                        int randomPage = test3_disk[found].getRandomPage();
                        if (randomPage == -1) { // process has no pages in memory, regular LRU
                            // find least recently used
                            unsigned long long leastRecentlyUsed = -1;
                            int memAddress = -1;
                            for (int i = 0; i < memFrames; i++) {
                                if (test3_memory[i].timestamp < leastRecentlyUsed) {
                                    test3_memory[i].timestamp = leastRecentlyUsed;
                                    memAddress = i;
                                }
                            }

                            // Old Process in memory, to be replaced
                            int oldProcessNum = test3_memory[memAddress].processNumber;
                            int oldPageNum = test3_memory[memAddress].pageNumber;

                            // Replace with new process reference
                            test3_memory[memAddress].processNumber = processNum;
                            test3_memory[memAddress].pageNumber = virtualPageNum;
                            test3_memory[memAddress].timestamp = time;
                            test3_disk[found].setPageLocation(found, virtualPageNum);

                            // Set invalid/valid bit to -1 in old process
                            for (int i = 0; i < diskUsageCounter; i++) {
                                if (test3_disk[i].getProcessNumber() == oldProcessNum) {
                                    test3_disk[i].setPageLocation(oldPageNum, -1);
                                }
                            }
                        } else {
                            int oldProcessNum = test3_memory[randomPage].processNumber;
                            int oldPageNum = test3_memory[randomPage].pageNumber;
                            test3_memory[randomPage].processNumber = processNum;
                            test3_memory[randomPage].pageNumber = virtualPageNum;
                            test3_memory[randomPage].timestamp = time;

                            for (int i = 0; i < diskUsageCounter; i++) {
                                if (test3_disk[i].getProcessNumber() == oldProcessNum) {
                                    test3_disk[i].setPageLocation(oldPageNum, -1);
                                }
                            }
                        }
                        test3_pageFaults++;
                        std::cout << "Page Fault, memory full: " << line << std::endl;
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
                        std::cout << "No fault, space in memory: " << line << std::endl;
                        test3_memSize++;
                    }
                } else {
                    std::cout << "No fault, already exists in memory: " << line << std::endl;
                }

                time++;
                totalReferences++;
            } else {
                std::cout << "Invalid: " << line << std::endl;
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
                std::cout << "Invalid: " << line << std::endl;
            }
        } else {
            std::cout << "Unrecognized Command: " << command << std::endl;
        }
    }

    std::cout << "\nAlgorithm 3 Results:" << std::endl;
    std::cout << "Page Fault Amount: " << test3_pageFaults << std::endl;
    std::cout << "Total Page References: " << totalReferences << std::endl;

    // std::cout << "Printing Disk Contents:" << std::endl;
    // for (int i = 0; i < diskUsageCounter; i++) {
    //     std::cout << "PROCESS " << disk[i].getProcessNumber() 
    //         << ", SIZE: " << disk[i].getProcessSize() << std::endl;
    // }
    // 
    // std::cout << "Printing Memory Contents:" << std::endl;
    // for (int i = 0; i < memFrames; i++) {
    //     std::cout << i << " PROCESS " << memory[i].processNumber
    //         << ", PAGE #: " << memory[i].pageNumber << std::endl;
    // }

    // delete [] memory;
    // delete [] test1_memory;
    // delete [] test2_memory;
    // delete [] test3_memory;
    return 0;
}

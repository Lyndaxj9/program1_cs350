#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include "Process.h"

struct MemoryFrame {
    int processNumber;
    int pageNumber;
    long timestamp;
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
    int pageFaults = 0;
    long time = 0;
    while (getline(inputFile, line)) {
        std::stringstream ss(line);
        ss >> command >> processNum;

        if (command == "START") {
            ss >> addressSpaceSize;
            // std::cout << "START " << processNum << " " << addressSpaceSize << std::endl;
            Process p(processNum, addressSpaceSize);
            disk[diskUsageCounter] = p;
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
                if (disk[found].getPageLocation(virtualPageNum) == -1) { //not in memory
                    if (memSize == memFrames) {
                        // memory is at capacity
                        // ******************************
                        // ADD REPLACEMENT ALGORITHM HERE
                        // ******************************
                        pageFaults++;
                        std::cout << "Page Fault, memory full: " << line << std::endl;
                    } else {
                        // page replacement
                        for (int i = 0; i < memFrames; i++) {
                            if (memory[i].processNumber == -1) {
                                memory[i].processNumber = processNum;
                                memory[i].pageNumber = virtualPageNum;
                                disk[found].setPageLocation(virtualPageNum, i);
                                break;
                            }
                        }
                        std::cout << "No fault, space in memory: " << line << std::endl;
                        memSize++;
                    }
                } else {
                    std::cout << "No fault, already exists in memory: " << line << std::endl;
                }
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

    delete [] memory;
    delete [] test1_memory;
    delete [] test2_memory;
    delete [] test3_memory;
    return 0;
}
